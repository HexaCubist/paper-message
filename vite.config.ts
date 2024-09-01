import { sveltekit } from "@sveltejs/kit/vite";
import { defineConfig } from "vite";
import packageJson from "./package.json";
import { configDotenv } from "dotenv";
configDotenv();

export default defineConfig({
  plugins: [sveltekit()],
  define: {
    APP_VERSION: JSON.stringify(packageJson.version),
    SERVER_TIMEZONE: JSON.stringify(process.env.TZ),
  },
  optimizeDeps: {
    include: ["@xterm/xterm"],
  },
  ssr: {
    noExternal: ["@curtishughes/pixel-editor"],
  },
  build: {
    target: "modules",
  },
});
