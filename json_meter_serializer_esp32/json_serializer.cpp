#include "json_serializer.h"
#include <cstdio>
#include <cstdarg>

// Internal helper macro for safe writing
#define SAFE_WRITE(...)                                   \
    do {                                                  \
        int n = snprintf(output + written,                \
                         buffer_size - written,           \
                         __VA_ARGS__);                     \
        if (n < 0 || n >= (buffer_size - written)) {      \
            return -1;                                    \
        }                                                 \
        written += n;                                     \
    } while (0)

int serialize_to_json(
    const GatewayData* data,
    char* output,
    int buffer_size
) {
    if (!data || !output || buffer_size <= 0) {
        return -1;
    }

    int written = 0;

    // ---- JSON start (outer array + object) ----
    SAFE_WRITE("[{");

    SAFE_WRITE("\"gatewayId\":\"%s\",", data->gatewayId);
    SAFE_WRITE("\"date\":\"%s\",", data->date);
    SAFE_WRITE("\"deviceType\":\"%s\",", data->deviceType);
    SAFE_WRITE("\"interval_minutes\":%d,", data->interval_minutes);
    SAFE_WRITE("\"total_readings\":%d,", data->total_readings);

    // ---- values object ----
    SAFE_WRITE("\"values\":{");
    SAFE_WRITE("\"device_count\":%d,", data->device_count);
    SAFE_WRITE("\"readings\":[");

    // ---- device list ----
    for (int i = 0; i < data->device_count; i++) {
        const DeviceReading* dev = &data->devices[i];


        SAFE_WRITE("{");
        SAFE_WRITE("\"media\":\"%s\",", dev->media);
        SAFE_WRITE("\"meter\":\"%s\",", dev->meter);
        SAFE_WRITE("\"deviceId\":\"%s\",", dev->deviceId);
        SAFE_WRITE("\"unit\":\"%s\",", dev->unit);
        SAFE_WRITE("\"data\":[");

        // ---- data points ----
        for (int j = 0; j < dev->data_count; j++) {
            const DataPoint* p = &dev->data[j];


            SAFE_WRITE("{");
            SAFE_WRITE("\"timestamp\":\"%s\",", p->timestamp);
            SAFE_WRITE("\"meter_datetime\":\"%s\",", p->meter_datetime);
            SAFE_WRITE("\"total_m3\":%.3f,", p->total_m3);
            SAFE_WRITE("\"status\":\"%s\"", p->status);
            SAFE_WRITE("}");

            if (j < dev->data_count - 1) {
                SAFE_WRITE(",");
            }
        }

        SAFE_WRITE("]}");

        if (i < data->device_count - 1) {
            SAFE_WRITE(",");
        }
    }

    // ---- close all objects ----
    SAFE_WRITE("]}}]");

    return written;
}
