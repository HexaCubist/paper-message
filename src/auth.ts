import { SvelteKitAuth } from "@auth/sveltekit";
import { DrizzleAdapter } from "@auth/drizzle-adapter";
import { db } from "./db/dbClient";
import Google from "@auth/sveltekit/providers/google";
import { env } from "$env/dynamic/private";
import { redirect, type Handle } from "@sveltejs/kit";
import normalize from "path-normalize";

const {
  handle: authenticationHandle,
  signIn,
  signOut,
} = SvelteKitAuth({
  adapter: DrizzleAdapter(db),
  trustHost: true,
  providers: [
    Google({
      authorization: {
        params: {
          prompt: "consent",
          access_type: "offline",
          response_type: "code",
        },
      },
    }),
  ],
  callbacks: {
    async signIn({ account, profile }) {
      if (account?.provider === "google") {
        return !!(
          profile?.email_verified &&
          profile.email &&
          env.EMAIL_WHITELIST.toLowerCase()
            .split(",")
            .includes(profile.email.toLowerCase())
        );
      }
      return true; // Do different verification for other providers that don't have `email_verified`
    },
  },
});

export { authenticationHandle, signIn, signOut };

export const authorizationHandle: Handle = async ({ event, resolve }) => {
  // Protect all routes except /api and /auth
  const normPath = normalize(event.url.pathname);
  if (!normPath.startsWith("/auth") && !normPath.startsWith("/api")) {
    const session = await event.locals.auth();
    if (!session) {
      // Redirect to the signin page
      throw redirect(303, "/auth/signin");
    }
  }

  // If the request is still here, just proceed as normally
  return resolve(event);
};
