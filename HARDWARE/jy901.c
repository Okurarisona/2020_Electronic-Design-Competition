#include "jy901.h"
#include "math.h"
#include <string.h>

#define JY901_PACKET_LENGTH      15    //数据包长度
#define OPEN 1

extern u8 jy_901_flag ;
struct SAcc stcAcc;
short  acc_x,acc_y ,acc_z;
float v0 = 0,vt,disance;
float acc_conpe = 0;
float acc_avg = 0,acc_sum;
u8 acc_con_flag = 0;
u8 RxBuffer[20] = {1};  //数据包
float accx = 0;


void data_receive(u8 data)
{
		
		static u8 RxCheck = 0;	  //尾校验字
		static u8 RxCount = 0;	    //接收计数
		static u8 i = 0;	   		  //接收计数
		
		RxBuffer[RxCount++] = data;	//将收到的数据存入缓冲区中

		if (RxBuffer[0]!=0x68)
		{ //数据头不对，则重新开始寻找0x55数据头
				RxCount=0;					  //清空缓存区
				return;
		}
				
	

		if (RxCount < JY901_PACKET_LENGTH) {return;}//数据不满11个，则返回
		
		/*********** 只有接收满11个字节数据 才会进入以下程序 ************/
	
		
		for(i = 0;i < JY901_PACKET_LENGTH-1;i++){
				RxCheck += RxBuffer[i]; //校验位累加
				
		}
		
		if(	RxCheck == RxBuffer[JY901_PACKET_LENGTH-1])//判断数据包校验 是否正确
		{
				
				if(RxBuffer[1] == 0x51)
			{	
					for(i=0;i<7;i++)
					{
						stcAcc.a[i]=RxBuffer[2+i];
						
					}	
			}
					
					
				
		}				
					data_jy901(); //打开jy901开关，开始计算
		
					
					RxBuffer[0] = 0;
					RxBuffer[1] = 0;
					RxCount = 0;//清空缓存区
					RxCheck = 0;//校验位清零
}


void data_jy901()
{
		
	  acc_x = (stcAcc.a[1]<<8)|stcAcc.a[0] ;
		
		accx = acc_x / 32768.0f*16*9.8f; 
		acc_conpe = acc_conponten(accx);
		acc_y = (((stcAcc.a[3]<<8)|stcAcc.a[2])/ 32768.0f*16*9.8f);
		acc_z = (((stcAcc.a[5]<<8)|stcAcc.a[4])/ 32768.0f*16*9.8f);
		
		
		if(OPEN== acc_con_flag)accx = accx - acc_conpe;
	
}	
double distance(float acc)
{
		
		if(accx<0.05f)
		{
			v0 = 0;
			vt = 0;
		}
		vt = v0 + acc*0.01f;											//计算末速度
		disance += (vt + v0)*0.5f*0.01f;								//计算运动距离	
	
		v0 = vt;																	//此次末速度作为下次初速度
		return disance;
	
	
}
u8  acc_counter=0;
	static float acc_rebuff[20];
float acc_conponten(float acc)
{
	

	
		u8 i= 0 ;
		if(fabs(acc)<0.2f)
		{
			acc_rebuff[acc_counter] = acc;
			
			
			if(acc_counter>=20) 
			{
				acc_counter=0 ;
				acc_con_flag = 1;
			}	
			else acc_counter++;
			
			
			for(i = 0; i < 20 ;i++)
			{
				acc_sum += acc_rebuff[i];
				
			}
			acc_avg = acc_sum/20;
			acc_sum = 0 ;
		}
		return acc_avg;
		



}
	


