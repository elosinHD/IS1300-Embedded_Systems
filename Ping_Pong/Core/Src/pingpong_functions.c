#include <stdint.h>
#include <gpio.h>
#include <stdbool.h>
/**
@brief Led_on, turn one of the pingpong leds on

@param uint8_t Lednr , number to the Led that is turned on
	Lednr can be 1-8, all other values turns all leds off

@return void
*/

void Led_on(uint8_t Lednr)
{
uint8_t i;
for (i=1; i<= 8; i++)
{
switch(i){
case 1 : // Led 1
if (Lednr==i) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
break;
case 2 : // Led 2
if (Lednr==i) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
break;
case 3 : // Led 3
if (Lednr==i) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
break;
case 4 : // Led 4
if (Lednr==i) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
break;
case 5 : // Led 5
if (Lednr==i) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
break;
case 6 : // Led 6
if (Lednr==i) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
break;
case 7 : // Led 7
if (Lednr==i) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
break;
case 8 : // Led 8
if (Lednr==i) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
break;
default :
;
} // end switch
} // end for-loop
return;
} // end function Led_on

/**
@brief Led_on2, turn a led.

@param uint8_t Lednr , number to the Led that is turned on
	Lednr can be 1-8, all other leds stay on or off.

@return void
*/

void Led_on2(uint8_t Lednr)
{
uint8_t i;
for (i=1; i<= 8; i++)
{
switch(i){
case 1 : // Led 1
if (Lednr==i) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
break;
case 2 : // Led 2
if (Lednr==i) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
break;
case 3 : // Led 3
if (Lednr==i) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
break;
case 4 : // Led 4
if (Lednr==i) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
break;
case 5 : // Led 5
if (Lednr==i) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
break;
case 6 : // Led 6
if (Lednr==i) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
break;
case 7 : // Led 7
if (Lednr==i) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
break;
case 8 : // Led 8
if (Lednr==i) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
break;
default :
;
} // end switch
} // end for-loop
return;
} // end function Led_on



/**
@brief Led_on2, turn on all pingpong leds.
@return void
*/

void Led_All_on(void)
{
HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);

return;
} // end function Led_All_on

/**
@brief Led_off, turn off all of the pingpong leds.
@return void
*/

void Led_off(void)
{
HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
return;
} // end function Led_off

/**
@brief Led_Flash, turn on and off all of the pingpong leds.
@return void
*/

void Led_Flash(){
uint8_t i;
for (i=1; i<= 3; i++){
    Led_All_on();
    HAL_Delay(100);
    Led_off();
    HAL_Delay(100);
}
}

/**
@brief Show_points, shows points after missed ball
@param1 uint8_t L_points points for left player
@param2 uint8_t R_points points for right player
@return void, no return value
*/

void Show_Points(uint8_t L_points, uint8_t R_points){
    
    // Show points on the left side (Left to Right)
    for (int i = 1; i <= L_points; i++){
        Led_on(i);
    }
    // Show points on the right side (Right to Left)
    for (int i = 8; i > 8-R_points; i--){
        Led_on(i);
    }
    return;
}

void Show_End_Points(uint8_t L_points, uint8_t R_points){
        
        // Show points on the left side (Left to Right)
        for (int i = 1; i <= L_points; i++){
            Led_on2(i);
        }
        // Show points on the right side (Right to Left)
        for (int i = 8; i > 8-R_points; i--){
            Led_on2(i);
        }
        return;
}

/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise
*/

bool L_hit(void){
   if (HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin) == 0) return true;
else return false;
}

/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise
*/

bool R_hit(void){
   if (HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin) == 0) return true;
else return false;
}
