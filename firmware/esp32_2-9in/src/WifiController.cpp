#include <WifiController.h>

WiFiManagerParameter* custom_token;
char api_token[64] = "YOUR_API_TOKEN";
bool shouldSaveConfig = false;

void configModeCallback(WiFiManager* myWiFiManager) {
    Serial.println("config mode");
    renderStatic(IMAGE_WIFI);
}

void saveConfigCallback() {
    Serial.println("Should save config now");
    shouldSaveConfig = true;
}

bool wifiInit(bool force_config) {
    // if (!EEPROM.begin(512)) {
    //     Serial.println("Failed to initialise EEPROM");
    //     return false;
    // }
    // String saved_token = EEPROM.readString(0);
      if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if ( ! deserializeError ) {

          Serial.println("\nparsed json");
          strcpy(api_token, json["api_token"]);
          if (json["api_token"] != nullptr) {
            Serial.print("Found API token in config file: ");
            Serial.println(api_token);
          } else {
            Serial.println("No API token found in config file");
            force_config = true;
          }
        } else {
          Serial.println("failed to load json config");
          force_config = true;
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
    force_config = true;
  }


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
        strcpy(api_token, custom_token->getValue());
        if (shouldSaveConfig) {
            Serial.println("saving config");
            DynamicJsonDocument json(1024);
            json["api_token"] = api_token;

            File configFile = SPIFFS.open("/config.json", "w");
            if (!configFile) {
                Serial.println("failed to open config file for writing");
            }

            serializeJson(json, Serial);
            serializeJson(json, configFile);
            configFile.close();
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