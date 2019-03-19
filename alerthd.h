#ifndef __ALERTHD_H__
#define __ALERTHD_H__

//异常温湿度报警提示
void alert_handle()
{
	if(cetemp>tempmax||rehumi>humimax)
	{
		led1=1;		//降温湿指示灯
		led2=0;
	}
	if(cetemp<tempmin||rehumi<humimin)
	{
		led1=0;
		led2=1;	   //升高温湿指示灯
	}
	if((cetemp>=tempmin&&cetemp<=tempmax)&&(rehumi>=humimin&&rehumi<=humimax))
	{
		led1=0;
		led2=0;	
	}
}

//人体感应报警提示
void hcsr501_handle()
{
	while(hcsr501_data==1)
	{
		beep=~beep;
		delay_us(10);
		if(hcsr501_data==0)
			break;
	}
}

#endif