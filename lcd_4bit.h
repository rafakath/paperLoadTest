#ifndef __LCD4BIT_H__
#define __LCD4BIT_H__
#include<pic.h>
#include<htc.h>
#include "Delay.h"
void lcd_ini();
void data_str(const unsigned char *dat1);
void lcd_comn(unsigned char comn );
void lcd_data(unsigned char dat );
void comndata(unsigned char comnd,const unsigned char *dat);
#define lcd_out PORTB
#define rs RB1
#define rw RB2
#define en RB3
#endif