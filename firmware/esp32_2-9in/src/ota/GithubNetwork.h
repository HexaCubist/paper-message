#pragma once


#include <WiFiClientSecure.h>
#include <Update.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

typedef HTTPUpdate Updater;

#include "semver.h"

String get_updated_base_url_via_api(WiFiClientSecure wifi_client, String release_url);
String get_updated_base_url_via_redirect(WiFiClientSecure &wifi_client, String release_url);
String get_redirect_location(WiFiClientSecure &wifi_client, String initial_url);

void print_update_result(Updater updater, HTTPUpdateResult result, const char *TAG);

bool update_required(semver_t _new_version, semver_t _current_version);

void synchronize_system_time();

extern const char *github_certificate;
