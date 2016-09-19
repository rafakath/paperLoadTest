#include<pic.h>
#include<htc.h>
#include "Delay.h"
void eeprom_wrt(unsigned char a,unsigned char d)
{
	EEADR=a;
	EEDATA=d;

	EEPGD=0;
	WREN=1;
	GIE=0;
	EECON2=0x55;
	EECON2=0xaa;
	WR=1;
	while(WR==1);
	GIE=1;
	WREN=0;
}
void eeprom_wrtc(unsigned char a, char d)
{
	EEADR=a;
	EEDATA=d;

	EEPGD=0;
	WREN=1;
	GIE=0;
	EECON2=0x55;
	EECON2=0xaa;
	WR=1;
	while(WR==1);
	GIE=1;
	WREN=0;
}
unsigned char eeprom_rd(unsigned char a)
{	
	EEADR=a;
	EEPGD=0;
	RD=1;
	while(RD==1);
	return(EEDATA);
}