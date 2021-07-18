#ifndef _BOOTH_H
#define _BOOTH_H
#include "sys.h"


#define BOOTH0 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4) //PF4
#define BOOTH1 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)	//PF5 

void BOOTH_Init(void);
void Booth_mode(void);





#endif







