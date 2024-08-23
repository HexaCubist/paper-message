ALTER TABLE "messages" ALTER COLUMN "createdAt" SET DEFAULT now();--> statement-breakpoint
ALTER TABLE "messages" ALTER COLUMN "createdAt" SET NOT NULL;