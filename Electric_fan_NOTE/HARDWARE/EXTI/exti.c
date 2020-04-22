#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

//外部中断0服务程序
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOB.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//KEY1
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
//	  //GPIOB6	  中断线以及中断初始化配置 下降沿触发 //KEY2
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
//  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
//	
//	//GPIOB7	  中断线以及中断初始化配置 下降沿触发 //KEY3
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
//  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);

}


 


 
