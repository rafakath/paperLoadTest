#include"lcd_4bit.h"
void lcd_ini()
{
	DelayMs(40);
	lcd_comn(0x30);
	lcd_comn(0x30);
	lcd_comn(0x30);
	lcd_comn(0x02);
	lcd_comn(0x28);
	lcd_comn(0x0e);
	lcd_comn(0x01);
	lcd_comn(0x06);
	lcd_comn(0x80);
}

void lcd_comn(unsigned char comn )
{
	lcd_out=lcd_out&0x0f;
	lcd_out|=(comn&0xf0);
	rs=0;
	rw=0;
	en=1;
	DelayMs(1);
	en=0;
	DelayMs(2);
	lcd_out=lcd_out&0x0f;
		lcd_out|=(comn<<4);
	rs=0;
	rw=0;
	en=1;
	DelayMs(1);
	en=0;
	DelayMs(5);	
}
void lcd_data(unsigned char dat )
{
	lcd_out=lcd_out&0x0f;
	lcd_out|=(dat&0xf0);
	rs=1;
	rw=0;
	en=1;
	DelayMs(1);
	en=0;
    DelayMs(2);
    lcd_out=lcd_out&0x0f;	
	lcd_out|=(dat<<4);
	rs=1;
	rw=0;
	en=1;
	DelayMs(1);
	en=0;
    DelayMs(5);
}

void comndata(unsigned char comnd,const unsigned char *dat)
{
     lcd_comn(comnd);
     while(*dat!='\0')
     {
      lcd_data(*dat++);

     }
}

void data_str(const unsigned char *dat1)
{
     while(*dat1!='\0')
     {
      lcd_data(*dat1++);

     }
}

