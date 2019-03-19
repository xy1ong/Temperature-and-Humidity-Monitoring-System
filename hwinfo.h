#ifndef __HWINFO_H__
#define __HWINFO_H__

typedef unsigned char uint8;  //单字节无符号整数
typedef unsigned int uint16;  //双字节无符号整数
//参考原理图
sbit rs=P2^6;	          //数据命令选择
sbit rw=P2^5;	          //读写选择
sbit e=P2^7;	          //使能

//定义按键接口
sbit k1=P2^2;           //设定温度或湿度上下限
sbit k2=P2^3;           //温（湿）度加
sbit k3=P2^4;           //温（湿）度减

sbit dht11_data=P1^2;   //DHT11串行数据（单总线）端口
sbit hcsr501_data=P1^3;     //人体感应模块HC-SR501数据端口
sbit beep=P1^4;

sbit led1=P1^0;         //降温湿指示灯
sbit led2=P1^1;         //升温湿指示灯

uint8 mode=0;           //k1模式

//缺省温湿度上下限
char tempmax=38,tempmin=23;
char humimax=80,humimin=30;

uint8 cetemp,rehumi;
uint8 flag;	            //设置报警标志

//定义以下数据放在程序存储区中，不能更改
uint8 code info1[]="CeTemp:";     //摄氏温度
uint8 code info2[]="ReHumi:";     //相对湿度
uint8 code info3[]="Error";       //DHT11初始化错误
uint8 code info4[]="%RH";         //相对湿度：空气中水汽压与相同温度下饱和水汽压之比。
uint8 code info5[]="TempMax:";	  //设定温度上限显示
uint8 code info6[]="TempMin:";	  //设定温度下限显示
uint8 code info7[]="HumiMax:";	  //设定湿度上限显示
uint8 code info8[]="HumiMin:";	  //设定湿度下限显示

//延时time*10微秒
void delay_us(uint16 time)
{
	while(time--);
}

//延时time毫秒
void delay_ms(uint16 time)
{
	while(time--)
		delay_us(90);
}

#endif