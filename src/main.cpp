#include <Arduino.h>

#include "./node/debug-test.hpp"
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
#if IS_SENDING
    // send byte
    node.sendByte(182);

    delay(200);

    // send buffer
    uint8_t bufferData[4] = {
        0x00,
        0x01,
        0x03,
        0x10,
    };
    Buffer bufferToSend(bufferData, sizeof(bufferData));
    node.sendBuffer(bufferToSend);
    delay(200);

    // send string
    node.sendString("trafficcar");
    delay(1000);
#else
    // read a byte
    uint8_t byteValue = node.readByte();
    Serial.println("BYTE RECIEVED: " + String(byteValue, BIN));

    // read a buffer
    Buffer bufferValue = node.readBuffer();
    if (bufferValue.length == 0 || bufferValue.data == nullptr)
        Serial.println("ERROR: BUFFER IS CORRUPTED");
    else
        Serial.println("BUFFER RECIEVED: " + bufferValue.toString());

    // read a string
    String stringValue = node.readString();
    if (stringValue == "")
        Serial.println("ERROR: DATA IS CORRUPTED");
    else
        Serial.println("STRING RECIEVED: " + stringValue);
#endif
}