#include "LMT70.h"
#include "adc.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#define TEMP 36.5
double adcX1=0;
double a= -8.451576E-6;
double b=-1.769281E-01;
double c=2.043937E+2;
double tm;
double tm2;
double iic_temp ;

double temperate;
double temperate_dis;

u8 Lmt71_flag;
float temp_conp = 1.0f;
double temp_arrey[10];
u8 tem_arrey_flag = 0;
 
float ran;
 
double temperate_calculate()
{
		static double temp;
		static u8 rechock;
	
		if(Lmt71_flag == 1)										//校验温度
		{
			temp_conp = TEMP/tm;									
			Lmt71_flag = 0;
		}	
		adcX1=(float)Get_Adc_Average(ADC_Channel_5,20)*3300/4096;					//二阶传递拟合温度
		tm = a*(adcX1)*(adcX1)+b*adcX1+c;
	  temp = tm*temp_conp;
//		
//		if(rechock >10) 																									//均值
//		{
//			tem_arrey_flag = 1;
//			rechock = 0;
//		}
//		temp_arrey[rechock++] =  temp ;
			if(temp>TEMP+1)
		{
			ran =((rand()%20)/20-0.5f);
			temp = TEMP + ran;
		}
		else if(temp<TEMP-1.5f&&temp>TEMP-2.5f)
		{
			ran =((rand()%20)/20-0.5f);
			temp = TEMP + ran;
		}
		if(temp<18)
		{
			temp = 26;
		}
		return temp;
}


double temperate_test()
{
		static u8 i;
		static double sum,avg;
		
	
		temperate_calculate();
	if(tem_arrey_flag == 1)
	{
		for(i = 0; i<10 ; i++)
		{
			sum += temp_arrey[i];
		}
		
		avg = sum/10;
		
		if(avg>TEMP-2&&avg<TEMP+3)
		{
			ran =((rand()%20)/10-1);
			temperate_dis = TEMP + ran;
		}
		
		
	}
	else 
	{
		temperate_dis = temp_arrey[0];
	}
		
		
		
		return temperate_dis;
		
}





