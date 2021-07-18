#include "t423.h"
#include "timer.h"
u8 step_number;
u8 step_flag;
u8 step_lenth;
extern u8 t423_flag_time,t423_flag;
void t423_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	

}



void t423_input()
{
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)==0&&t423_flag==1)
	{
		step_number++;
		t423_flag = 0;
	}
}









