/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "Trafficlights_functions.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
#define toggleFreq 800      // Frequency in milliseconds for the blinking pedestrian light
#define walkingDelay 6000     // Delay in milliseconds for the pedestrian signal to stay green
#define orangeDelay 5000    // Delay in milliseconds for the orange light (yellow)
#define pedestrianDelay 5000  // Delay in milliseconds for red car signals after button press

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
lightsstates states;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  states.p_north = pred;          // Red for pedestrians
  states.t_NorthAndSouth = green; // Green for cars
  uint8_t lights[3] = {0};

  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Normal state: Green for cars, Red for pedestrians
    formatlights(lights, &states);
    lights_display(lights);

    if (HAL_GPIO_ReadPin(P_North_GPIO_Port, P_North_Pin) == GPIO_PIN_RESET)
    {
      // Blink the pedestrian light until car light changes
        states.t_NorthAndSouth = yellow;  // Change car signal to yellow
        formatlights(lights, &states);
        lights_display(lights);

        int count = (orangeDelay/toggleFreq);
        while (count != 0)
      {
        blinkinglights(&states);  // Toggle between blue and off
        formatlights(lights, &states);
        lights_display(lights);
        HAL_Delay(toggleFreq);
        count--;
      }
       
        formatlights(lights, &states);
        lights_display(lights);

      // After the pedestrian button is pressed, make car lights red for pedestrian crossing
      states.t_NorthAndSouth = red; // Set car signal to red
      formatlights(lights, &states);
      lights_display(lights);

      int count1 = (pedestrianDelay/toggleFreq); 
      while (count1 != 0)
      {
        blinkinglights(&states);  // Toggle between blue and off
        formatlights(lights, &states);
        lights_display(lights);
        HAL_Delay(toggleFreq);
        count1--;
      }

      // Turn pedestrian signal green for walking
      states.p_north = pgreen;
      formatlights(lights, &states);
      lights_display(lights);

      HAL_Delay(walkingDelay); // Pedestrian light stays green for walkingDelay

      // Blink pedestrian signal before switching back to red
      for (int i = 0; i < 6; i++) {
        if (states.p_north == pgreen) {
          states.p_north = off; // Turn off pedestrian signal
        } else {
          states.p_north = pgreen; // Toggle pedestrian signal back to green
        }
        formatlights(lights, &states);
        lights_display(lights);
        HAL_Delay(500);
      }

      // After pedestrian crossing, switch pedestrian signal to red
      states.p_north = pred;
      formatlights(lights, &states);
      lights_display(lights);

      // Wait for a safety delay before switching car signal back to green
      HAL_Delay(2000);

      // Transition car signal back to green
      states.t_NorthAndSouth = green;
      formatlights(lights, &states);
      lights_display(lights);
    }
  }
  /* USER CODE END WHILE */
  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
