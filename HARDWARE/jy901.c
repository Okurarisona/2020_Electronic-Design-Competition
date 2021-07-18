#include "jy901.h"
#include "math.h"
#include <string.h>

#define JY901_PACKET_LENGTH      15    //���ݰ�����
#define OPEN 1

extern u8 jy_901_flag ;
struct SAcc stcAcc;
short  acc_x,acc_y ,acc_z;
float v0 = 0,vt,disance;
float acc_conpe = 0;
float acc_avg = 0,acc_sum;
u8 acc_con_flag = 0;
u8 RxBuffer[20] = {1};  //���ݰ�
float accx = 0;


void data_receive(u8 data)
{
		
		static u8 RxCheck = 0;	  //βУ����
		static u8 RxCount = 0;	    //���ռ���
		static u8 i = 0;	   		  //���ռ���
		
		RxBuffer[RxCount++] = data;	//���յ������ݴ��뻺������

		if (RxBuffer[0]!=0x68)
		{ //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
				RxCount=0;					  //��ջ�����
				return;
		}
				
	

		if (RxCount < JY901_PACKET_LENGTH) {return;}//���ݲ���11�����򷵻�
		
		/*********** ֻ�н�����11���ֽ����� �Ż�������³��� ************/
	
		
		for(i = 0;i < JY901_PACKET_LENGTH-1;i++){
				RxCheck += RxBuffer[i]; //У��λ�ۼ�
				
		}
		
		if(	RxCheck == RxBuffer[JY901_PACKET_LENGTH-1])//�ж����ݰ�У�� �Ƿ���ȷ
		{
				
				if(RxBuffer[1] == 0x51)
			{	
					for(i=0;i<7;i++)
					{
						stcAcc.a[i]=RxBuffer[2+i];
						
					}	
			}
					
					
				
		}				
					data_jy901(); //��jy901���أ���ʼ����
		
					
					RxBuffer[0] = 0;
					RxBuffer[1] = 0;
					RxCount = 0;//��ջ�����
					RxCheck = 0;//У��λ����
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
		vt = v0 + acc*0.01f;											//����ĩ�ٶ�
		disance += (vt + v0)*0.5f*0.01f;								//�����˶�����	
	
		v0 = vt;																	//�˴�ĩ�ٶ���Ϊ�´γ��ٶ�
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
	


