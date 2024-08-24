#include <WifiController.h>

WiFiManagerParameter* custom_token;
char api_token[64] = "YOUR_API_TOKEN";
bool shouldSaveConfig = false;

void configModeCallback(WiFiManager* myWiFiManager) {
    Serial.println("config mode");
}

void saveConfigCallback() {
    Serial.println("Should save config now");
    shouldSaveConfig = true;
}

bool wifiInit(bool force_config) {
    if (!EEPROM.begin(512)) {
        Serial.println("Failed to initialise EEPROM");
        return false;
    }
    Serial.println(EEPROM.readString(0));

    WiFiManager wm;
    wm.setSaveConfigCallback(saveConfigCallback);

    custom_token = new WiFiManagerParameter("api_token", "RSB API Token (visit rsb.nz to get!)", api_token, 64);

    wm.addParameter(custom_token);
    wm.setAPCallback(configModeCallback);

    bool res;
    if (force_config)  {
        res = wm.startConfigPortal("RSB-Device");
    } else {
        res = wm.autoConnect("RSB-Device");
    }

    if (!res) {
        Serial.println("Failed to connect");
    } else {
        Serial.println("connected...yay :)");
        // strcpy(api_token, customParam.getValue());
        strcpy(api_token, custom_token->getValue());
        if (shouldSaveConfig) {
            EEPROM.writeString(0, api_token);
            delay(100);
            Serial.println(EEPROM.readString(0));
        }
    }

    return res;
}

void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

char* getApiToken() {
    return api_token;
}