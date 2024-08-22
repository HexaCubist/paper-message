import type { LayoutServerLoad } from "./$types";
import QRCode from "qrcode";

export const load: LayoutServerLoad = async ({
  params,
  url,
  setHeaders,
  locals,
}) => {
  let page = params.page;
  if (!page) {
    // Calculate page from last segment of URL
    page = url.pathname.split("/").filter(Boolean).pop();
  }
  setHeaders({
    messageCount: locals.messages.length.toString(),
  });
  return {
    page: parseInt(page),
    messages: locals.messages,
    qr: await QRCode.toDataURL("https://paper.zac.nz/", {
      errorCorrectionLevel: "L",
      margin: 0,
      color: {
        dark: "#ffffff",
        light: "#000000",
      },
    }),
  };
};
