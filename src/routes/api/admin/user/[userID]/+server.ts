import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import { changeUserName } from "$lib/../db/dbClient";
import { Role } from "$lib/../constants";

export const POST: RequestHandler = async ({ request, params, locals }) => {
  if (locals.role !== Role.Admin) {
    return json({ error: "Unauthorized" }, { status: 401 });
  }
  const user = params.userID;
  const { name } = await request.json();
  if (!name) {
    return json({ error: "Missing name" }, { status: 400 });
  }
  await changeUserName(user, name);

  return json(true);
};
