#ifndef _JY901_H__
#define _JY901_H__

#include "sys.h"

struct SAcc
{
	short a[6];
	short T;
};


void data_jy901(void); //加速度转转码
void data_receive(u8 data);
double distance(float acc);    	//计算距离
float acc_conponten(float acc)  ;   //加速度补偿


#endif
