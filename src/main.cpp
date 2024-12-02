#include <Arduino.h>

#include "./user.hpp"
#include "./send-string.hpp"
#include "./read-string.hpp"

#define DATA_PIN 25
#define DEFAULT_SEND_FREQUENCY 50

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
    sendString("Hallo du! Dies ist ein test Satz!", DATA_PIN, DEFAULT_SEND_FREQUENCY);
    delay(2000);
#else
    String value = readString(DATA_PIN, DEFAULT_SEND_FREQUENCY);

    if (value == "")
        Serial.println("ERROR: VALUE IS EMPTY");
    else
        Serial.println(value);
        // Serial.write((char)readByte(DATA_PIN, DEFAULT_SEND_FREQUENCY)); // Corrected "recieved" to "received"
#endif
}