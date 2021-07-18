#include "key.h"
#include "delay.h" 
#include "t423.h"
#include "LMT70.h"
#include "booth.h"
u8 jy_901_flag = 0;

extern u8 step_flag;

extern u8 Lmt71_flag;



//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOA0
 
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan()
{	 
	static u8 key_up=0;//按键按松开标志
	 if(KEY0 == 0)	
	 {
			delay_ms(10);
		 if(KEY0 == 0 &&key_up == 1)
		 {
				step_flag = 0;
				
				key_up = 0;
			 Lmt71_flag = 1;
		 }
	 }
	 if(KEY0 == 1)key_up = 1;
		
 	return 0;// 无按键按下
}




















