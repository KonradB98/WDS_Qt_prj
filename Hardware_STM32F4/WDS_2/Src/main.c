/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h" // Plik bedacy interfejsem uzytkownika do kontrolera USB
#include <limits.h> //Do maxint
#include <stdio.h> //Do printf()
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

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
//Rejestry
#define LSM303_ACC_ADDRESS (0x19 << 1) // adres akcelerometru: 0011001x
#define LSM303_ACC_CTRL_REG1_A 0x20 // rejestr ustawien 1

#define LSM303_ACC_X_H_A 0x29		   // wyzszy bajt danych osi x
#define LSM303_ACC_X_L_A 0x28          // nizszy bajt osi x

#define LSM303_ACC_Y_H_A 0x2B		   // wyzszy bajt danych osi y
#define LSM303_ACC_Y_L_A 0x2A          // nizszy bajt osi y

#define LSM303_ACC_Z_H_A 0x2D          // wyzszy bajt danych osi z
#define LSM303_ACC_Z_L_A 0x2C          // nizszy bajt osi z

#define LSM303_ACC_Z_L_A_MULTI_READ (LSM303_ACC_Z_L_A | 0x80)
#define LSM303_ACC_X_L_A_MULTI_READ (LSM303_ACC_X_L_A | 0x80)
#define LSM303_ACC_Y_L_A_MULTI_READ (LSM303_ACC_Y_L_A | 0x80)
// Maski bitowe
// CTRL_REG1_A = [ODR3][ODR2][ODR1][ODR0][LPEN][ZEN][YEN][XEN]
#define LSM303_ACC_XYZ_ENABLE 0x07 // 0000 0111
#define LSM303_ACC_1HZ 0x10 //0001 0000 50

#define LSM303_ACC_RESOLUTION 2.0 // Maksymalna wartosc mierzalnego przyspieszenia [g]
//------------------------- Zmienne--------------------------------------//
uint8_t Data[6]; // Zmienna do bezposredniego odczytu z akcelerometru
int16_t Xaxis; // Zawiera przeksztalcona forme odczytanych danych z osi X
int16_t Yaxis; // Zawiera przeksztalcona forme odczytanych danych z osi Y
int16_t Zaxis; // Zawiera przeksztalcona forme odczytanych danych z osi Z

uint8_t DataToSend[1000]; // Tablica zawierajaca dane do wyslania
uint8_t Length;	//Rozmiar wiadomości

uint16_t ToCrc; //Zmienna pom - wartosc rejsstru CRC
//int syncSign;
uint16_t syncSign;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//Przekierowanie funkcji printf() za pomoca SWV
int _write(int file, char *ptr, int len){
	int i ;
	for(i=0;i<len;++i){
		ITM_SendChar(*ptr++);
	}
	return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
Xaxis = 0;
Yaxis = 0;
Zaxis = 0;
ToCrc = 0;
syncSign = 0x24;// Znak '$' zapisany w systemie szesnastkowym Hex
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
  MX_USB_DEVICE_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  // wypelnienie zmiennej konfiguracyjnej odpowiednimi opcjami
  uint8_t Settings = LSM303_ACC_XYZ_ENABLE | LSM303_ACC_1HZ;
  // Wpisanie konfiguracji do rejestru akcelerometru
  HAL_I2C_Mem_Write(&hi2c1, LSM303_ACC_ADDRESS, LSM303_ACC_CTRL_REG1_A, 1, &Settings, 1, 100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Pobieranie 6 bajtów danych zawierających przyspieszenia w 3 osiach
	  HAL_I2C_Mem_Read(&hi2c1, LSM303_ACC_ADDRESS, (LSM303_ACC_X_H_A), 1, &Data[1], 2, 100);
	  HAL_I2C_Mem_Read(&hi2c1, LSM303_ACC_ADDRESS, (LSM303_ACC_Y_H_A), 1, &Data[3], 2, 100);
	  HAL_I2C_Mem_Read(&hi2c1, LSM303_ACC_ADDRESS, (LSM303_ACC_Z_H_A), 1, &Data[5], 2, 100);

	  Xaxis = ((Data[1] << 8) | Data[0]);
	  Yaxis = ((Data[3] << 8) | Data[2]);
	  Zaxis = ((Data[5] << 8) | Data[4]);
	  ToCrc = Xaxis + Yaxis + Zaxis;
	  ToCrc = (ToCrc % 128);
	  //Length=sprintf(DataToSend,"%d %d %d %d",Xaxis,Yaxis,Zaxis,ToCrc);
	  //Przeslij ramke [$][_][X][_][Y][_][Z][_][CRC][_][\n]
	  Length=sprintf(DataToSend,"%x %d %d %d %d \n",syncSign,Xaxis,Yaxis,Zaxis,ToCrc);
	  printf("%x %d %d %d %d \r\n",syncSign,Xaxis,Yaxis,Zaxis,ToCrc);
	  CDC_Transmit_FS(DataToSend, Length);
	 //elk HAL_Delay(200);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
