ALTER TABLE "messages" ADD COLUMN "authorId" text;--> statement-breakpoint
ALTER TABLE "messages" ADD COLUMN "createdAt" timestamp;--> statement-breakpoint
DO $$ BEGIN
 ALTER TABLE "messages" ADD CONSTRAINT "messages_authorId_user_id_fk" FOREIGN KEY ("authorId") REFERENCES "public"."user"("id") ON DELETE cascade ON UPDATE no action;
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;
