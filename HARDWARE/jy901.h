#ifndef _JY901_H__
#define _JY901_H__

#include "sys.h"

struct SAcc
{
	short a[6];
	short T;
};


void data_jy901(void); //���ٶ�תת��
void data_receive(u8 data);
double distance(float acc);    	//�������
float acc_conponten(float acc)  ;   //���ٶȲ���


#endif
