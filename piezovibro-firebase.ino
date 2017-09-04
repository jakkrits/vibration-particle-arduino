#include "Particle.h"

// Test Program #2 for Firebase Integration
// Just generates some simple random data once a minute, stores in a per-device table
// using the device name as the key.

#include <math.h> // This is just for cos and M_PI, used in generating random sample data

// Forward declarations
void publishData();
void deviceNameHandler(const char *topic, const char *data);

const unsigned long PUBLISH_PERIOD_MS = 3000;
const unsigned long FIRST_PUBLISH_MS = 1000;
const char *PUBLISH_EVENT_NAME = "vibration-data";

unsigned long lastPublish = FIRST_PUBLISH_MS - PUBLISH_PERIOD_MS;
int nextValue = 1;
String deviceName;

void setup() {
    Serial.begin(9600);

    Particle.keepAlive(45);
    Particle.subscribe("spark/", deviceNameHandler);
    Particle.publish("spark/device/name");
}

void loop() {
    if (millis() - lastPublish >= PUBLISH_PERIOD_MS) {
        lastPublish = millis();
        if (deviceName.length() > 0) {
            publishData();
        }
    }
}

void publishData() {
    // This just publishes some somewhat random data for testing

    // x is a monotonically increasing integer
    int x = nextValue++;

    // double value b is a cosine, so the values will rise and fall nicely over 360 steps
    double y = cos((double)(x % 360) * M_PI / 180.0);

    // c is a random integer
    int z = rand();

    //total
    int total = rand();

    char buf[256];
    snprintf(buf, sizeof(buf), "{\"x\":%d,\"y\":%.3f,\"z\":%d,\"total\":%d,\"n\":\"%s\"}", x, y, z, total, deviceName.c_str());
    Serial.printlnf("publishing %s", buf);
    Particle.publish(PUBLISH_EVENT_NAME, buf, PRIVATE);
}

void deviceNameHandler(const char *topic, const char *data) {
    deviceName = data;
}
