#pragma once

#include <Arduino.h>

// bytes
#include "./read-byte.hpp"
#include "./send-byte.hpp"

// strings
#include "./read-string.hpp"
#include "./send-string.hpp"

struct Node
{
    u_int8_t inpPin, outPin;
    int sendDelay;

    Node(u_int8_t _inpPin, u_int8_t _outPin, int _sendDelay)
    {
        inpPin = _inpPin;
        outPin = _outPin;
        sendDelay = _sendDelay;
    }

    void init()
    {
        pinMode(inpPin, INPUT);
        pinMode(outPin, OUTPUT);
    }

    void sendByte(uint8_t value)
    {
        rawSendByte(value, outPin, sendDelay);
    }

    uint8_t readByte()
    {
        return rawReadByte(inpPin, sendDelay);
    }

    void sendString(String value)
    {
        rawSendString(value, outPin, sendDelay);
    }

    String readString()
    {
        return rawReadString(inpPin, sendDelay);
    }
};