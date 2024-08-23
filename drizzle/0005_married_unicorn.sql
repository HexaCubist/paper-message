CREATE UNIQUE INDEX IF NOT EXISTS "token_index" ON "user" USING btree ("token");--> statement-breakpoint
ALTER TABLE "user" ADD CONSTRAINT "user_token_unique" UNIQUE("token");