import { redirect, type Handle } from "@sveltejs/kit";
import nodeHtmlToImage from "node-html-to-image";
import Jimp from "jimp";
import { encode } from "bmp-ts";
import { sequence } from "@sveltejs/kit/hooks";
import { handle as authenticationHandle } from "./auth";
import { getMessages, getUser, getUserFromEmail } from "./db/dbClient";
import { env as privateEnv } from "$env/dynamic/private";
import { env as publicEnv } from "$env/dynamic/public";
import { Role } from "./hookTypes";

async function transformPageChunk({ html }: { html: string }) {
  const image = await nodeHtmlToImage({
    html,
    encoding: "binary",
    transparent: false,
    puppeteerArgs: {
      args: ["--no-sandbox", "--disable-setuid-sandbox"],
    },
  });
  return image as Buffer;
}

export type messageDataType = NonNullable<
  Awaited<ReturnType<typeof getMessages>>
>[0];

const authorizationHandle: Handle = async ({ event, resolve }) => {
  // Protect all routes except /api and /auth
  if (
    !event.url.pathname.startsWith("/auth") &&
    !event.url.pathname.startsWith("/api")
  ) {
    const session = await event.locals.auth();
    if (!session) {
      // Redirect to the signin page
      throw redirect(303, "/auth/signin");
    }
  }

  // If the request is still here, just proceed as normally
  return resolve(event);
};

const renderHandle: Handle = async ({ event, resolve }) => {
  if (
    /^\/?api\/[^\/]+\/pages\/\d/.test(event.url.pathname) &&
    !event.url.searchParams.has("live")
  ) {
    const res = await resolve(event);
    if (res.status !== 200) {
      return res;
    }
    const body = await res.text();
    const transformedBody = await transformPageChunk({ html: body });
    const img = await Jimp.read(transformedBody);
    const onebit = encode({
      data: img.bitmap.data,
      width: img.bitmap.width,
      height: img.bitmap.height,
      bitPP: 1,
    }).data;

    let messageData: [string, string][] = [];
    if (res.headers.has("messageCount")) {
      messageData = [["messageCount", res.headers.get("messageCount") || ""]];
    }

    return new Response(onebit, {
      status: res.status,
      headers: [["Content-Type", Jimp.MIME_BMP], ...messageData],
    });
  }
  const response = await resolve(event);
  return response;
};

const userDataHandle: Handle = async ({ event, resolve }) => {
  const session = await event.locals.auth();
  let id = session?.user?.id;
  if (session && !id && session.user?.email) {
    // Get ID from database
    const foundUser = await getUserFromEmail(session.user?.email);
    if (foundUser) {
      id = foundUser.id;
    }
  }
  if (session && id) {
    event.locals.role =
      session.user?.email &&
      privateEnv.ADMIN_WHITELIST.split(",").includes(session.user.email)
        ? Role.Admin
        : Role.User;
    event.locals.userID = id;
    const messages = await getMessages();
    if (messages && messages.length > 0) {
      event.locals.messages = messages;
      const time = messages[0].createdAt.getTime();
      if (time)
        event.locals.nextTime = time + parseInt(publicEnv.PUBLIC_TIME_INTERVAL);
    } else {
      event.locals.messages = [];
      event.locals.nextTime = Date.now();
    }
  } else {
    event.locals.messages = [];
    event.locals.nextTime = Date.now();
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
