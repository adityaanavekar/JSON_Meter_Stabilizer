#ifndef METER_DATA_H
#define METER_DATA_H

// -------- Configuration limits (embedded safe) --------
#define MAX_DEVICES         5
#define MAX_DATA_POINTS     5
#define MAX_STRING_LEN      32

struct DataPoint {
    char timestamp[20];       
    char meter_datetime[20];   
    double total_m3;           
    char status[8];            
};

// -------- One device --------
struct DeviceReading {
    char media[MAX_STRING_LEN];
    char meter[MAX_STRING_LEN];
    char deviceId[MAX_STRING_LEN];
    char unit[8];

    int data_count;
    DataPoint data[MAX_DATA_POINTS];
};

// -------- Gateway-level data --------
struct GatewayData {
    char gatewayId[MAX_STRING_LEN];
    char date[11];               
    char deviceType[MAX_STRING_LEN];
    int interval_minutes;
    int total_readings;

    int device_count;
    DeviceReading devices[MAX_DEVICES];
};

#endif
