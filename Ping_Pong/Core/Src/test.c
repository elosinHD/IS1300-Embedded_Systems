#include <stdint.h>
#include <stdbool.h>
#include "pingpong_functions.h"

void Test_program(void)
{
	//Test_buttons();
   // Test_Show_Points(2, 2);
   Led_Flash();
    HAL_Delay(100000);
}


void Test_Led(void)
{
int8_t Lednr;
/* Loop checking that all leds can be turned on*/
for (Lednr=1; Lednr<= 8; Lednr++) {
Led_on(Lednr);
HAL_Delay(500);
}
Led_on(9); // Turn off led 8
HAL_Delay(1000); // 1000 ms
return;
}

void Test_Show_Points(uint8_t L_points, uint8_t R_points){
    
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


void Test_buttons(void)
{
int8_t j;
/* Checking buttons */
j=4;
Led_on(j); // Light on
while (j<9 && j>0)
{
if ( L_hit() == true ) // Wait for left button hit
{
j++; // next led to the right
Led_on(j); // Light on
HAL_Delay(100); // 100 ms
while ( L_hit() == true ); // Wait for button release
HAL_Delay(100); // 100 ms
}
if ( R_hit() == true ) // Wait for right button hit
{
j--; // next led to the left
Led_on(j); // Light on
HAL_Delay(100); // 100 ms
while ( R_hit() == true ); // Wait for button release
HAL_Delay(100); // 100 ms
if (j<1) j=0; // Start again from left
}
}}
