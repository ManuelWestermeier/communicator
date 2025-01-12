#include <Arduino.h>

#include "./node/debug-test.hpp"
#include "./networking/network.hpp"

#define OUT_PIN 27
#define INP_PIN 26

#define SEND_DELAY 25

Network network;

void setup()
{
    Serial.begin(115200);
    Serial.println(IS_SENDING ? "SENDER" : "RECEIVER");

    network.init(INP_PIN, OUT_PIN, SEND_DELAY);
    network.start();
}

void loop()
{
#if IS_SENDING
    // network.sendByteWF(111, true);
    // delay(1000);
#else
    // auto pocket = network.readByteWF();
    // Serial.println(pocket.isFollowing ? "is f" : "is n f");
    // Serial.println(pocket.data);
#endif
}