#include "UserInfo.h"


bool parseUserInfo(const char* json, UserInfo *ui) {
    StaticJsonDocument<200> doc;
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
    WiFiClientSecure client;

    client.setInsecure();

    if (!client.connect(rsb_host, 443)) {
        Serial.println("Connection failed");
        return false;
    }

    client.print(String("GET ") + path + api_token + " HTTP/1.1\r\n" +
                 "Host: " + rsb_host + "\r\n" +
                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return false;
        }
    }

    // Read all the lines of the reply from server, and ignore them
    while(client.available()){
        String line = client.readStringUntil('\r');

        if (line == "\n") {
            break;
        }
        
    }

    // Parse JSON
    String json = "";
    while(client.available()){
        json += (char)client.read();
    }
    client.stop();

    return parseUserInfo(json.c_str(), ui);
}
