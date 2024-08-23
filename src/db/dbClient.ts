import { pgTable, serial, text, varchar } from "drizzle-orm/pg-core";
import { and, desc, eq, gt, lte } from "drizzle-orm";
import { env } from "$env/dynamic/private";
import postgres from "postgres";
import * as schema from "./schema";
import { drizzle } from "drizzle-orm/postgres-js";
import "dotenv/config";
import {
  APP_MODE,
  AppModes,
  getLastPostTime,
  getNextPostTime,
} from "../constants";

const pool = postgres(process.env.AUTH_DRIZZLE_URL!, { max: 1 });

export const db = drizzle(pool, { schema });

export const getUser = async (id: string) => {
  const foundUser = await db.query.users.findFirst({
    where: eq(schema.users.id, id),
  });
  return foundUser;
};

export const getUserFromEmail = async (email: string) => {
  const foundUser = await db.query.users.findFirst({
    where: eq(schema.users.email, email),
  });
  return foundUser;
};

export const getMessages = async (
  id?: string,
  startDate = getLastPostTime().toDate(),
  admin = false
) => {
  const messages = await db.query.messages.findMany({
    where: and(
      // Get filter based on id and startDate
      ...[
        id ? eq(schema.messages.authorId, id) : undefined,
        gt(schema.messages.createdAt, startDate),
      ].filter(Boolean)
    ),
    orderBy: desc(schema.messages.createdAt),
    limit: 20,
    with: {
      author: {
        columns: {
          name: true,
          id: true,
          image: true,
        },
      },
    },
  });
  return messages;
};

export const createMessage = async (id: string, message: string) => {
  await db.insert(schema.messages).values({
    message,
    authorId: id,
  });
  console.log("Message created");
};

export const clearMessages = async (userID?: string) => {
  if (userID !== undefined)
    await db
      .delete(schema.messages)
      .where(eq(schema.messages.authorId, userID));
  else await db.delete(schema.messages);
};

export const clearMessage = async (messageID: number) => {
  await db.delete(schema.messages).where(eq(schema.messages.id, messageID));
};

process.on("sveltekit:shutdown", async (reason) => {
  await pool.end();
});
