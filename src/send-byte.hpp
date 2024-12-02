#pragma once
#include <Arduino.h>

void sendByte(uint8_t value, int pin, int delayTime)
{
    digitalWrite(pin, HIGH);
    // Record the start time once at the beginning
    unsigned long startTime = micros();

    unsigned long targetTime = startTime + delayTime;

    while (micros() < targetTime)
        ;

    // Send each bit, starting with the MSB
    for (uint8_t i = 0; i < 8; i++)
    {
        // Extract the bit at position `i`
        bool bit = (value & (1 << i)) != 0;

        // Write HIGH or LOW to the pin
        digitalWrite(pin, bit ? HIGH : LOW);

        // Calculate the target time for this bit
        unsigned long targetTime = startTime + ((i + 1) * delayTime);

        // Wait until it's time to send the current bit
        while (micros() < targetTime)
        {
        }
    }
    digitalWrite(pin, LOW);
}
