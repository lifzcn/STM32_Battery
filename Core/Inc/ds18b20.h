#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "stm32f1xx_hal.h"
#include "main.h"

//IO�ڲ���
#define DS18B20_1_DQ_OUT_HIGH HAL_GPIO_WritePin(DS18B20_Detect_1_GPIO_Port,DS18B20_Detect_1_Pin,GPIO_PIN_SET)
#define DS18B20_1_DQ_OUT_LOW 	HAL_GPIO_WritePin(DS18B20_Detect_1_GPIO_Port,DS18B20_Detect_1_Pin,GPIO_PIN_RESET)
#define DS18B20_1_DQ_IN	 HAL_GPIO_ReadPin(DS18B20_Detect_1_GPIO_Port,DS18B20_Detect_1_Pin)

#define DS18B20_2_DQ_OUT_HIGH HAL_GPIO_WritePin(DS18B20_Detect_2_GPIO_Port,DS18B20_Detect_2_Pin,GPIO_PIN_SET)
#define DS18B20_2_DQ_OUT_LOW 	HAL_GPIO_WritePin(DS18B20_Detect_2_GPIO_Port,DS18B20_Detect_2_Pin,GPIO_PIN_RESET)
#define DS18B20_2_DQ_IN	 HAL_GPIO_ReadPin(DS18B20_Detect_2_GPIO_Port,DS18B20_Detect_2_Pin)

uint8_t DS18B20_1_Init(void);//��ʼ��DS18B20
float DS18B20_1_GetTemperture(void);//��ȡ�¶�
void DS18B20_1_Start(void);		//��ʼ�¶�ת��
void DS18B20_1_Write_Byte(uint8_t dat);//д��һ���ֽ�
uint8_t DS18B20_1_Read_Byte(void);//����һ���ֽ�
uint8_t DS18B20_1_Read_Bit(void);//����һ��λ
uint8_t DS18B20_1_Check(void);//����Ƿ����DS18B20
void DS18B20_1_Reset(void);//��λDS18B20   

uint8_t DS18B20_2_Init(void);//��ʼ��DS18B20
float DS18B20_2_GetTemperture(void);//��ȡ�¶�
void DS18B20_2_Start(void);		//��ʼ�¶�ת��
void DS18B20_2_Write_Byte(uint8_t dat);//д��һ���ֽ�
uint8_t DS18B20_2_Read_Byte(void);//����һ���ֽ�
uint8_t DS18B20_2_Read_Bit(void);//����һ��λ
uint8_t DS18B20_2_Check(void);//����Ƿ����DS18B20
void DS18B20_2_Reset(void);//��λDS18B20   

#endif
