import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import { createMessage, getUser } from "../../../../db/dbClient";
import { Role } from "../../../../hookTypes";

export const POST: RequestHandler = async ({ request, params, locals }) => {
  if (locals.nextTime > Date.now() && locals.role !== Role.Admin) {
    return json({ error: "Rate limited" }, { status: 429 });
  }
  const { message } = await request.json();
  const user = params.user;
  const foundUser = await getUser(user);
  if (!foundUser) {
    return json({ error: "User not found" }, { status: 404 });
  }
  await createMessage(user, message);
  return json(true);
};
