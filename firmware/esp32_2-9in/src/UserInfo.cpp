#include "UserInfo.h"


UserInfo parseUserInfo(const char* json) {
    UserInfo ui;

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return ui;
    }

    strcpy(ui.version, doc["version"]);
    ui.last_message_at = doc["last_message_at"];
    ui.message_count = doc["message_count"];
    ui.total_pages = doc["total_pages"];
    strcpy(ui.userID, doc["userID"]);

    return ui;
}

// Request json from endpoint:
// https://rsb.nz/api/<token>
UserInfo getUserInfo(const char* api_token) {
    UserInfo ui;
    WiFiClientSecure client;

    client.setInsecure();

    if (!client.connect(rsb_host, 443)) {
        Serial.println("Connection failed");
        return ui;
    }

    client.print(String("GET ") + path + api_token + " HTTP/1.1\r\n" +
                 "Host: " + rsb_host + "\r\n" +
                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return ui;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
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


    ui = parseUserInfo(json.c_str());
    return ui;
}
