#include<pic.h>
#include<htc.h>
#include"lcd_4bit.h"
#include"delay.h"
#include"adc.h"
#include"eeprom.h"
////////////////////////////////////////////////////
// PROGRAMMER: MD. RAFAKATH
// TIME TAKEN: 24-28 HRS
// DATE: 23/11/2014
// PROJECT: To calculate Maximum Load cell
//					break Point and callibrate if required
// Limitation: Calibration input Range 10gm - 250gm
////////////////////////////////////////////////////
extern void character(unsigned char,unsigned char);
void DisplayStartMessage();
void CheckStartSwitch();
void CheckLimitSwitch1();
void CheckFunctionKey();
void CheckLimitSwitch();
void CheckLoadBreak(int);
void CheckLimitSwitch2();
void CheckCalibrationKey();
void CheckHomePosition();
void CheckStopKey();
int CheckPeakValue();
void DispScale1( unsigned int);
void variableIni();
extern int adcf0;
#define limitSwitch1 RA1
#define limitSwitch2 RA2
#define enter RC7
#define sw2 RC5
#define sw1 RC6
#define startSwitch RC4
#define resetSwitch RD5
#define relay2 RD0
#define relay1 RD3
bit onOff;			//bit variable must be Declared Globle
//bit gsm;
bit breakload;
bit clearPeak;
unsigned int scale1=0;
unsigned char scaleEepromValue;
void main()
{
	int peak=0;
	variableIni();
	lcd_ini();
	adc_ini(AN_0);
	int_ini();
	scaleEepromValue=eeprom_rd(0x01) ;
	if(scaleEepromValue!=0xff)
	scale1=(unsigned int)scaleEepromValue;
	CheckHomePosition();
	DisplayStartMessage();
	while(1)
	{
		CheckFunctionKey();
		CheckCalibrationKey();
		while(onOff)
			{
				if(breakload==0)
				{
				peak=CheckPeakValue();
				CheckLoadBreak(peak);
				CheckLimitSwitch1();
				CheckLimitSwitch2();
				}
				else
				CheckLimitSwitch();
				CheckStopKey();
		//*-------------- Prog for Reset Switch----------------*
				if(!resetSwitch)
					break;
			}
			if(!resetSwitch)
			{
				variableIni();
				peak=0;
				clearPeak=1;
				CheckHomePosition();
				DisplayStartMessage();
			}

	}
}
void CheckHomePosition()
{
	lcd_comn(0x01);
	comndata(0x80,"CHECKING HOME");
	comndata(0xc0,"POSITION....");
	while(1)
		{
			if(limitSwitch2)
			relay2=0;
			else
			{
				relay2=1;
				DelayMs(1000);
				break;
			}
		}
}
void CheckStopKey()
{

			if(startSwitch==0)
			{	DelayMs(5);
				if(startSwitch==0)
					{while(startSwitch==0);
						lcd_comn(0x01);
						comndata(0x80,"TESTING STOP");
						onOff=0;
						DelayMs(1000);
						DelayMs(1000);
						CheckHomePosition();
						DelayMs(1000);
						DelayMs(1000);
						variableIni();
						clearPeak=1;
						DisplayStartMessage();
					}

			}
}
void CheckCalibrationKey()
{
	if(enter==0)
	{DelayMs(20);
		if(enter==0)
		{
			lcd_comn(0x01);
			comndata(0x80,"CALI: (10g-250g)");
			comndata(0xc2,"1kg+0.");
			DispScale1(scale1);
			while(1)
					{
						if(sw1==0)			//up count
						{	DelayMs(30);
							if(sw1==0)
								{
									if(scale1<250)
										scale1=scale1+10;
										DispScale1(scale1);
								}
						}

						if(sw2==0)			//down count
							{	DelayMs(30);
								if(sw2==0)
									{
										if(scale1>=10)
										scale1=scale1-10;
										DispScale1(scale1);

									}
							}
						if(enter==0)
							{	DelayMs(5);
								if(enter==0){
										lcd_comn(0x01);
										comndata(0x80,"CALI. COMPLETE");
										comndata(0xc4,"PRESS START ");
										scaleEepromValue=(unsigned char)scale1;
										eeprom_wrt(0x01,scaleEepromValue);
										break;
														}
							}

					}	//while(1) loop End.

				}
		}
}
void variableIni()
{
	onOff=0;
	breakload=0;
	clearPeak=0;
	TRISB=0x00;
	TRISD=0b00100000;
	TRISC=0b11111000;
	relay1=1;
	relay2=1;

}
int CheckPeakValue()
{ int present=0;
	static int peak=0;
	present=adcf0;
	if(present>peak)
		peak=present;
	if(clearPeak)
	{
		peak=0;
		clearPeak=0;
	}
	if(!clearPeak)
	convert_disp1(0xc5,peak);
	return peak;
}
void CheckLoadBreak(int peak)
{
	int present=0;
	present=adcf0;
	if(present==0 && peak >=5)
	{
		relay1=1;
		PORTD=PORTD&0b11111110;		//relay2=0;
		lcd_comn(0x01);
		comndata(0x80,"RESULT B.S: ");
		convert_disp1(0x8b,peak);
		comndata(0xc0,"PRESS RESET KEY");
		breakload=1;
	}
}
void DisplayStartMessage()
{
	lcd_comn(0x01);
	comndata(0x80,"BOARD");
	comndata(0xc4,"PRESS START");
}
void CheckFunctionKey()
{
								CheckStartSwitch();
										if(onOff==1)
										{
											lcd_comn(0x01);
											comndata(0x80,"TEST RUNNING....");
											comndata(0xc0,"B.S: ");
										}
}
void DispScale1( unsigned int scale1)
{
	unsigned char lower1, midh,midl,higher1;
	lower1=scale1%10;
	scale1=scale1/10;
	midl=scale1%10;
	scale1=scale1/10;
	midh=scale1%10;
	higher1=scale1/10;
	lcd_comn(0xc8);
	//lcd_data(higher1+0x30);
	lcd_data(midh+0x30);
	lcd_data(midl+0x30);
	lcd_data(lower1+0x30);
}
void CheckStartSwitch()
{
		if(startSwitch==0)
			{	DelayMs(5);
				if(startSwitch==0)
					{	while(startSwitch==0);
						onOff=1;relay1=0;

					}

			}
}
void CheckLimitSwitch1()
{
	if(limitSwitch1==0)
		{	DelayMs(5);
			if(limitSwitch1==0){relay1=1;relay2=0;}
		}
}
void CheckLimitSwitch2()
{
	if(limitSwitch2==0)
		{	DelayMs(5);
			if(limitSwitch2==0){relay2=1;}
		}
}
void CheckLimitSwitch()
{
	if(limitSwitch1==0)
		{	DelayMs(5);
			if(limitSwitch1==0){relay1=1;relay2=0;}
		}
	if(limitSwitch2==0)
		{	DelayMs(5);
			if(limitSwitch2==0){relay2=1;}
		}
}
