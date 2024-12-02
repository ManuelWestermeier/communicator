#include <Arduino.h>

#include "./user.hpp"
#include "./send-byte.hpp"
#include "./read-byte.hpp"

#define DATA_PIN 25
#define DEFAULT_SEND_FREQUENCY 100

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
    String text = "Hallo du! Dies ist ein test Satz!\n";

    for (uint8_t i = 0; i < text.length(); i++)
    {
        sendByte(text[i], DATA_PIN, DEFAULT_SEND_FREQUENCY);
        delayMicroseconds(DEFAULT_SEND_FREQUENCY);
    }

    delay(500);
#else
    Serial.write((char)readByte(DATA_PIN, DEFAULT_SEND_FREQUENCY)); // Corrected "recieved" to "received"
#endif
}