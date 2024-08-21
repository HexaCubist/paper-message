import type { LayoutLoad } from "./$types";
export const load: LayoutLoad = async ({ params, url, setHeaders }) => {
  let page = params.page;
  if (!page) {
    // Calculate page from last segment of URL
    page = url.pathname.split("/").filter(Boolean).pop();
  }
  const messages = [
    { from: "Alice", text: "Hello, Bob!" },
    { from: "Bob", text: "Hi, Alice!" },
    { from: "Alice", text: "How are you?" },
    // { from: "Bob", text: "I'm good, thanks!" },
  ];
  setHeaders({
    messageCount: messages.length.toString(),
  });
  return {
    page: parseInt(page),
    messages,
  };
};
