import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import { clearMessage } from "../../../../db/dbClient";
import { Role } from "../../../../hookTypes";

export const DELETE: RequestHandler = async ({ request, params, locals }) => {
  if (locals.role !== Role.Admin) {
    return json({ error: "Unauthorized" }, { status: 401 });
  }
  const messageID = parseInt(params.messageID);
  await clearMessage(messageID);
  return json(true);
};
