import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import { clearMessages, createMessage, getUser } from "../../../../db/dbClient";
import { Role } from "../../../../hookTypes";

export const POST: RequestHandler = async ({ request, params, locals }) => {
  if (locals.role !== Role.Admin) {
    return json({ error: "Unauthorized" }, { status: 401 });
  }
  await clearMessages();
  return json(true);
};
