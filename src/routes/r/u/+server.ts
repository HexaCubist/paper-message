import { redirect, type RequestHandler } from "@sveltejs/kit";
import { github_release_url } from "../../../constants";

// URL shortener to allow truly tiny QR Codes

export const GET: RequestHandler = ({ url }) => {
    redirect(301, github_release_url);
}