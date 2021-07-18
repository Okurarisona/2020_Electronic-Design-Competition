#include "asd1292.h"





#define ECG_LENTH 1

#define ASD1292_LENTH 13


u8 state_data[11];
extern u8 step_number;





void ECG_process(u32 data)
{
		static u32 rebuff_ecg[ECG_LENTH];   //  心率缓冲区
		static u32 ecg_diff[ECG_LENTH];			//	差值区 
		static u8 i;
		
		
		
	
}




u32 max_calcule(u32 ecg_number)
{
		static u32 max;
		static u32 ecg_now,ecg_last;
		static u32 ecg_diffence;
		
		if(ecg_last==0)ecg_last = ecg_number;					//如果 过去值为0，则给它赋值。
		
		ecg_now = ecg_number;													//
		
		ecg_diffence = ecg_now - ecg_last;
		
		if(ecg_diffence)
		
		ecg_last = ecg_now;
		
		return ecg_diffence;
	
	
	
}

u8 RxBuffer1[ASD1292_LENTH];
u8 state_test[11];
void Ads1292_DAtaReceive(u8 data)
{
		static u8 RxCount = 0;	    //接收计数
		static u8 i = 0;	   		  //接收计数
		       //定义缓存区

	
		RxBuffer1[RxCount++] = data;	//将收到的数据存入缓冲区中

		if (RxBuffer1[0]!=0xAA)
		{ //数据头不对，则重新开始寻找0x55数据头
				RxCount=0;					  //清空缓存区
				return;
		}
				
	

		if (RxCount < ASD1292_LENTH) {return;}//数据不满13个，则返回
		
		/*********** 只有接收满13个字节数据 才会进入以下程序 ************/

		if(RxBuffer1[1] == 0xAA)
		{
			if(RxBuffer1[2] == 0xF1)
			{
					if(RxBuffer1[3] == 0x08)
					{
							for(i = 1 ; i<4;i++)
						{
								state_data[i+2] = RxBuffer1[i+8];
								state_test[i+2] = RxBuffer1[i+8];
								state_data[2] = 0;
						}
					}	
					
			}	
			
		}
	
				//	state_data[0] = 0xaa;
				//	state_data[1] = 0x08;
					RxBuffer1[0] = 0;
					RxBuffer1[1] = 0;
					RxBuffer1[2] = 0;
					RxBuffer1[3] = 0;
					RxCount = 0;//清空缓存区
	
}















