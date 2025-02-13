#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "Trafficlights_functions.h"

void lights_display(uint8_t *lights)
{
	HAL_SPI_Transmit(&hspi3, lights, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_RESET);
}

void blinkinglights(lightsstates *curr)
{
	if (curr->p_north == pred)
	{
		curr->p_north = blue; // Lägg till blått (blink)
	}
	else if (curr->p_north == blue)
	{
		curr->p_north = pred; // Tillbaka till rött (ingen blink)
	}
}

void formatlights(uint8_t *lights, lightsstates *curr)
{
	lights[0] = 0;
	lights[1] = 0;
	lights[2] = 0;
	switch (curr->t_NorthAndSouth)
	{
	case green:
		lights[0] |= 0b100;
		lights[1] |= 0b100000;
		break;
	case yellow:
		lights[0] |= 0b1000;
		lights[1] |= 0b1000000;
		break;
	case red:
		lights[0] |= 0b10000;
		lights[1] |= 0b10000000;
		break;
	default:
		break;
	}

	switch (curr->p_north)
	{
	case pgreen:
		lights[1] |= 0b1000;
		break;
	case pred:
		lights[1] |= 0b10000;
		break;
	case blue:
		lights[1] |= 0b10100;
		break;
	case off:
		lights[1] |= 0b00000;
	default:
		break;
	}
}
void Togglefreq(uint8_t freq){
HAL_Delay(freq);
}
