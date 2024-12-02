#pragma once
#include <Arduino.h>

void rawSendByte(uint8_t value, int pin, int delayTime)
{
    // Send start signal
    digitalWrite(pin, HIGH);
    delayMicroseconds(delayTime);

    unsigned long startTime = micros() + delayTime;

    // Send each bit (LSB-first)
    for (uint8_t i = 0; i < 8; i++)
    {
        bool bit = (value & (1 << i)) != 0; // Extract bit `i`
        digitalWrite(pin, bit ? HIGH : LOW);

        // Wait for the bit duration
        unsigned long bitEndTime = startTime + (i * delayTime);
        while (micros() < bitEndTime)
            ;
    }

    // Send end signal
    digitalWrite(pin, LOW);
    delayMicroseconds(delayTime);
}