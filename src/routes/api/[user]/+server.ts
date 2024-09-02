import { error, json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import type { messageDataType } from "../../../constants";
import moment from "moment";

const allPages = import.meta.glob("./pages/*/+page.svelte");

export interface userDataType {
  version: string;
  last_message_at: string;
  message_count: number;
  messages?: messageDataType[];
  total_pages: number;
  userID?: string;
  streak?: number;
  highest_streak?: number;
}

export const GET: RequestHandler = ({ url, locals }) => {
  return json({
    version: APP_VERSION,
    last_message_at: locals.messages[0]?.createdAt.valueOf() || "",
    message_count: locals.messages.length,
    total_pages:
      Object.keys(allPages).filter(
        (p) => !p.split("/")[p.split("/").length - 2]?.startsWith("_")
      ).length -
      1 +
      locals.messages.length,
    userID: locals.userID,
    streak: locals.user.current_streak,
    highest_streak: locals.user.highest_streak,
  } as userDataType);
};
