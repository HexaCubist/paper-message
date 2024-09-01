import type { Tool, Color, Point, Pixel } from "@curtishughes/pixel-editor";
import { PixelEditor } from "@curtishughes/pixel-editor";
import { getLineWithColor } from "@curtishughes/pixel-editor/dist/utils/getLineWithColor";

const offsetCenter = (radius: number, y: number) => {
  return new Array(radius * 2 + 1)
    .fill(0)
    .map<[number, number]>((_, i) => [i - radius, y]);
};

const sizePixelMap = {
  px: [[0, 0]],
  sm: [...offsetCenter(1, -1), ...offsetCenter(1, 0), ...offsetCenter(1, 1)],
  md: [
    ...offsetCenter(1, -3),
    ...offsetCenter(2, -2),
    ...offsetCenter(3, -1),
    ...offsetCenter(3, 0),
    ...offsetCenter(3, 1),
    ...offsetCenter(2, 2),
    ...offsetCenter(1, 3),
  ],
  lg: [
    ...offsetCenter(2, -4),
    ...offsetCenter(3, -3),
    ...offsetCenter(4, -2),
    ...offsetCenter(4, -1),
    ...offsetCenter(4, 0),
    ...offsetCenter(4, 1),
    ...offsetCenter(4, 2),
    ...offsetCenter(3, 3),
    ...offsetCenter(2, 4),
  ],
};

function pixelToBrushArray(px: Pixel, size: keyof typeof sizePixelMap) {
  return sizePixelMap[size].map((offset) => ({
    x: px.x + offset[0],
    y: px.y + offset[1],
    color: px.color,
  }));
}

function uniquePixelArray(pixels: Pixel[]) {
  const unique = new Map<string, Pixel>();
  pixels.forEach((px) => {
    unique.set(`${px.x},${px.y}`, px);
  });
  return Array.from(unique.values());
}

export default class Brush implements Tool {
  private dragging = false;

  private prevPosition!: Point;

  constructor(
    private color?: Color,
    public size: keyof typeof sizePixelMap = "md"
  ) {}

  public handlePointerUp() {
    this.dragging = false;
  }

  public handlePointerDown(position: Point, editor: PixelEditor) {
    this.dragging = true;
    this.prevPosition = position;
    const px = pixelToBrushArray(
      { x: position.x, y: position.y, color: this.color },
      this.size
    );
    editor.set(px);
  }

  public handlePointerMove(position: Point, editor: PixelEditor) {
    if (this.dragging) {
      const line = getLineWithColor(
        this.prevPosition.x,
        this.prevPosition.y,
        position.x,
        position.y,
        this.color
      );
      this.prevPosition = position;
      editor.set(
        uniquePixelArray(line.flatMap((px) => pixelToBrushArray(px, this.size)))
      );
      editor.history.squash();
    }
  }
}
