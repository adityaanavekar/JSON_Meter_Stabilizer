#include <Arduino.h>
#include <cstring>

#include "json_serializer.h"

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("ESP32 JSON Serializer Demo");

    // -------- Create sample gateway data --------
    GatewayData gateway = {0};

    strcpy(gateway.gatewayId, "gateway_1234");
    strcpy(gateway.date, "1970-01-01");
    strcpy(gateway.deviceType, "stromleser");
    gateway.interval_minutes = 15;
    gateway.total_readings = 1;

    gateway.device_count = 1;

    // -------- Device data --------
    DeviceReading* dev = &gateway.devices[0];

    strcpy(dev->media, "water");
    strcpy(dev->meter, "waterstarm");
    strcpy(dev->deviceId, "stromleser_50898527");
    strcpy(dev->unit, "m3");

    dev->data_count = 1;

    // -------- Data point --------
    DataPoint* p = &dev->data[0];

    strcpy(p->timestamp, "1970-01-01 00:00");
    strcpy(p->meter_datetime, "1970-01-01 00:00");
    p->total_m3 = 107.752;
    strcpy(p->status, "OK");

    // -------- JSON buffer --------
    char json_buffer[1024];

    int result = serialize_to_json(
        &gateway,
        json_buffer,
        sizeof(json_buffer)
    );

    if (result < 0) {
        Serial.println("ERROR: JSON serialization failed");
    } else {
        Serial.println("Generated JSON:");
        Serial.println(json_buffer);
    }
}

void loop() {
    // Nothing to do
}
