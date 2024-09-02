import { pgTable, serial, text, varchar } from "drizzle-orm/pg-core";
import { and, count, desc, eq, gt, lte, max, min, sql } from "drizzle-orm";
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
  type userDataType,
} from "../constants";
import moment from "moment-timezone/builds/moment-timezone-with-data-10-year-range.js";
import { bufferToImage } from "./imageSanitize";

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

export const getUserFromToken = async (token: string) => {
  const foundUser = await db.query.users.findFirst({
    where: eq(schema.users.deviceToken, token),
  });
  return foundUser;
};

export const getAllUsers = async () => {
  const users = await db.query.users.findMany({
    columns: {
      id: true,
      name: true,
      email: true,
      image: true,
    },
    with: {
      messages: {
        columns: {
          id: true,
        },
      },
    },
  });
  return users.map((u) => ({
    ...u,
    messages: u.messages.length,
  }));
};

export const getMessages = async (
  id?: string,
  startDate = getLastPostTime().subtract(1, "day").toDate(),
  endDate = APP_MODE === AppModes.LimitArrives
    ? getLastPostTime().toDate()
    : new Date()
) => {
  const messages = await db.query.messages.findMany({
    where: and(
      // Get filter based on id and startDate
      ...[
        id ? eq(schema.messages.authorId, id) : undefined,
        gt(schema.messages.createdAt, startDate),
        lte(schema.messages.createdAt, endDate),
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
  return messages.map((m) => ({
    ...m,
    image: m.image ? bufferToImage(m.image) : undefined,
  }));
};

export const createMessage = async (
  id: string,
  override?: string,
  message?: string,
  image?: Buffer
) => {
  await db.insert(schema.messages).values({
    message,
    image,
    authorId: id,
    createdAt: override ? moment().subtract(1, "day").toDate() : undefined,
  });
  console.log("Message created");
  // See if we need to update streaks
  const user = await getUser(id);
  if (user) {
    // If streak is not today, update streak
    const lastStreak = user.last_streak_day;
    const today = moment().startOf("day");
    if (today.isSame(lastStreak)) return;
    // If streak is yesterday, add to streak, else reset streak
    const streakWindow = today.subtract(1, "day");
    const newStreak = streakWindow.isBefore(lastStreak)
      ? 1
      : user.current_streak + 1;
    // Update streaks
    await db
      .update(schema.users)
      .set({
        current_streak: newStreak,
        highest_streak: Math.max(newStreak, user.highest_streak),
        last_streak_day: today.toDate(),
      })
      .where(eq(schema.users.id, id));
  }
};

export const editMessage = async (
  authorId: string,
  messageID: number,
  override?: string,
  message?: string,
  image?: Buffer
) => {
  await db
    .update(schema.messages)
    .set({
      message,
      image,
      authorId: authorId,
      createdAt: override ? moment().subtract(1, "day").toDate() : undefined,
    })
    .where(eq(schema.messages.id, messageID));
  console.log("Message edited");
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

// Users list
export async function userEmailList(
  resultType:
    | (keyof userDataType | "hasSent")[]
    | (keyof userDataType | "hasSent") = "name"
) {
  const allUsers = (
    await db.query.users.findMany({
      with: {
        messages: {
          columns: {
            id: true,
          },
          where: gt(schema.messages.createdAt, getLastPostTime().toDate()),
        },
      },
    })
  ).map(({ messages, ...u }) => ({
    ...u,
    current_streak: moment()
      .subtract(1, "day")
      .isSameOrBefore(u.last_streak_day, "day")
      ? u.current_streak
      : 0,
    hasSent: messages.length > 0,
  }));
  if (Array.isArray(resultType)) {
    return allUsers.map((u) => resultType.map((r) => u[r]));
  } else {
    return allUsers.map((u) => u[resultType]);
  }
}

// Admin: Change User Name
export const changeUserName = async (userID: string, newName: string) => {
  await db
    .update(schema.users)
    .set({
      name: newName,
    })
    .where(eq(schema.users.id, userID));
};

// On server launch, we should also make sure all users have a token
// This is to ensure that all users can access the API
// This is a one-time operation
export const ensureTokens = async () => {
  const users = await db.query.users.findMany();
  for (const user of users) {
    if (!user.deviceToken) {
      console.log("Creating token for user", user.id);
      await db
        .update(schema.users)
        .set({
          deviceToken: crypto.randomUUID(),
        })
        .where(eq(schema.users.id, user.id));
    }
  }
};
