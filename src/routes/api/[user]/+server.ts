import { error, json } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import type { messageDataType } from "../../../hooks.server";

const allPages = import.meta.glob("./pages/*/+page.svelte");

export interface userDataType {
  version: string;
  last_message_at: string;
  message_count: number;
  messages?: messageDataType[];
  total_pages: number;
  userID?: string;
}

export const GET: RequestHandler = ({ url, locals }) => {
  return json({
    version: APP_VERSION,
    last_message_at: locals.messages[0]?.createdAt || "",
    message_count: locals.messages.length,
    total_pages: Object.keys(allPages).length - 1 + locals.messages.length,
    userID: locals.userID,
  } as userDataType);
};
