#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "drv_oled.h"

#include "30205.h" 
#include "jy901.h"
#include "adc.h"
#include "timer.h"
#include "LMT70.h"
#include "t423.h"
#include "exti.h"
#include "data.h"

#include "booth.h"

extern float acc_x,acc_y ,acc_z,accx;

extern float v0 ,vt,disance;
extern u8 jy_901_flag;
extern u8 step_number,step_flag;
extern u8 t423_flag_time,t423_flag;
extern double temperate;
extern u8 data_timer;
extern u8 temp1,temp2;
extern u8 mode;
static u8 booth0_static;
extern u8 step_lenth;

int main(void)
{ 
	char str[100];
//	double Temperature_max30205 = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	
	//t423_init();

	
	KEY_Init();
	OLED_Init();				//	初始化oled
	Adc_Init();         //初始化ADC
	EXTIX_Init();
	//max_init();  //i2c初始化
	TIM3_Int_Init(100-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/84000=10Khz的计数频率，计数50000次为10ms  
	TIM4_Int_Init(10-1,840-1); // 100us
	uart_init(9600);	
	uart2_init(9600);
	uart3_init(9600);
	BOOTH_Init();
		
	while(1)
	{			
				//booth0_static = GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4);
				State_data_procee()	;								//状态信息获取
				Booth_mode();
				sprintf(str,"d:%d",step_number*step_lenth);
				OLED_ShowString(0,0,(u8 *)str,16);
				
				sprintf(str,"%d",mode);
				OLED_ShowString(96,0,(u8 *)str,16);
		
				sprintf(str,"temp:%d ",step_flag);
				OLED_ShowString(0,32,(u8 *)str,16);
		
				sprintf(str,"flag:%.1f",temperate);
				OLED_ShowString(0,16,(u8 *)str,16);
				
				sprintf(str,"st:%d",step_number);
				OLED_ShowString(0,48,(u8 *)str,16);
		
				KEY_Scan();
				OLED_Refresh_Gram();//
				
	}
}

