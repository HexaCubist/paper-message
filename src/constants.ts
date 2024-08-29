import { env } from "$env/dynamic/public";
import moment from "moment-timezone/builds/moment-timezone-with-data-10-year-range.js";
import type { getMessages, getUser } from "./db/dbClient";

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
export type userDataType = NonNullable<Awaited<ReturnType<typeof getUser>>>;

export enum AppModes {
  LimitSends,
  LimitArrives,
}

export const APP_MODE = env.PUBLIC_DELIVER_TIME
  ? AppModes.LimitArrives
  : AppModes.LimitSends;

export const getNextPostTime = () => {
  if (APP_MODE === AppModes.LimitSends) return moment();
  let time = moment.tz(env.PUBLIC_DELIVER_TIME, "h:mm A", SERVER_TIMEZONE);
  time = time.tz(moment.tz.guess());
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
