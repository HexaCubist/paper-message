import Jimp from "jimp";
import { resolution } from "../constants";

export function bufferToImage(buf: Buffer): string {
  return `data:image/png;base64,${buf.toString("base64")}`;
}

export async function imageToBuffer(image: string): Promise<Buffer> {
  if (!image.startsWith("data:image/png;base64,")) {
    throw new Error("Invalid image data");
  }
  if (image.length > 1e6) {
    throw new Error("Image too large");
  }
  const imageData = Buffer.from(image.split(",")[1], "base64");
  const jimpImg = await Jimp.read(imageData);
  if (
    jimpImg.getWidth() !== resolution.w ||
    jimpImg.getHeight() !== resolution.h
  ) {
    jimpImg.resize(resolution.w, resolution.h, Jimp.RESIZE_NEAREST_NEIGHBOR);
  }
  jimpImg.threshold({ max: 150 });
  return await jimpImg.getBufferAsync(Jimp.MIME_PNG);
}
