#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED1 PCout(13)// PC13
#define BEEP PBout(12)// PB13
#define HC_SR501 PAin(4)  //PAI(4)是位绑定，方便操作用的，
	
/*	15：红
	14：绿
	13：蓝*/
#define LED_RED    PBout(13)	// PB15
#define LED_Green  PBout(14)	// PB14
#define LED_Blue   PBout(15)	// PB13

void LED_Init(void);//初始化
void HC_SR501Init(void);
void show_ThreeLED(void);
void show_BlueLED(void);
void show_GreenLED(void);
void show_RedLED(void);
u8 HC_SR501_Statue(void);//是为了判断PA0输入状态，如果被拉高了，说明有人进入了		 				    
#endif
