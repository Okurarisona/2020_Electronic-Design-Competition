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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	
	//t423_init();

	
	KEY_Init();
	OLED_Init();				//	��ʼ��oled
	Adc_Init();         //��ʼ��ADC
	EXTIX_Init();
	//max_init();  //i2c��ʼ��
	TIM3_Int_Init(100-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/84000=10Khz�ļ���Ƶ�ʣ�����50000��Ϊ10ms  
	TIM4_Int_Init(10-1,840-1); // 100us
	uart_init(9600);	
	uart2_init(9600);
	uart3_init(9600);
	BOOTH_Init();
		
	while(1)
	{			
				//booth0_static = GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4);
				State_data_procee()	;								//״̬��Ϣ��ȡ
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

