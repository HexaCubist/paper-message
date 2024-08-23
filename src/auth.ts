import { SvelteKitAuth } from "@auth/sveltekit";
import { DrizzleAdapter } from "@auth/drizzle-adapter";
import { db } from "./db/dbClient";
import Google from "@auth/sveltekit/providers/google";
import { env } from "$env/dynamic/private";

export const { handle, signIn, signOut } = SvelteKitAuth({
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
      if (account.provider === "google") {
        console.log("Google account", profile.email);
        return (
          profile.email_verified &&
          env.EMAIL_WHITELIST.toLowerCase()
            .split(",")
            .includes(profile.email.toLowerCase())
        );
      }
      return true; // Do different verification for other providers that don't have `email_verified`
    },
  },
});
