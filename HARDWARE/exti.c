#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
#include "t423.h"
#include "timer.h"
#include "jy901.h"
#include <stdlib.h>
#include <stdio.h>

extern u8 t423_flag_time,t423_flag;
extern u8 step_number ,step_flag;
extern float v0 ,vt,disance;
//////////////////////////////////////////////////////////////////////////////////	 
 
//外部中断 驱动代码	   
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 

//外部中断0服务程序
void EXTI15_10_IRQHandler(void)
{
	//delay_ms(10);	//消抖
	if(t423_flag == 1)
	{		
			step_flag ++;
			if(step_flag>=2)
			{
				step_number++;
				//disance += ((float)(rand()%400)/100)+48;
			}
			t423_flag = 0;
			
	}
	
	 
	 EXTI_ClearITPendingBit(EXTI_Line13); //清除LINE0上的中断标志位 
}	
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	//delay_ms(10);	//消抖
	if(KEY2==0)	  
	{				 
   LED0=!LED0; 
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	//delay_ms(10);	//消抖
	if(KEY1==0)	 
	{
		LED1=!LED1;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY0==0)	 
	{				 
		LED0=!LED0;	
		LED1=!LED1;	
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
	t423_init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource13);//PE13 连接到中断线13
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */

  EXTI_InitStructure.EXTI_Line = EXTI_Line13;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置

	
//	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
//  EXTI_Init(&EXTI_InitStructure);//配置
// 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
//	
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
//	
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
//	   
}












