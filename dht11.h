#ifndef __DHT11_H__
#define __DHT11_H__

//复位DHT11
void dht11_reset()	   
{                 
	dht11_data=0; 	//拉低数据位
	delay_ms(20);   //低电平保持时间不能小于18ms
	dht11_data=1;
	delay_us(4);     	//拉高持续20~40us
}


/***********************
* 函数功能：检查是否存在DHT11
* 返回值：0，检测到DHT11
*         1，未检测到DHT11
***********************/
uint8 dht11_conf() 	   
{   
	uint8 retry=0;
	
	//首先等待DHT11输出80us低电平作为应答信号（响应信号）
	while(dht11_data&&retry<100)
	{
		retry++;
		_nop_();        //延时一个机器周期（约1微秒）
	};
	
	if(retry>=100)
		return 1;      //未检测到DHT11
	else
		retry=0;       //进行下一步检查
	
	//然后等待DHT11拉高80us通知外设准备接收数据
  while(!dht11_data&&retry<100)
	{
		retry++;
		_nop_();
	};
	if(retry>=100)
		return 1;	     //检测DHT11状态失败
	return 0;
}


/***********************
* 函数功能：DHT11初始化
* 返回值：0，初始化成功
*         1，初始化失败
***********************/
uint8 dht11_init()
{
	dht11_reset();	  
	return dht11_conf();	
}

void delay30us(void)   //误差 0us
{
    unsigned char a,b;
    for(b=3;b>0;b--)
        for(a=3;a>0;a--);
}
/***********************
* 函数功能：从DHT11读取一位数据
* 函数说明：读取每一位数据时，先把50微秒的低电平等过去，然后判断高电平的时长
* 返回值：0，位数据为0（50微秒的低电平和26-28微秒的高电平）
*         1，位数据为1（50微秒的低电平加70微秒的高电平）
***********************/
uint8 dht11_rd1bit(void) 			 
{
 	uint8 retry=0;
	while(dht11_data&&retry<100)//等待变为低电平 12-14us 开始
	{
		retry++;
		_nop_();
	}
	retry=0;
	while(!dht11_data&&retry<100)//等待变高电平	 
	{
		retry++;
		_nop_();
	}
	
	//等待30微秒后判断是在继续保持高电平还是进行下一位读取等待50微秒低电平来确定1或0
	delay30us();  //高电平持续时长26~28us（这里取30us，是要大于此时长）为止表示0,而继续保持高电平42~44us为止表示1
	if(dht11_data)
		return 1;
	else
		return 0;		   
}


/***********************
* 函数功能：从DHT11读取一个字节数据
* 返回值：读到的数据
***********************/
uint8 dht11_rd1byte(void)    
{
	uint8 i,datas=0;
	for (i=0;i<8;i++) 
	{
		datas<<=1;
		datas|=dht11_rd1bit();
	}
	return datas;
}


/***********************
* 函数功能：从DHT11读取一次数据（8字节）
* 返回值：0，读取成功
					1，读取失败
***********************/
uint8 dht11_rd8byte(uint8 *cetemp,uint8 *rehumi)    
{        
 	uint8 buf[5];
	uint8 i;
	dht11_reset();
	if(dht11_conf()==0)
	{
		for(i=0;i<5;i++)  //读取8字节数据
		{
			buf[i]=dht11_rd1byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])  //与校验位对比
		{
			*rehumi=buf[0];   //湿度高8位
			*cetemp=buf[2];   //温度高8位
		}
	}
	else
		return 1;
	return 0;	    
}

#endif