#include <stdint.h>
#include <stdbool.h>
void Led_on(uint8_t Lednr);
void Led_on2(uint8_t Lednr);
void Led_All_on(void);
void Led_off(void);
void Led_Flash(void);
void Show_Points(uint8_t L_points, uint8_t R_points);
void Show_End_Points(uint8_t L_points, uint8_t R_points);
bool L_hit(void);
bool R_hit(void);
