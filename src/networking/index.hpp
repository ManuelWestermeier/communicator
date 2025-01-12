#pragma once

#include "../user.hpp"
#include "../node/node.hpp"
#include <map>

struct Network
{
    Node connection;

    void init()
    {
        connection.init();
    }

    Network(uint8_t inpPin, uint8_t outPin, int sendDelay)
    {
        connection = Node(inpPin, outPin, sendDelay);
        connection.init();
    }

    struct Group
    {
    };

    std::map<String, Group> groupsJoined;
    TaskHandle_t updateTaskHandle = nullptr; // Handle for the FreeRTOS task
    bool isRunning = false;

    // Start function: creates a new FreeRTOS task
    void start()
    {
        if (!isRunning)
        {
            isRunning = true;
            // Create a new FreeRTOS task to run the update function
            xTaskCreate(
                [](void *context)
                {
                    static_cast<Network *>(context)->update();
                },
                "NetworkUpdateTask", // Task name
                4096,                // Stack size (adjust as necessary)
                this,                // Pass the Network instance as context
                1,                   // Task priority
                &updateTaskHandle    // Task handle
            );
        }
    }

    // End function: deletes the task
    void end()
    {
        if (isRunning)
        {
            isRunning = false;
            if (updateTaskHandle != nullptr)
            {
                vTaskDelete(updateTaskHandle);
                updateTaskHandle = nullptr;
            }
        }
    }

private:
    // Update function: runs in the created task
    void update()
    {
        while (isRunning)
        {
            // Perform update logic here
            vTaskDelay(10 / portTICK_PERIOD_MS); // Sleep for 10ms to reduce CPU usage
        }
    }
};