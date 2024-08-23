import { env } from "$env/dynamic/public";
import moment from "moment";
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

export const APP_MODE = env.PUBLIC_DELIVER_TIME
  ? AppModes.LimitArrives
  : AppModes.LimitSends;

export const getNextPostTime = () => {
  if (APP_MODE === AppModes.LimitSends) return moment();
  const time = moment(env.PUBLIC_DELIVER_TIME, "h:mm A");
  if (moment().isBefore(time)) return time;
  return time.add(1, "days");
};

export const getLastPostTime = () => {
  if (APP_MODE === AppModes.LimitSends)
    return moment()
      .subtract(1, "days")
      .set({ hour: 0, minute: 0, second: 0, millisecond: 0 });
  const time = moment(env.PUBLIC_DELIVER_TIME, "h:mm A");
  if (moment().isAfter(time)) return time;
  return time.subtract(1, "days");
};
