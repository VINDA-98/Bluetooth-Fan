//#ifndef __DHT11_H
//#define __DHT11_H 
//#include "sys.h"   
////////////////////////////////////////////////////////////////////////////////////	 
////本程序只供学习使用，未经作者许可，不得用于其它任何用途
////ALIENTEK战舰STM32开发板
////DHT11数字温湿度传感器驱动代码	   
////正点原子@ALIENTEK
////技术论坛:www.openedv.com
////修改日期:2012/9/12
////版本：V1.0
////版权所有，盗版必究。
////Copyright(C) 广州市星翼电子科技有限公司 2009-2019
////All rights reserved									  
////////////////////////////////////////////////////////////////////////////////////
// 
////IO方向设置
//#define DHT11_IO_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
//#define DHT11_IO_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
//////IO操作函数											   
//#define	DHT11_DQ_OUT PBout(8) //数据端口	PA0 
//#define	DHT11_DQ_IN  PBin(8)  //数据端口	PA0 


//u8 DHT11_Init(void);//初始化DHT11
//u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
//u8 DHT11_Read_Byte(void);//读出一个字节
//u8 DHT11_Read_Bit(void);//读出一个位
//u8 DHT11_Check(void);//检测是否存在DHT11
//void DHT11_Rst(void);//复位DHT11    
//#endif


#ifndef __DHT11_H
#define	__DHT11_H

#include "stm32f10x.h"
#include "delay.h"


#define HIGH  1
#define LOW   0

#define DHT11_CLK     RCC_APB2Periph_GPIOB
#define DHT11_PIN     GPIO_Pin_8                 
#define DHT11_PORT	  GPIOB 

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_8)
 //读取引脚的电平
#define  DHT11_DATA_IN()	   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
					

					
					

typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
}DHT11_Data_TypeDef;

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte(void);



#endif /* __DHT11_H */




















