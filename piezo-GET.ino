#include "Particle.h"

// Test Program #3 for Firebase Integration
// Reads data from the database and prints it to the debug serial port

// Requires the SparkJson library:
// https://github.com/menan/SparkJson
#include "SparkJson/SparkJson.h"

// Forward declarations
void getDataHandler(const char *topic, const char *data);


const unsigned long CHECK_PERIOD_MS = 60000;
const unsigned long FIRST_CHECK_MS = 5000;
const char *CHECK_EVENT_NAME = "vibration-data";

unsigned long lastPublish = FIRST_CHECK_MS - CHECK_PERIOD_MS;
int nextValue = 1;

void setup() {
    Serial.begin(9600);
    Particle.subscribe("hook-response/vibration-data", getDataHandler, MY_DEVICES);
}

void loop() {
    if (millis() - lastPublish >= CHECK_PERIOD_MS) {
        lastPublish = millis();

        Particle.publish(CHECK_EVENT_NAME, "", PRIVATE);
    }
}

void getDataHandler(const char *topic, const char *data) {
    // This isn't particularly efficient; there are too many copies of the data floating
    // around here, but the data is not very large and it's not kept around long so it
    // should be fine.
    StaticJsonBuffer<256> jsonBuffer;
    char *mutableCopy = strdup(data);
    JsonObject& root = jsonBuffer.parseObject(mutableCopy);
    free(mutableCopy);

    // Serial.printlnf("data: %s", data);

    // Because of the way the webhooks work, all data, including numbers, are represented as
    // strings, so we need to convert them back to their native data type here
    int x = atoi(root["x"]);
    float y = atof(root["y"]);
    int z = atoi(root["z"]);
    int total = atoi(root["total"]);

    Serial.printlnf("x=%d y=%.3f z=%d total=%d", x, y, z, total);
}
