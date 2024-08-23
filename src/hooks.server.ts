import { type Handle } from "@sveltejs/kit";
import { sequence } from "@sveltejs/kit/hooks";
import { authenticationHandle, authorizationHandle } from "./auth";
import { getMessages, getUser, getUserFromEmail } from "./db/dbClient";
import { env as privateEnv } from "$env/dynamic/private";
import { env as publicEnv } from "$env/dynamic/public";
import { AppModes, Role } from "./constants";
import { env } from "$env/dynamic/private";
import moment from "moment";
import { renderHandle } from "$lib/render";

export const APP_MODE = env.DELIVER_TIME
  ? AppModes.LimitArrives
  : AppModes.LimitSends;

const getNextPostTime = () => {
  const time = moment("6:00 PM", "h:mm A");
  if (moment().isBefore(time)) return time;
  return time.add(1, "days");
};

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
  event.locals.messages = await getMessages();

  //4. Get time the user can next post
  if (APP_MODE == AppModes.LimitSends) {
    const time = messages.find((m) => m.authorId === id)?.createdAt.getTime();
    if (time)
      event.locals.nextTime = time + parseInt(publicEnv.PUBLIC_TIME_INTERVAL);
    else event.locals.nextTime = Date.now();
  } else {
    event.locals.nextTime = getNextPostTime().valueOf();
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
