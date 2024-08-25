import { type Handle } from "@sveltejs/kit";
import { sequence } from "@sveltejs/kit/hooks";
import { authenticationHandle, authorizationHandle } from "./auth";
import {
  ensureTokens,
  getMessages,
  getUser,
  getUserFromEmail,
  getUserFromToken,
  userEmailList,
} from "./db/dbClient";
import { env as privateEnv } from "$env/dynamic/private";
import { env as publicEnv } from "$env/dynamic/public";
import {
  AppModes,
  Role,
  APP_MODE,
  getNextPostTime,
  getLastPostTime,
  type userDataType,
} from "./constants";
import { renderHandle } from "$lib/render";
import normalize from "path-normalize";

// Run here to prevent build-time execution
ensureTokens();

const userDataHandle: Handle = async ({ event, resolve }) => {
  const session = await event.locals.auth();
  const normedPath = normalize(event.url.pathname);
  // Set up defaults
  event.locals.messages = [];
  event.locals.nextTime = Date.now();
  event.locals.userID = "";
  event.locals.tokenID = "";
  event.locals.role = Role.Guest;
  event.locals.appMode = APP_MODE;
  event.locals.thisTermMessages = [];
  //1. Get User from DB
  let id = session?.user?.id;
  let user: userDataType | undefined;
  if (id) {
    user = await getUser(id);
  } else if (session && session.user?.email) {
    // Get ID from database
    user = await getUserFromEmail(session.user?.email);
    if (user) {
      id = user.id;
    }
  } else if (normedPath.startsWith("/api") && event.params.user) {
    // Get ID if in the API routes
    user = await getUserFromToken(event.params.user);
    if (user) {
      id = user.id;
    }
  }
  // Exit if no session or id
  if (!user || !id) {
    return await resolve(event);
  }

  //2. Get user ID and role
  event.locals.role =
    user.email && privateEnv.ADMIN_WHITELIST.split(",").includes(user.email)
      ? Role.Admin
      : Role.User;
  event.locals.userID = id;
  event.locals.tokenID = user.token;

  //3. Get messages
  event.locals.messages = await getMessages();
  if (APP_MODE == AppModes.LimitArrives)
    event.locals.thisTermMessages = await getMessages(
      undefined,
      getLastPostTime().toDate(),
      new Date()
    );

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
