/** @type {import('tailwindcss').Config} */
export default {
  content: ["./src/**/*.{html,svelte,js,ts}"],
  theme: {
    fontSize: {
      sm: ["8px", "12px"],
      base: ["16px", "20px"],
      lg: ["24px", "28px"],
      xl: ["32px", "36px"],
    },
    extend: {},
  },
  plugins: [require("daisyui")],
  daisyui: {
    themes: ["lofi"],
  },
};
