import type { userDataType } from "../api/[user]/+server";
import type { LayoutLoad } from "./$types";

export const load: LayoutLoad = async ({ fetch }) => {
  const user = 0;
  // .then((r) => r.json())) as userDataType
  return {
    user: await fetch(`/api/${user}`).then((r) => r.json()),
  };
};
