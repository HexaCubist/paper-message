import { error, json, text } from "@sveltejs/kit";
import type { RequestHandler } from "./$types";
import type { messageDataType } from "../../../constants";

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
  return text(locals.messages[0]?.createdAt.valueOf().toString());
};
