#include "addwind.h"
#include "tim.h"

void AddWind(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_Delay(3000);
	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3);
}
