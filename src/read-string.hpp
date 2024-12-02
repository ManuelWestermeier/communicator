#pragma once

#include <Arduino.h>

#include "./read-byte.hpp"

String readString(int pin, int delayTime)
{
    uint8_t receivedHash = readByte(pin, delayTime);
    int length = (readByte(pin, delayTime) << 8) + readByte(pin, delayTime);

    // basic hash for the length
    uint8_t lengthHash = ((length >> 8) & 0x0F) ^ (length & 0x0F);

    if (lengthHash != receivedHash)
        return "";

    char *string = new char[length];

    uint8_t dataHash = 0;

    for (uint8_t i = 0; i < length; i++)
    {
        uint8_t value = readByte(pin, delayTime);
        string[i] = value;
        dataHash ^= value;
    }

    uint8_t receivedDataHash = readByte(pin, delayTime);
    if (dataHash != receivedDataHash)
    {
        delete[] string;
        return "";
    }

    String result = String(string, length); // Convert to String
    delete[] string;                        // Free memory
    return result;
}