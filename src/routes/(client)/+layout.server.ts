import type { userDataType } from "../api/[user]/+server";
import type { LayoutServerLoad } from "./$types";

export const load: LayoutServerLoad = async ({ fetch, locals }) => {
  const user = 0;
  // .then((r) => r.json())) as userDataType
  return {
    user: (await fetch(`/api/${user}`).then((r) => r.json())) as userDataType,
    nextTime: locals.nextTime,
  };
};
