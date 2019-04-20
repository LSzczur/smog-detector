// -- Setup debug mode - Serial messages will be printed
#define DEBUG_MODE          0

// -- Setup your own Wifi settings  ---------------
#define STA_SSID            "YourSSID"              // [Ssid] Wifi SSID

#define STA_PASS            "YourWifiPassword"      // [Password] Wifi password

#define STA_HOST_NAME       "YourHostName"          // [HostName] Wifi Host name

// -- Setup your own MQTT settings  ---------------
#define MQTT_HOST           "your-mqtt-server.com"  // [MqttHost]

#define MQTT_PORT           1883                    // [MqttPort] MQTT port (10123 on CloudMQTT)

#define MQTT_USER           "YourMqttUser"          // [MqttUser] Optional user

#define MQTT_PASS           "YourMqttPass"          // [MqttPassword] Optional password

// -- Master parameter control --------------------
#define PROJECT             "smog"                  // PROJECT is used as the default topic delimiter

// -- MQTT topics ---------------------------------
// Example "tele/smog/bedroom/" up to 80 characers
#define SUB_FULLTOPIC       "cmnd/smog/"            // [FullTopic] Subscribe full topic name
#define PUB_FULLTOPIC       "stat/smog/"            // [FullTopic] Publish full topic name
#define TELE_FULLTOPIC      "tele/smog/"            // [FullTopic] Telemetry and Publish full topic name

// -- MQTT - Publish ------------------------------
#define STAT_PERIOD            300                  // [StatPeriod] Publish interval (0 = disable, 10 - 3600 seconds)

// -- MQTT - Telemetry ----------------------------
#define TELE_ON_POWER          0                    // [SetOption59] Send information about connection on power
