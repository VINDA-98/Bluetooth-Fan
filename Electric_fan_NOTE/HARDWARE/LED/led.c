#include "led.h"
#include "delay.h"

void LED_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);	 //使能PB,PE端口时钟
	
	 //选择端口
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PC13端口配置
	//选择模式
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	//选择工作速度
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	//配置完毕确认初始化选中端口
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PC13.5
	//给有电压还是没有电压
	 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PB.5 输出高	
	//GPIO_ResetBits
	
	/*15：红
	  14：绿
	  13：蓝*/
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//LED0-->PB.5 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);						 //根据设定参数初始化GPIOB.5
	 GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //关掉蜂鸣器
	 GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //关灯	
	 GPIO_ResetBits(GPIOB,GPIO_Pin_14);						 //关灯	
	 GPIO_ResetBits(GPIOB,GPIO_Pin_15);						 //关灯	
}

/*三种颜色显示*/
void show_ThreeLED(void){
	LED_Blue=1;										
	LED_Green=1;
	LED_RED=1;
	delay_ms(500);
	LED_Blue=0;									
	LED_Green=0;
	LED_RED=0;
	delay_ms(500);
}

/*红灯*/
void show_RedLED(void){
	LED_RED=1;
	delay_ms(500);
	LED_RED=0;
	delay_ms(500);
}

/*绿灯*/
void show_GreenLED(void){
	LED_Green=1;
	delay_ms(500);
	LED_Green=0;
	delay_ms(500);
}

/*蓝灯*/
void show_BlueLED(void){
	LED_Blue=1;
	delay_ms(500);
	LED_Blue=0;
	delay_ms(500);
}


/*使用函数GPIO_ReadInputData(GPIOE)可将E口的所有引脚一次读回，
也可以使用GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)将改引脚单独读回*/
void HC_SR501Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);//打开GPIOA时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//选中0引脚
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPD;//配置为下拉输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);						 //PB.4 输出高
}

u8 HC_SR501_Statue(void)
{
	if(HC_SR501==1){
		return 1;
	}else return 0;
}
