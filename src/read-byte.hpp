#pragma once
#include <Arduino.h>

uint8_t readByte(int pin, int delayTime)
{
    while (digitalRead(pin) != HIGH)
        ;
    // Record the start time once at the beginning
    unsigned long startTime = micros();

    unsigned long targetTime = startTime + 1.5 * delayTime;

    while (micros() < targetTime)
        ;

    uint8_t value = 0;

    // Read each bit, starting with the LSB
    for (uint8_t i = 0; i < 8; i++)
    {
        if (digitalRead(pin) == HIGH)
        {
            value |= (1 << i); // LSB-first order
        }

        // Calculate the target time for this bit
        unsigned long bitTargetTime = startTime + ((i + 1.5) * delayTime);

        // Wait until it's time to read the current bit
        while (micros() < bitTargetTime)
        {
        }
    }

    return value;
}