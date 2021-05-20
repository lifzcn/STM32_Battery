#include "switch.h"
#include "main.h"

void Disconnect(void)
{
	HAL_GPIO_WritePin(SWITCH_GPIO_Port,SWITCH_Pin,GPIO_PIN_SET);
}
