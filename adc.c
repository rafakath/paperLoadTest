#include<pic.h>
#include<htc.h>
#include"lcd_4bit.h"
#include"adc.h"
unsigned char adcl0,adch0;
int adcf0=0x00;
extern unsigned int scale1;
void adc_ini(unsigned char adc_value)
{	
	TRISA=0xff;
	//ADCON0=0x81;
	ADCON0=adc_value;
	//ADCON1=0xc0;	//configure all ADC channel as a analog input.
	ADCON1=0xce;	//configure AN0 ADC channel as a analog input and all other as Digital I/O.
	ADCON0|=0x4;
}
void int_ini()
{
	INTCON=0b11000000;
	ADIE=1;
}
void delay()
{	
	unsigned char i;
	for(i=0;i<5;i++);
}
void convert_disp1(unsigned char position,int adcf1 )
{
		unsigned char lower1, midh,midl,higher1;
	float adcf1unt;
	unsigned int adcf1unt1,add;
	adcf1unt=(float)adcf1;
	adcf1unt=(adcf1unt*5000)/1023;
	adcf1unt1=(unsigned int)adcf1unt;
	if(scale1==0)
	add=0x00;
	else if(scale1>=10){
	add=adcf1unt1/(100);
	add=add*(scale1/10);}
	adcf1unt1=adcf1unt1+add;
	lower1=adcf1unt1%10;
	adcf1unt1=adcf1unt1/10;
	midl=adcf1unt1%10;
	adcf1unt1=adcf1unt1/10;
	midh=adcf1unt1%10;
	adcf1unt1=adcf1unt1/10;
	higher1=adcf1unt1%10;
	lcd_comn(position);
	lcd_data(higher1+0x30);
	lcd_data(midh+0x30);
	lcd_data('.');
	lcd_data(midl+0x30);
	lcd_data(lower1+0x30);
}
void interrupt isr()	//ouput in difference of 5.
{
	if(ADIF)
	{
	adcl0=ADRESL;
	adch0=ADRESH;
	adcf0=adch0;
	adcf0=adcf0<<8;
	adcf0=(adcf0|adcl0);
	delay();
	ADIF=0;
	ADCON0|=0x4;	// start ADC conversion
	}
}