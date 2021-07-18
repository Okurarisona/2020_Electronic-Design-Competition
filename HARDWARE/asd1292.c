#include "asd1292.h"





#define ECG_LENTH 1

#define ASD1292_LENTH 13


u8 state_data[11];
extern u8 step_number;





void ECG_process(u32 data)
{
		static u32 rebuff_ecg[ECG_LENTH];   //  ���ʻ�����
		static u32 ecg_diff[ECG_LENTH];			//	��ֵ�� 
		static u8 i;
		
		
		
	
}




u32 max_calcule(u32 ecg_number)
{
		static u32 max;
		static u32 ecg_now,ecg_last;
		static u32 ecg_diffence;
		
		if(ecg_last==0)ecg_last = ecg_number;					//��� ��ȥֵΪ0���������ֵ��
		
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
		static u8 RxCount = 0;	    //���ռ���
		static u8 i = 0;	   		  //���ռ���
		       //���建����

	
		RxBuffer1[RxCount++] = data;	//���յ������ݴ��뻺������

		if (RxBuffer1[0]!=0xAA)
		{ //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
				RxCount=0;					  //��ջ�����
				return;
		}
				
	

		if (RxCount < ASD1292_LENTH) {return;}//���ݲ���13�����򷵻�
		
		/*********** ֻ�н�����13���ֽ����� �Ż�������³��� ************/

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
					RxCount = 0;//��ջ�����
	
}















