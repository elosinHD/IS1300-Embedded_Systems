#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "traffic.h"

// Define Delays and times:

int toggleFreq = 500;       // 500ms // 0.5s
int pedestrianDelay = 5000; // 5000ms // 5s
int orangeDelay = 2000;     // 2000ms // 2s
int greenDelay = 10000;     // 10000ms // 10s
int redDelayMax = 4000;     // 4000ms // 4s

// Define the traffic light data array and other
uint8_t trafficLights[3] = {0b00000100, 0b00000000, 0b00000000};
// index 0: TL1 | index 1: TL2 | index 2: TL3
uint8_t carSwitches[4] = {1, 1, 1, 1}; // 0: car | 1: no car
// index 0: TL1_Car | index 1: TL2_Car | index 2: TL3_Car | index 3: TL4_Car
uint8_t pedestrianButtons[2] = {1, 1}; // 0: pedestrian | 1: no pedestrian
// index 0: PL1_Switch | index 1: PL2_Switch

// send traffic light data to the other board using SPI
void sendLightData(uint8_t *trafficLights)
{
    // HAL_GPIO_WritePin(Enable_GPIO_Port, Enable_Pin, GPIO_PIN_SET); // IMPORTANT TO ENABLE SO THAT LIGHTS ARE STABLE
    HAL_SPI_Transmit(&hspi3, trafficLights, 3, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(Enable_GPIO_Port, Enable_Pin, GPIO_PIN_RESET); // Just to be safe
    HAL_Delay(100);
};

void readCarSwitches(uint8_t *carSwitches)
{
    carSwitches[0] = HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin);
    carSwitches[1] = HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin);
    carSwitches[2] = HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin);
    carSwitches[3] = HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin);
};

void readPedestrianButtons(uint8_t *pedestrianButtons)
{
    pedestrianButtons[0] = HAL_GPIO_ReadPin(PL1_Switch_GPIO_Port, PL1_Switch_Pin);
    pedestrianButtons[1] = HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin);
};

void writeLightData(uint8_t *trafficLights, TrafficLightPort_t trafficLightPort, TrafficLightState_t trafficLightState)
{
    if (trafficLightPort == TL_North)
    {
        if (trafficLightState == RED)
        {
            trafficLights[0] |= 0b00010000;
        }
        else if (trafficLightState == YELLOW)
        {
            trafficLights[0] |= 0b00001000;
        }
        else if (trafficLightState == GREEN)
        {
            trafficLights[0] |= 0b00000100;
        }
        else if (trafficLightState == OFF)
        {
            trafficLights[0] &= 0b11100000;
        }
    }
    else if (trafficLightPort == TL_East)
    {
        if (trafficLightState == RED)
        {
            trafficLights[0] |= 0b10000000;
        }
        else if (trafficLightState == YELLOW)
        {
            trafficLights[0] |= 0b01000000;
        }
        else if (trafficLightState == GREEN)
        {
            trafficLights[0] |= 0b00100000;
        }
        else if (trafficLightState == OFF)
        {
            trafficLights[0] &= 0b00011100;
        }
    }
    else if (trafficLightPort == TL_South)
    {
        if (trafficLightState == RED)
        {
            trafficLights[1] |= 0b10000000;
        }
        else if (trafficLightState == YELLOW)
        {
            trafficLights[1] |= 0b01000000;
        }
        else if (trafficLightState == GREEN)
        {
            trafficLights[1] |= 0b00100000;
        }
        else if (trafficLightState == OFF)
        {
            trafficLights[1] &= 0b00011100;
        }
    }
    else if (trafficLightPort == TL_West)
    {
        if (trafficLightState == RED)
        {
            trafficLights[2] |= 0b10000000;
        }
        else if (trafficLightState == YELLOW)
        {
            trafficLights[2] |= 0b01000000;
        }
        else if (trafficLightState == GREEN)
        {
            trafficLights[2] |= 0b00100000;
        }
        else if (trafficLightState == OFF)
        {
            trafficLights[2] &= 0b00011100;
        }
    }
    else if (trafficLightPort == PL_North)
    {
        if (trafficLightState == RED)
        {
            trafficLights[1] |= 0b00010000;
        }
        else if (trafficLightState == YELLOW)
        {
            trafficLights[1] |= 0b00001000;
        }
        else if (trafficLightState == BLUE)
        {
            trafficLights[1] |= 0b00000100;
        }
        else if (trafficLightState == OFF)
        {
            trafficLights[1] &= 0b11100000;
        }
    }
    else if (trafficLightPort == PL_West)
    {
        if (trafficLightState == RED)
        {
            trafficLights[2] |= 0b00010000;
        }
        else if (trafficLightState == YELLOW)
        {
            trafficLights[2] |= 0b00001000;
        }
        else if (trafficLightState == BLUE)
        {
            trafficLights[2] |= 0b00000100;
        }
        else if (trafficLightState == OFF)
        {
            trafficLights[2] &= 0b11100000;
        }
    }
};

