#ifndef __DATAHD_H__
#define __DATAHD_H__

//温湿度数据处理
void data_handle()
{
	uint8 i;  	    
	uint8 temp_buf[2],humi_buf[2];     //实时温度缓冲变量
	uint8 temphbuf[2],templbuf[2],humihbuf[2],humilbuf[2];  //温湿度上下限缓冲变量

	//读取温湿度值
	dht11_rd8byte(&cetemp,&rehumi);
	
	//温度分位存储
	temp_buf[0]=cetemp/10+0x30;	 //0x30：字符'0'
	temp_buf[1]=cetemp%10+0x30;

	//湿度分位存储
	humi_buf[0]=rehumi/10+0x30;	
	humi_buf[1]=rehumi%10+0x30;
	
	//温度上下限字符转化
	temphbuf[0]=tempmax/10;
	temphbuf[1]=tempmax%10;
	templbuf[0]=tempmin/10;
	templbuf[1]=tempmin%10;

	//湿度上下限字符转化
	humihbuf[0]=humimax/10;
	humihbuf[1]=humimax%10;
	humilbuf[0]=humimin/10;
	humilbuf[1]=humimin%10;

	if(mode==0)
	{
		lcd_init_display();
		write_cmd(0x87);
		write_data(temp_buf[0]);  //温度十位数
		write_data(temp_buf[1]);  //温度个位数
		write_data(0xdf);   //字符'°'
		write_data('C');
	
		for(i=0;i<2;i++)
		{
			write_cmd(0Xc7+i);
			write_data(humi_buf[i]);		  
		}	
		for(i=0;i<3;i++)
		{
			write_cmd(0Xc9+i);
			write_data(info4[i]);
		}	
	}
	
	//显示设置温湿度上下限
	if(mode==1)			  //温度上限显示
	{
		write_cmd(0x80);
		for(i=0;i<8;i++)
		{
			write_data(info5[i]);		  
		}
		write_data(temphbuf[0]);
		write_data(temphbuf[1]);			
	}
	if(mode==2)			  //温度下限显示
	{
		write_cmd(0x80);
		for(i=0;i<8;i++)
		{
			write_data(info6[i]);		  
		}
		write_data(templbuf[0]);
		write_data(templbuf[1]);			
	}
	if(mode==3)			  //湿度上限显示
	{
		write_cmd(0x80);
		for(i=0;i<8;i++)
		{
			write_data(info7[i]);		  
		}
		write_data(humihbuf[0]);
		write_data(humihbuf[1]);			
	}
	if(mode==4)			  //湿度下限显示
	{
		write_cmd(0x80);
		for(i=0;i<8;i++)
		{
			write_data(info8[i]);		  
		}
		write_data(humilbuf[0]);
		write_data(humilbuf[1]);			
	}
}

#endif