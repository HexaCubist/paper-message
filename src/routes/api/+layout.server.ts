import { env } from "$env/dynamic/public";
import { github_release_url } from "../../constants";
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
    page: parseInt(page!),
    messages: locals.messages,
    qr: await QRCode.toDataURL(env.PUBLIC_HOST, {
      errorCorrectionLevel: "L",
      margin: 0,
      scale: 1,
      color: {
        dark: "#ffffff",
        light: "#000000",
      },
    }),
    wifi_ip: await QRCode.toDataURL("http://192.168.4.1/", {
      errorCorrectionLevel: "L",
      margin: 0,
      scale: 1,
      color: {
        dark: "#000000",
        light: "#ffffff",
      },
    }),
    update_details: await QRCode.toDataURL(`${env.PUBLIC_HOST}/r/u`, {
      errorCorrectionLevel: "L",
      margin: 0,
      scale: 1,
      color: {
        dark: "#000000",
        light: "#ffffff",
      },
    }),

  };
};
