#include <reg51.h>
#include <intrins.h>
#include <hwinfo.h>
#include <lcd1602.h>
#include <dht11.h>
#include <keyhd.h>
#include <datahd.h>
#include <alerthd.h>



void main()
{
	uint8 i=0;
	led1=0;
	led2=0;
	lcd_init();
	
	while(dht11_init())
	{
		for(i=0;i<5;i++)
		{
			write_cmd(0x80+i);
			write_data(info3[i]);
		}			
	}
	
	write_cmd(0x01);
	lcd_init_display();
	i=0;
	
	while(1)
	{	
		i++;
		key_handle();
		alert_handle();
		if(i==15)
		{
			i=0;
			data_handle();
		}
		hcsr501_handle();
		delay_us(1000); 
	}	
}