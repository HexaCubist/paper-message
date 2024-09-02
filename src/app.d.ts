import type { messageDataType, userDataType, Role } from "./constants";
import type moment from "moment";
// See https://kit.svelte.dev/docs/types#app
// for information about these interfaces
declare global {
  namespace App {
    // interface Error {}
    interface Locals {
      messages: messageDataType[];
      userID: string;
      tokenID: string;
      nextTime: number;
      appMode: AppModes;
      role: Role;
      user: userDataType;
      thisTermMessages: messageDataType[];
    }
    // interface PageData {}
    // interface PageState {}
    // interface Platform {}
  }
}

export {};
