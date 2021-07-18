#include "booth.h"

u8 mode;

void BOOTH_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5; //BOOTH0    BOOTH1对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOE4.5

 
} 


void Booth_mode(void)
{
	if(BOOTH0==1&&BOOTH1==1)
	{
		mode = 1;
	}
	else if(BOOTH0==0&&BOOTH1==1)
	{
		mode = 2;
	}
	else if(BOOTH0==0&&BOOTH1==0)
	{
		mode = 3;
	}
	else if(BOOTH0==1&&BOOTH1==0)
	{
		mode = 4;
	}
}






