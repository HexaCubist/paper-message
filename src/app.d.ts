import type { messageDataType, Role } from "./constants";

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
    }
    // interface PageData {}
    // interface PageState {}
    // interface Platform {}
  }
}

export {};
