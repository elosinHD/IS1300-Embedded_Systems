#include <stdbool.h>
#include <stdint.h>

#ifndef INC_TRAFFIC_H_
#define INC_TRAFFIC_H_

void startTraffic(void);

typedef enum
{
    RED,
    YELLOW,
    GREEN,
    BLUE,
    OFF
}TrafficLightState_t;

typedef enum 
{
    TL_North,
    TL_East,
    TL_South,
    TL_West,
    PL_North,
    PL_West
}TrafficLightPort_t;

void sendLightData(uint8_t *trafficLights);
void readCarSwitches(uint8_t *carSwitches);
void readPedestrianButtons(uint8_t *pedestrianButtons);
void writeLightData (uint8_t *trafficLights, TrafficLightPort_t trafficLightPort, TrafficLightState_t trafficLightState);

void task1_pedestrian(void);

#endif /* INC_TRAFFIC_H_ */