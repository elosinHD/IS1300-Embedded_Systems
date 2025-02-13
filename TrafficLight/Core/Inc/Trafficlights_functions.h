#ifndef INC_TRAFFICLIGHTS_FUNCTIONS_H_
#define INC_TRAFFICLIGHTS_FUNCTIONS_H_
typedef enum {red, green, pgreen, yellow, blue, off, pred } light_t;
typedef struct{
	light_t p_north;
	light_t t_NorthAndSouth;
} lightsstates;


void lights_display(uint8_t *lights);
void blinkinglights(lightsstates *curr);
void formatlights(uint8_t *lights, lightsstates *curr);



#endif /* INC_TRAFFICLIGHTS_FUNCTIONS_H_ */
