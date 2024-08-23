import type { getMessages } from "./db/dbClient";

export const resolution = {
  w: 296,
  h: 128,
};

export enum Role {
  Admin = "admin",
  User = "user",
  Guest = "guest",
}

export type messageDataType = NonNullable<
  Awaited<ReturnType<typeof getMessages>>
>[0];

export enum AppModes {
  LimitSends,
  LimitArrives,
}
