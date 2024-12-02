#pragma once

#include <Arduino.h>
#include "./send-byte.hpp"

void sendString(String text, int pin, int delayTime)
{
    // Get the size of the text
    int length = text.length();

    // Generate a simple hash for the length
    uint8_t lengthHash = ((length >> 8) & 0x0F) ^ (length & 0x0F);
    sendByte(lengthHash, pin, delayTime);
    delayMicroseconds(delayTime);

    // Send the length of the string as two bytes
    sendByte((length >> 8) & 0xFF, pin, delayTime); // Correct mask for high byte
    delayMicroseconds(delayTime);
    sendByte(length & 0xFF, pin, delayTime); // Correct mask for low byte
    delayMicroseconds(delayTime);

    // Initialize the data hash
    uint8_t dataHash = 0;

    // Send the data bytes
    for (int i = 0; i < length; i++)
    {
        uint8_t value = (uint8_t)text[i];
        dataHash ^= value; // Update the hash
        sendByte(value, pin, delayTime);
        delayMicroseconds(delayTime);
    }

    // Send the data hash
    sendByte(dataHash, pin, delayTime);
    delayMicroseconds(delayTime);
}