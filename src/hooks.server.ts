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

export interface messageDataType {
  message: string;
  from: string;
  page?: number;
  date?: string;
}

const messages: messageDataType[] = [
  {
    message: "Hello, world!",
    from: "SvelteKit",
    page: 1,
    date: new Date().toISOString(),
  },
  {
    message: "Message 2",
    from: "Sender 2",
    page: 2,
    date: new Date().toISOString(),
  },
  {
    message: "Message 3",
    from: "The Third Sender",
    page: 3,
    date: new Date().toISOString(),
  },
];

export const handle: Handle = async ({ event, resolve }) => {
  event.locals.messages = messages;
  event.locals.userID = "12345";
  event.locals.nextTime = Date.now() + 5000;
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
