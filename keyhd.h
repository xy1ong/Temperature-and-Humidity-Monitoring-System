#ifndef __KEYHD_H__
#define __KEYHD_H__

//按键处理函数
void key_handle()
{
	if(k1==0)
	{
		delay_us(1000);  //消除按键抖动
		if(k1==0)
		{
			mode++;
			if(mode==5)
				mode=0;   //4次切换复位
			write_cmd(0x01);
		}
		while(!k1);
	}
	if(mode==1)		  //设置温度上限
	{
		if(k2==0)		  //增加
		{
			delay_us(1000);
			if(k2==0)
			{
				tempmax++;
				if(tempmax>=80)
					tempmax=80;
			}
			while(!k2);
		}
		if(k3==0)	   //减少
		{
			delay_us(1000);
			if(k3==0)
			{
				tempmax--;
				if(tempmax<=0)
					tempmax=0;
			}
			while(!k3);
		}
	}
	if(mode==2)		  //设置温度下限
	{
		if(k2==0)
		{
			delay_us(1000);
			if(k2==0)
			{
				tempmin++;
				if(tempmin>=80)
					tempmin=80;
			}
			while(!k2);
		}
		if(k3==0)
		{
			delay_us(1000);
			if(k3==0)
			{
				tempmin--;
				if(tempmin<=0)
					tempmin=0;
			}
			while(!k3);
		}
	}
	if(mode==3)		  //设置湿度上限
	{
		if(k2==0)
		{
			delay_us(1000);
			if(k2==0)
			{
				humimax++;
				if(humimax>=80)
					humimax=80;
			}
			while(!k2);
		}
		if(k3==0)
		{
			delay_us(1000);
			if(k3==0)
			{
				humimax--;
				if(humimax<=0)
					humimax=0;
			}
			while(!k3);
		}
	}
	if(mode==4)		  //设置湿度下限
	{
		if(k2==0)
		{
			delay_us(1000);
			if(k2==0)
			{
				humimin++;
				if(humimin>=80)
					humimin=80;
			}
			while(!k2);
		}
		if(k3==0)
		{
			delay_us(1000);
			if(k3==0)
			{
				humimin--;
				if(humimin<=0)
					humimin=0;
			}
			while(!k3);
		}
	}
}

#endif