#include "usr_c216.h"


u8 rebuffer_g[30];

#define USR_LENTH 11



void usr_c216_datasend()
{
	static u8 i;
	static u8 data;
	for(i =0;i<USR_LENTH;i++)
	{
		data = rebuffer_g[i];
	}
//	USART_SendData(USART3,data);
}






