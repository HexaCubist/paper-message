import type { Handle } from "@sveltejs/kit";
import nodeHtmlToImage from "node-html-to-image";
import Jimp from "jimp";
import { encode } from "bmp-ts";

async function transformPageChunk({ html }: { html: string }) {
  const image = await nodeHtmlToImage({
    html,
    encoding: "binary",
    transparent: false,
    // puppeteerArgs: {
  });
  return image as Buffer;
}

export const handle: Handle = async ({ event, resolve }) => {
  if (event.url.pathname.startsWith("/api")) {
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
