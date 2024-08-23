import { type Handle } from "@sveltejs/kit";
import { sequence } from "@sveltejs/kit/hooks";
import { authenticationHandle, authorizationHandle } from "./auth";
import { getMessages, getUser, getUserFromEmail } from "./db/dbClient";
import { env as privateEnv } from "$env/dynamic/private";
import { env as publicEnv } from "$env/dynamic/public";
import {
  AppModes,
  Role,
  APP_MODE,
  getNextPostTime,
  getLastPostTime,
} from "./constants";
import { renderHandle } from "$lib/render";

const userDataHandle: Handle = async ({ event, resolve }) => {
  const session = await event.locals.auth();
  // Set up defaults
  event.locals.messages = [];
  event.locals.nextTime = Date.now();
  event.locals.userID = "";
  event.locals.role = Role.Guest;
  event.locals.appMode = APP_MODE;
  //1. Get ID
  let id = session?.user?.id;
  if (session && !id && session.user?.email) {
    // Get ID from database
    const foundUser = await getUserFromEmail(session.user?.email);
    if (foundUser) {
      id = foundUser.id;
    }
  }
  // Exit if no session or id
  if (!id || !session) {
    return await resolve(event);
  }
  //2. Get user ID and role
  event.locals.role =
    session.user?.email &&
    privateEnv.ADMIN_WHITELIST.split(",").includes(session.user.email)
      ? Role.Admin
      : Role.User;
  event.locals.userID = id;

  //3. Get messages
  if (event.locals.role === Role.Admin) {
    event.locals.messages = await getMessages();
  } else {
    event.locals.messages = await getMessages(
      undefined,
      getLastPostTime().subtract(1, "days").toDate()
    );
  }

  //4. Get time the user can next post
  if (APP_MODE == AppModes.LimitSends) {
    const time = event.locals.messages
      .find((m) => m.authorId === id)
      ?.createdAt.getTime();
    if (time)
      event.locals.nextTime = time + parseInt(publicEnv.PUBLIC_TIME_INTERVAL);
  } else {
    const hasPosted = event.locals.messages.some(
      (m) => m.authorId === id && m.createdAt > getLastPostTime()
    );
    event.locals.nextTime = hasPosted
      ? getNextPostTime().valueOf()
      : getLastPostTime().valueOf();
  }

  const response = await resolve(event);
  return response;
};

export const handle: Handle = sequence(
  authenticationHandle,
  authorizationHandle,
  renderHandle,
  userDataHandle
);
