// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID
#define STA_SSID            "YourSSID"              // [Ssid] Wifi SSID

#undef  STA_PASS
#define STA_PASS            "YourWifiPassword"      // [Password] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST           "your-mqtt-server.com"  // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT           1883                    // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER           "YourMqttUser"          // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS           "YourMqttPass"          // [MqttPassword] Optional password

// -- Master parameter control --------------------
#undef  PROJECT
#define PROJECT             "smog"                  // PROJECT is used as the default topic delimiter

// -- MQTT topics ---------------------------------
// Example "tasmota/bedroom/%topic%/%prefix%/" up to 80 characers
#define MQTT_FULLTOPIC         "%prefix%/%topic%/"  // [FullTopic] Subscribe and Publish full topic name - Legacy topic

// %prefix% token options
#define SUB_PREFIX             "cmnd"               // [Prefix1] Sonoff devices subscribe to %prefix%/%topic% being SUB_PREFIX/MQTT_TOPIC and SUB_PREFIX/MQTT_GRPTOPIC
#define PUB_PREFIX             "stat"               // [Prefix2] Sonoff devices publish to %prefix%/%topic% being PUB_PREFIX/MQTT_TOPIC
#define PUB_PREFIX2            "tele"               // [Prefix3] Sonoff devices publish telemetry data to %prefix%/%topic% being PUB_PREFIX2/MQTT_TOPIC/UPTIME, POWER and TIME
                                                    // May be named the same as PUB_PREFIX
// %topic% token options (also ButtonTopic and SwitchTopic)
// #define MQTT_TOPIC             PROJECT           // [Topic] (unique) MQTT device topic, set to 'PROJECT "_%06X"' for unique topic including device MAC address
// #define MQTT_GRPTOPIC          "sonoffs"         // [GroupTopic] MQTT Group topic
// #define MQTT_BUTTON_TOPIC      "0"               // [ButtonTopic] MQTT button topic, "0" = same as MQTT_TOPIC, set to 'PROJECT "_BTN_%06X"' for unique topic including device MAC address
// #define MQTT_SWITCH_TOPIC      "0"               // [SwitchTopic] MQTT button topic, "0" = same as MQTT_TOPIC, set to 'PROJECT "_SW_%06X"' for unique topic including device MAC address
// #define MQTT_CLIENT_ID         "DVES_%06X"       // [MqttClient] Also fall back topic using Chip Id = last 6 characters of MAC address

// -- MQTT - Publish ------------------------------
#define STAT_PERIOD            300                  // [StatPeriod] Publish interval (0 = disable, 10 - 3600 seconds)

// -- MQTT - Telemetry ----------------------------
#define TELE_ON_POWER          0                    // [SetOption59] Send information about connection on power
