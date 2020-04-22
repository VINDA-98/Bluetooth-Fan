#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "delay.h"
#include "oled.h"
#include "lanya.h"

void Blue(void)
{
		u16  i,bule;
// PWM2 右边 关闭可实现右转
		i=USART_ReceiveData(USART1);
		bule=i;    //蓝牙接收到的值
		OLED_ShowNum(60,4,bule,3,12);//蓝牙值显示
//		u16 zuobizhang,youbizhang;
//	    zuobizhang=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15);//避障左边传感器
//	    youbizhang=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14);
		TIM_SetCompare2(TIM3,1000);	
		
}







