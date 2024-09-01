#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <GitHubOTA.h>

// This string should correspond to github tag used for Releasing (via. Github Actions)

// Replace your_username/your_repo with your values (ex. axcap/Esp-GitHub-OTA)
// This is a link to repo where your firmware updates will be pulled from
// #define RELEASE_URL "https://api.github.com/repos/your_username/your_repo/releases/latest"

// Use this version of the URL together with init_ota(VERSION, true) under debugging
// to spare yourself from getting timeout from GitHub API
#define RELEASE_URL "https://github.com/HexaCubist/paper-message/releases/latest"

