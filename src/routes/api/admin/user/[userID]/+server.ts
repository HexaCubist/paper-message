import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import { changeCurrentStreak, changeUserName } from "$lib/../db/dbClient";
import { Role } from "$lib/../constants";

export const POST: RequestHandler = async ({ request, params, locals }) => {
  if (locals.role !== Role.Admin) {
    return json({ error: "Unauthorized" }, { status: 401 });
  }
  const user = params.userID;
  const { name, current_streak, reset_date } = await request.json();
  if (name) {
    await changeUserName(user, name);
  } else if (current_streak) {
    await changeCurrentStreak(user, current_streak, reset_date);
  } else {
    return json({ error: "Missing data" }, { status: 400 });
  }

  return json(true);
};
