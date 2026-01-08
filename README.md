# JSON Meter Data Serializer (ESP32 – Arduino)

## Overview
This project implements a small embedded-friendly C++ library that converts structured smart-meter data into a predefined JSON format.  
The goal is to simulate a part of a smart-meter / gateway data pipeline where internal meter data is serialized and sent to a backend system.

Radio communication, encryption, OMS, and real meter hardware are intentionally not included.

---

## Platform & Language
- **Target Platform:** ESP32 (Arduino framework)
- **Language:** C++

**Why ESP32 + Arduino?**  
ESP32 is commonly used in IoT and gateway applications. The Arduino framework makes it easy to demonstrate and test firmware logic.  
The core serialization code is hardware-independent and can run on other microcontrollers like STM32 without changes.

---

## Project Structure
json_meter_serializer_esp32/
├── meter_data.h
├── json_serializer.h
├── json_serializer.cpp
├── json_meter_serializer_esp32.ino
└── README.md


- `meter_data.h` → Data structures  
- `json_serializer.h` → Public API  
- `json_serializer.cpp` → JSON serialization logic  
- `json_meter_serializer_esp32.ino` → Demo application  

---

## How It Works
1. Meter and gateway data is stored in C++ structures  
2. The serializer converts this data into JSON  
3. JSON is written into a caller-provided buffer  
4. The demo prints the JSON output

No external JSON libraries are used, and memory usage is fully controlled.

---

## Public API

``cpp
int serialize_to_json(
    const GatewayData* data,
    char* output_buffer,
    int buffer_size
);


* Writes JSON into the given buffer
* Prevents buffer overflow
* Returns number of bytes written
* Returns -1 if an error occurs


JSON Output
* The generated JSON strictly follows the format specified in the assignment, including:
* Fixed field names
* Correct structure 
* Numbers serialized as numbers
* Outer element always being an array


Demo Application
The demo application creates sample meter data, calls the serializer, and prints the generated JSON.
The code was verified by compiling successfully in Arduino IDE.


Design Decisions
* Fixed-size arrays are used for predictable memory usage
* No dynamic memory allocation
* Serialization logic is transport-agnostic
* ESP32-specific code is limited to the demo only