void task1_pedestrian(void)
{
    if (pedestrianButtons[1] == 0)
    {                                      // NORTH PEDESTRIAN
        if ((trafficLights[0] & (1 << 2))) // If TL_North is Green
        {
            HAL_Delay(100);
            int i;
            for (i = 0; i < 5; i++) // Blink Blue 5 times
            {
                writeLightData(trafficLights, PL_North, BLUE);
                sendLightData(trafficLights);
                HAL_Delay(toggleFreq);
                writeLightData(trafficLights, PL_North, OFF);
                writeLightData(trafficLights, PL_North, RED);
                sendLightData(trafficLights);
                HAL_Delay(toggleFreq);
            }
            writeLightData(trafficLights, TL_North, OFF);
            writeLightData(trafficLights, TL_South, OFF);
            writeLightData(trafficLights, TL_East, OFF);
            writeLightData(trafficLights, TL_West, OFF);
            writeLightData(trafficLights, TL_North, YELLOW);
            writeLightData(trafficLights, TL_South, YELLOW);
            writeLightData(trafficLights, TL_East, YELLOW);
            writeLightData(trafficLights, TL_West, YELLOW);
            sendLightData(trafficLights);
            HAL_Delay(orangeDelay);
            writeLightData(trafficLights, TL_North, OFF);
            writeLightData(trafficLights, TL_South, OFF);
            writeLightData(trafficLights, TL_East, OFF);
            writeLightData(trafficLights, TL_West, OFF);
            writeLightData(trafficLights, TL_North, RED);
            writeLightData(trafficLights, TL_South, RED);
            writeLightData(trafficLights, TL_East, GREEN);
            writeLightData(trafficLights, TL_West, GREEN);
            sendLightData(trafficLights);
        }
        // Change Pedestrian Light from RED, to GREEN and then back to RED.
        writeLightData(trafficLights, PL_North, OFF);
        writeLightData(trafficLights, PL_North, YELLOW); // Make PL_North Green
        sendLightData(trafficLights);
        HAL_Delay(pedestrianDelay);
        writeLightData(trafficLights, PL_North, OFF);
        writeLightData(trafficLights, PL_North, RED); // Make PL_North
        sendLightData(trafficLights);
    }
    if (pedestrianButtons[0] == 0)
    {                                      // WEST PEDESTRIAN
        if ((trafficLights[2] & (1 << 5))) // If TL_West is GREEN
        {
            HAL_Delay(100);
            int i;
            for (i = 0; i < 5; i++) // Blink Blue 5 times
            {
                writeLightData(trafficLights, PL_West, BLUE);
                sendLightData(trafficLights);
                HAL_Delay(toggleFreq);
                writeLightData(trafficLights, PL_West, OFF);
                writeLightData(trafficLights, PL_West, RED);
                sendLightData(trafficLights);
                HAL_Delay(toggleFreq);
            }
            writeLightData(trafficLights, TL_North, OFF);
            writeLightData(trafficLights, TL_South, OFF);
            writeLightData(trafficLights, TL_East, OFF);
            writeLightData(trafficLights, TL_West, OFF);
            writeLightData(trafficLights, TL_North, YELLOW);
            writeLightData(trafficLights, TL_South, YELLOW);
            writeLightData(trafficLights, TL_East, YELLOW);
            writeLightData(trafficLights, TL_West, YELLOW);
            sendLightData(trafficLights);
            HAL_Delay(orangeDelay);
            writeLightData(trafficLights, TL_North, OFF);
            writeLightData(trafficLights, TL_South, OFF);
            writeLightData(trafficLights, TL_East, OFF);
            writeLightData(trafficLights, TL_West, OFF);
            writeLightData(trafficLights, TL_North, GREEN);
            writeLightData(trafficLights, TL_South, GREEN);
            writeLightData(trafficLights, TL_East, RED);
            writeLightData(trafficLights, TL_West, RED);
            sendLightData(trafficLights);
        }
        // Change Pedestrian light from Red, to Green and then back to Red
        writeLightData(trafficLights, PL_West, OFF);
        writeLightData(trafficLights, PL_West, YELLOW); // Make PL_West Green
        sendLightData(trafficLights);
        HAL_Delay(pedestrianDelay); // Wait pedestrianDelay
        writeLightData(trafficLights, PL_West, OFF);
        writeLightData(trafficLights, PL_West, RED); // Make PL_West Red
        sendLightData(trafficLights);
    }
}

// start the traffic light system

void startTraffic(void)
{
    writeLightData(trafficLights, TL_North, GREEN);
    writeLightData(trafficLights, TL_East, RED);
    writeLightData(trafficLights, TL_South, GREEN);
    writeLightData(trafficLights, TL_West, RED);
    writeLightData(trafficLights, PL_North, RED);
    writeLightData(trafficLights, PL_West, RED);
    sendLightData(trafficLights);
    HAL_Delay(100);

    while (1)
    {
        readCarSwitches(carSwitches);
        readPedestrianButtons(pedestrianButtons);

        // PEDESTRIAN SECTION
        task1_pedestrian();

        // CAR TRAFFIC SECTION
    }
};
