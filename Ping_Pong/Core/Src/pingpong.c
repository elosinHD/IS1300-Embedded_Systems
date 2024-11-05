

/**
******************************************************************************
@brief Pingpong statemachine for Pingpong-program
@file pingpong.c
@author Bengt Molin
@version 1.0
@date 12-August-2019
@brief Functions and structures for program Pingpong
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "pingpong.h"
#include <stdbool.h>
#include <stdint.h>
#include <pingpong_functions.h>
/* Define states for state machine*/
typedef enum
{
    Start,
    MoveRight,
    MoveLeft,
    Serve,
    Game_END
} states;
static states State, NextState;
void Pingpong(void)
{
    bool ButtonPressed;   // To remember that button is pressed
    uint32_t Varv, Speed; // Ball speed
    uint8_t Led;          // LED nr
    State = Start;        // Initiate State to Start
    NextState = Start;
    /* Infinite loop */
    while (1)
    {
        State = NextState;
        switch (State) // State machine
        {
        case Start: 
            Led_on(0);           // Turn off all LEDs
            Speed = 500000; // Number of loops
            int R_Score = 0;     // Reset R scores
            int L_Score = 0;     // Reset L scores
            int Served = 0;      // 1 = L served, 2 = R served
            if (L_hit() == true) // L serve
            {
                Led = 1;
                Served = 1;
                NextState = MoveRight;
                while (L_hit() == true); // wait until button is released
            }
            else if (R_hit() == true) // R serve
            {
                Led = 8;
                Served = 2;
                NextState = MoveLeft;
                while (R_hit() == true); // wait until button is released
            }
            else
                NextState = Start; // Stay in Start state
            break;
        case MoveRight:
        {
            Led_on(Led);
            Varv = Speed;
            while (Varv != 0)
            {
                if (R_hit())
                    ButtonPressed = true; // R hit
                Varv--;
            }
            if (ButtonPressed) // R pressed
            {
                Speed -= 40000;
                if (Led == 8) // and LED8 activa
                {
                    NextState = MoveLeft; // return ball
                    Led = 7;
                }
                else{
                    HAL_Delay(100);
                NextState = Serve; // hit to early
                    L_Score++;
                    Led_Flash();
                }
            }
            else
            {
                if (Led == 9)
                { // no hit or to late
                    HAL_Delay(100);
                    NextState = Serve;
                    L_Score++;
                    Led_Flash();
                }
                else{
                    NextState = MoveRight; // ball continues to move right
                    }
            }
            if (!ButtonPressed)
                Led++; // prepare to turn next LED on
            ButtonPressed = false;
        }
        break;
        case MoveLeft:
        {
            Led_on(Led);
            Varv = Speed;
            while (Varv != 0)
            {
                if (L_hit())
                    ButtonPressed = true; // L hit
                Varv--;
            }
            if (ButtonPressed) // L pressed
            {
                Speed -= 40000;
                if (Led == 1) // and LED1 active
                {
                    NextState = MoveRight; // return ball
                    Led = 2;
                }
                else {
                    HAL_Delay(100);
                NextState = Serve; // hit to early
                    R_Score++;
                    Led_Flash();
                }
            }
            else
            {
                if (Led == 0)
                { // no hit or to late
                    HAL_Delay(100);
                    NextState = Serve;
                    R_Score++;
                    Led_Flash();
                }
                else {
                    NextState = MoveLeft; // ball continues to move left
                    }
            }
            if (!ButtonPressed)
                Led--; // prepare to turn next LED on
            ButtonPressed = false;
        }
        break;
        case Serve:
        {
             Show_Points(L_Score, R_Score);      // Show points
             Speed = 500000; // Number of loops
             if(L_Score >= 4){
                 NextState = Game_END;
             }
             else if(R_Score >= 4){
                 NextState = Game_END;
             }
             else {

                if (L_hit() && Served == 2) // L serve
             {
                 Led = 1;
                 NextState = MoveRight;
                 Served = 1;
                 while (L_hit() == true)
                     ; // wait until button is released
             }
             else if ((R_hit() && Served == 1)) // R serve
             {
                 Led = 8;
                 NextState = MoveLeft;
                 Served = 2;
                 while (R_hit() == true)
                     ; // wait until button is released
             }
             else
                 NextState = Serve; // Stay in Serve state
             }          
        } // End of Serve
        break;
        case Game_END: 
        {
            Show_End_Points(L_Score, R_Score); // Show points
            HAL_Delay(5000);
            NextState = Start;

        }
        break;   
        default:
            break;
        } // End of switch
    } // End of while
} // End of function Pingpong
