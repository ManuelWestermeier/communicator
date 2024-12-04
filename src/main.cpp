#include <Arduino.h>

#include "./user.hpp"
#include "./node/node.hpp"

#define INP_PIN_SENDER 26
#define INP_PIN_RECIEVER 25

#define DEFAULT_SEND_DELAY 50

Node node{
    IS_SENDING ? INP_PIN_SENDER : INP_PIN_RECIEVER,
    !IS_SENDING ? INP_PIN_SENDER : INP_PIN_RECIEVER,
    DEFAULT_SEND_DELAY,
};

void setup()
{
    Serial.begin(115200);
    Serial.println(IS_SENDING ? "SENDER" : "RECEIVER");
    node.init();
}

void loop()
{
#if true || IS_SENDING
    node.sendByte(182);
    uint8_t buffer[] = {
        0x00,
        0x01,
        0x03,
        0x10,
    };
    node.sendBuffer(Buffer(buffer, sizeof(buffer)));
    node.sendString("trafficcar");
#else
    // read a byte
    uint8_t byteValue = node.readByte();
    Serial.println("BYTE RECIEVED: " + String(byteValue, BIN));

    // read a buffer
    Buffer bufferValue = node.readBuffer();
    if (bufferValue.length == 0)
        Serial.println("ERROR: DATA LENGTH IS 0");
    else
        Serial.println("BUFFER RECIEVED: " + bufferValue.toString());
    // read a string
    String stringValue = node.readString();
    if (stringValue == "")
        Serial.println("ERROR: Invalid data received");
    else
        Serial.println("STRING RECIEVED: " + stringValue);
#endif
}