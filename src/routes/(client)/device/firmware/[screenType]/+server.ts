import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";

export const GET: RequestHandler = async ({
  request,
  params,
  locals,
  fetch,
}) => {
  // CORS Proxy
  if (!["BW", "BWR"].includes(params.screenType.toUpperCase())) {
    return json({ error: "Invalid screen type" }, { status: 400 });
  }
  let downloadURL = `https://github.com/HexaCubist/paper-message/releases/latest/download/esp32-${params.screenType.toUpperCase()}-firmware-merged.bin`;
  const res = await fetch(downloadURL);
  console.log(downloadURL);
  const data = await res.arrayBuffer();
  const buffer = Buffer.from(data);
  return new Response(buffer, {
    headers: {
      "Content-Type": "application/octet-stream",
      "Content-Disposition": `attachment; filename="esp32-${params.screenType.toUpperCase()}-firmware-merged.bin"`,
    },
  });
};
