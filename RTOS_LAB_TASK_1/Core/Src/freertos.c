/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <semphr.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t varBlink1 = 0;
uint8_t varBlink2 = 0;
uint8_t varBlink3 = 0;
SemaphoreHandle_t mutex;
uint8_t isBlocked = 0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Blink1Task */
osThreadId_t Blink1TaskHandle;
const osThreadAttr_t Blink1Task_attributes = {
  .name = "Blink1Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Blink2Task */
osThreadId_t Blink2TaskHandle;
const osThreadAttr_t Blink2Task_attributes = {
  .name = "Blink2Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for TriggTask */
osThreadId_t TriggTaskHandle;
const osThreadAttr_t TriggTask_attributes = {
  .name = "TriggTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for UserbuttonTask */
osThreadId_t UserbuttonTaskHandle;
const osThreadAttr_t UserbuttonTask_attributes = {
  .name = "UserbuttonTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void wait_cycles(uint32_t n);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Blink1(void *argument);
void Blink2(void *argument);
void Trigg(void *argument);
void Userbutton(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
	mutex = xSemaphoreCreateMutex();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Blink1Task */
  Blink1TaskHandle = osThreadNew(Blink1, NULL, &Blink1Task_attributes);

  /* creation of Blink2Task */
  Blink2TaskHandle = osThreadNew(Blink2, NULL, &Blink2Task_attributes);

  /* creation of TriggTask */
  TriggTaskHandle = osThreadNew(Trigg, NULL, &TriggTask_attributes);

  /* creation of UserbuttonTask */
  UserbuttonTaskHandle = osThreadNew(Userbutton, NULL, &UserbuttonTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Blink1 */
/**
* @brief Function implementing the Blink1Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Blink1 */
void Blink1(void *argument)
{
  /* USER CODE BEGIN Blink1 */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(10) ; // ms to ticks
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
	xSemaphoreTake( mutex, portMAX_DELAY );
	wait_cycles(200000);
	if (isBlocked == 0){
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	}
	else {
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	}
	xSemaphoreGive( mutex );
	vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END Blink1 */
}

/* USER CODE BEGIN Header_Blink2 */
/**
* @brief Function implementing the Blink2Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Blink2 */
void Blink2(void *argument)
{
  /* USER CODE BEGIN Blink2 */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(20) ; // ms to ticks
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
	varBlink2 = 1;
	wait_cycles(400000);
	varBlink2 = 0;
	vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END Blink2 */
}

/* USER CODE BEGIN Header_Trigg */
/**
* @brief Function implementing the TriggTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Trigg */
void Trigg(void *argument)
{
  /* USER CODE BEGIN Trigg */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(200) ; // ms to ticks
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
	vTaskDelayUntil( &xLastWakeTime, xPeriod );
	wait_cycles(10); //add a breakpoint in this line
	}
  /* USER CODE END Trigg */
}

/* USER CODE BEGIN Header_Userbutton */
/**
* @brief Function implementing the UserbuttonTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Userbutton */
void Userbutton(void *argument)
{
  /* USER CODE BEGIN Userbutton */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(20);
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
	xSemaphoreTake( mutex, portMAX_DELAY );
	if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==GPIO_PIN_RESET)
	{
	isBlocked = 1;
	wait_cycles(250000);
	varBlink3 = 0; }
	else {
		isBlocked = 0;
	}
	xSemaphoreGive( mutex );
	vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END Userbutton */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void wait_cycles( uint32_t n ) {
uint32_t l = n/3; //cycles per loop is 3
asm volatile( "0:" "SUBS %[count], 1;" "BNE 0b;" :[count]"+r"(l) );
}
/* USER CODE END Application */

