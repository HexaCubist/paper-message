ALTER TABLE "user" DROP CONSTRAINT "user_token_unique";--> statement-breakpoint
DROP INDEX IF EXISTS "token_index";--> statement-breakpoint
ALTER TABLE "user" ADD COLUMN "deviceToken" uuid DEFAULT gen_random_uuid() NOT NULL;--> statement-breakpoint
CREATE UNIQUE INDEX IF NOT EXISTS "token_index" ON "user" USING btree ("deviceToken");--> statement-breakpoint
ALTER TABLE "user" DROP COLUMN IF EXISTS "token";