#ifndef _ASD1292_H
#define _ASD1292_H

#include "sys.h"

u32 max_calcule(u32 ecg_number);// 计算差值
void ECG_process(u32 data);     //  心率计算
void Ads1292_DAtaReceive(u8 data);//ads


#endif




