#include <Arduino.h>

#include "./user.hpp"
#include "./node/node.hpp"

#define INP_PIN_SENDER 26
#define INP_PIN_RECIEVER 25

#define DEFAULT_SEND_DELAY 40

Node node{
    IS_SENDING ? INP_PIN_SENDER : INP_PIN_RECIEVER,
    !IS_SENDING ? INP_PIN_SENDER : INP_PIN_RECIEVER,
    DEFAULT_SEND_DELAY,
};

void setup()
{
    Serial.begin(115200);
    Serial.println(IS_SENDING ? "SENDER" : "RECEIVER"); // Corrected typo in "RECEIVER"
    node.init();
}

long recievedIndex = 0;

void loop()
{
#if IS_SENDING
    node.sendString("trafficcar");
#else
    recievedIndex++;
    String value = node.readString();
    if (value == "")
        Serial.println("ERROR: Invalid data received");
    else
        Serial.println(value);
    Serial.println(recievedIndex);
#endif
}