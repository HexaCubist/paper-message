import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";

export const POST: RequestHandler = async ({ request, params, locals }) => {
  if (locals.nextTime > Date.now()) {
    return json({ error: "Rate limited" }, { status: 429 });
  }
  const { message } = await request.json();
  const user = params.user;
  //TODO: Store in redis
  await new Promise<void>((r) =>
    setTimeout(() => {
      r();
    }, 300)
  );
  return json(true);
};
