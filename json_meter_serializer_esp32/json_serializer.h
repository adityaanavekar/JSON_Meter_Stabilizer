#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "meter_data.h"

// Serializes gateway data into JSON format

int serialize_to_json(
    const GatewayData* data,
    char* output_buffer,
    int buffer_size
);

#endif
