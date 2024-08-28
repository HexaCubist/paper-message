import { sveltekit } from "@sveltejs/kit/vite";
import { defineConfig } from "vite";
import packageJson from "./package.json";

export default defineConfig({
  plugins: [sveltekit()],
  define: {
    APP_VERSION: JSON.stringify(packageJson.version),
  },
  optimizeDeps: {
    include: ["@xterm/xterm"],
  },
});
