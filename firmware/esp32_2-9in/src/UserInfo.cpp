#include "UserInfo.h"



bool parseUserInfo(const char* json, UserInfo *ui) {
    StaticJsonDocument<250> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return false;
    }

    strcpy(ui->version, doc["version"]);
    ui->last_message_at = doc["last_message_at"];
    ui->message_count = doc["message_count"];
    ui->total_pages = doc["total_pages"];
    strcpy(ui->userID, doc["userID"]);

    return true;
}

// Request json from endpoint:
// https://rsb.nz/api/<token>
bool getUserInfo(const char* api_token, UserInfo *ui) {
	// path + user_token + pagesEndpoint
	char full_path [128];

	if (!snprintf(full_path, 128, "https://%s/api/%s", rsb_host, api_token)) {
		// Buffer too small
		Serial.println("Buffer too small");
		return false;
	}

    HTTPClient& http = HttpClientSingleton::getInstance();


	http.setUserAgent("ESP32_Zac_EPaper");
	http.setReuse(true);
	
	if (!http.begin(full_path)) {
        Serial.println("Failed to connect to server");
        return false;
    }

    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK) {
        Serial.print("Failed to get user info, response code: ");
        Serial.println(httpCode);
        
        return false;
    }

    String payload = http.getString();

    http.end();

    return parseUserInfo(payload.c_str(), ui);
}
