import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import { createMessage, getUser } from "../../../../db/dbClient";
import { Role } from "../../../../constants";

export const POST: RequestHandler = async ({ request, params, locals }) => {
  if (locals.nextTime > Date.now() && locals.role !== Role.Admin) {
    return json({ error: "Rate limited" }, { status: 429 });
  }
  const { message, override } = await request.json();
  const user = params.user;
  const foundUser = await getUser(user);
  if (!foundUser) {
    return json({ error: "User not found" }, { status: 404 });
  }
  await createMessage(user, message, locals.role === Role.Admin && override);
  return json(true);
};
