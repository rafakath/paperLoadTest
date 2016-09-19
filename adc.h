#ifndef __ADC_H__
#define __ADC_H__
#include<pic.h>
#include<htc.h>
#include "Delay.h"
void adc_ini(unsigned char);
void int_ini();
void delay();
void convert_disp1(unsigned char position,int adcf1 );
#define FORMULA 488
#define AN_0 0x81
#define AN_1 0x89
#define AN_2 0x91
#define AN_3 0x99
#define AN_4 0xA1
#define AN_5 0xA9
#define AN_6 0xB1
#define AN_7 0xB9
#endif