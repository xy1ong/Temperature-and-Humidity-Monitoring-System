#ifndef __LCD1602_H__
#define __LCD1602_H__

void write_cmd(uint8 com)	 //写命令
{
	e=0;
	rs=0;        //命令选择
	delay_us(50);
	rw=0;        //写选择
	delay_us(50);
	P0=com;      //端口赋值
	e=1;         //高脉冲
	delay_us(50);
	e=0;
}
void write_data(uint8 datas)	  //写数据
{
	e=0;
	rs=1;         //数据选择
	delay_us(50);
	rw=0;	        //写选择
	delay_us(50);
	P0=datas;     //端口赋值
	delay_us(50);
	e=1;
	delay_us(50);
	e=0;
	rs=0;         //命令选择
}
void lcd_init()	   //LCD1602初始化
{
	write_cmd(0x38);   //模式设置：16*2显示，5*7点阵，8位数据接口
	delay_ms(5);
	write_cmd(0x06);	//显示模式：读写字符后地址加1，屏显不移动
	delay_ms(5);
	write_cmd(0x0c);	//显示设置：显示开关控制，不显示光标，光标不闪烁
	delay_ms(5);
	write_cmd(0x01);	//清屏，数据指针清零
	delay_ms(5);
}

//LCD复位显示
void lcd_init_display()
{
	uint8 i;
	for(i=0;i<7;i++)
	{
		write_cmd(0x80+i);
		write_data(info1[i]);	
	}

	for(i=0;i<7;i++)
	{
		write_cmd(0xc0+i);
		write_data(info2[i]);	
	}
}
#endif