#include "data.h"
#include "asd1292.h"
#include "LMT70.h"
#include "t423.h"
#include "jy901.h"
#include "delay.h"
#include "booth.h"
#include "stdio.h"
#define DATA_LENTH 7
extern u8 state_data[11];
extern u8 asd1912_data[7];
extern double temperate;
extern u8 step_number;
extern float disance;
extern u8 state_test[11];
extern u8 mode;
extern u8 step_lenth;
u8 check;	
u8 temp1,temp2;



void State_data_procee()								//状态数据处理
{
		static u8 i;
											//校验位
		
		static float temp_float;
	//	static u8 temp_f=0xFF;
		temperate = temperate_calculate();	//计算体温
		temp_float = (float)temperate;
		temp1 = (u8)(temp_float);
		temp2 = 	(u8)((temp_float -temp1)*100);
		
		
		state_data[0] =0xaa;	
		state_data[1] =0x08;	
		state_data[6] =temp1;						//温度1
		state_data[7] =temp2;					//温度2	
		state_data[8] =step_number;							//距离
	
		state_data[9] =step_number;										//空白
	
	
		state_test[0] =0xaa;	
		state_test[1] =0x08;	
		state_test[6] =temp1;						//温度1
		state_test[7] =temp2;					//温度2	
		state_test[8] =step_number;							//步数
		if(mode == 1)state_test[9] =71;							//步距
		else if(mode == 2)state_test[9] = 35;							//步距
		else state_test[9] =49;
		step_lenth = state_test[9];
		for(i = 0; i<10;i++)									//校验位 累加
	{
		check += state_data[i];
	}
		state_data[10] =check;								//校验位

}







