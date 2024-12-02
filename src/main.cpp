// filepath: src/main.cpp
#include <Arduino.h>

#include "./user.hpp"
#include "./send-byte.hpp"
#include "./read-byte.hpp"

#define DATA_PIN 25
#define DEFAULT_SEND_FREQUENCY 50000

void setup()
{
    Serial.begin(115200);
    Serial.println(IS_SENDING ? "SENDER" : "RECEIVER"); // Corrected typo in "RECEIVER"

    pinMode(DATA_PIN, IS_SENDING ? OUTPUT : INPUT);
    if (IS_SENDING)
        digitalWrite(DATA_PIN, LOW); // Set initial state
}

void loop()
{
#if IS_SENDING
    sendByte(123, DATA_PIN, DEFAULT_SEND_FREQUENCY);
    delay(1000);
#else
    Serial.println("received: " + String(readByte(DATA_PIN, DEFAULT_SEND_FREQUENCY))); // Corrected "recieved" to "received"
#endif
}
