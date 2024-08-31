import { json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import { createMessage, editMessage, getUser } from "../../../../db/dbClient";
import {
  APP_MODE,
  AppModes,
  getNextPostTime,
  Role,
} from "../../../../constants";

export const POST: RequestHandler = async ({ request, params, locals }) => {
  const existingMessage = locals.thisTermMessages.find(
    (m) => m.authorId === locals.userID
  );
  const hasAlreadyPosted = existingMessage && locals.role !== Role.Admin;
  if (hasAlreadyPosted && APP_MODE === AppModes.LimitSends) {
    return json({ error: "Rate limited" }, { status: 429 });
  }
  const { message, override } = await request.json();
  const user = params.user;
  const foundUser = await getUser(user);
  if (!foundUser) {
    return json({ error: "User not found" }, { status: 404 });
  }
  if (hasAlreadyPosted) {
    // Find existing message
    if (!existingMessage)
      return json({ error: "No message found" }, { status: 404 });
    await editMessage(
      user,
      existingMessage.id,
      message,
      locals.role === Role.Admin && override
    );
  } else {
    await createMessage(user, message, locals.role === Role.Admin && override);
  }
  return json(true);
};
