import { redirect, type Handle } from "@sveltejs/kit";
import Jimp from "jimp";
import { encode } from "bmp-ts";
import { sequence } from "@sveltejs/kit/hooks";
import { handle as authenticationHandle } from "./auth";
import { getMessages, getUser, getUserFromEmail } from "./db/dbClient";
import { env as privateEnv } from "$env/dynamic/private";
import { env as publicEnv } from "$env/dynamic/public";
import { Role } from "./hookTypes";
import puppeteer from "puppeteer";
import { env } from "$env/dynamic/private";
import normalize from "path-normalize";

const resolution = {
  w: 296,
  h: 128,
};

const getNextPostTime = () => {
  const time = moment("6:00 PM", "h:mm A");
  if (moment().isBefore(time)) return time;
  return time.add(1, "days");
};

async function transformPageChunk({ html }: { html: string }) {
  // const image = await nodeHtmlToImage({
  //   html,
  //   encoding: "binary",
  //   transparent: false,
  //   puppeteerArgs: {
  //     args: ["--no-sandbox", "--disable-setuid-sandbox"],
  //   },
  // });
  // return image as Buffer;
  const browser = await puppeteer.launch({
    // https://github.com/puppeteer/puppeteer/issues/2410#issuecomment-1249727413
    args: [
      "--no-sandbox",
      "--disable-setuid-sandbox",
      `--window-size=${resolution.w},${resolution.h}`,
      "--font-render-hinting=none",
      "--force-color-profile=generic-rgb",
      "--disable-gpu",
      "--disable-translate",
      "--disable-extensions",
      "--disable-accelerated-2d-canvas",
      "--deterministic-mode",
      "--disable-skia-runtime-opts",
      "--force-device-scale-factor=1",
      "--js-flags=--random-seed=1157259157",
      "--disable-partial-raster",
      "--use-gl=swiftshader",
      "-–disable-dev-shm-usage",
      "-–no-first-run",
      "--no-sandbox",
      "--disable-web-security",
      "--ignore-certificate-errors",
      "--disable-font-subpixel-positioning",
      "--font-render-hinting=none",
    ],
  });
  const page = await browser.newPage();
  await page.goto("https://developer.chrome.com/");
}

export type messageDataType = NonNullable<
  Awaited<ReturnType<typeof getMessages>>
>[0];

const authorizationHandle: Handle = async ({ event, resolve }) => {
  // Protect all routes except /api and /auth
  const normPath = normalize(event.url.pathname);
  if (!normPath.startsWith("/auth") && !normPath.startsWith("/api")) {
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
  const normPath = normalize(event.url.pathname);
  if (
    /^\/?api\/[^\/]+\/pages\/\d/.test(normPath) &&
    !event.url.searchParams.has("live")
  ) {
    const res = await resolve(event);
    if (res.status !== 200) {
      return res;
    }
    // const body = await res.text();
    const browser = await puppeteer.launch({
      args: ["--no-sandbox", "--disable-setuid-sandbox"],
      defaultViewport: null,
    });
    const page = await browser.newPage();
    await page.setViewport({
      width: resolution.w,
      height: resolution.h,
      deviceScaleFactor: 1,
    });
    await page.goto(`${env.PRIVATE_HOST}${normPath}?live`, {
      waitUntil: "networkidle0",
    });
    const screenshot = await page.screenshot({
      type: "png",
      encoding: "binary",
      captureBeyondViewport: false,
    });
    // const transformedBody = await transformPageChunk({ html: body });
    const img = await Jimp.read(Buffer.from(screenshot));
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
