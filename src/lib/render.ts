// This script handles the rendering of pages into a .bmp image the ESP can render.
// It makes use of puppeteer to render the page and then encodes the image into a .bmp file.
// Puppeteer is great, but it's pretty heavy. It's not a problem for this use case, but it's something to keep in mind.

import type { Handle } from "@sveltejs/kit";
import normalize from "path-normalize";
import puppeteer from "puppeteer";
import { resolution } from "../constants";
import { env } from "$env/dynamic/private";
import Jimp from "jimp";
import { encode } from "bmp-ts";

export const renderHandle: Handle = async ({ event, resolve }) => {
  const normPath = normalize(event.url.pathname);
  console.log("Jasper, please fix this: (normPath, path)", normPath, event.url);
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
