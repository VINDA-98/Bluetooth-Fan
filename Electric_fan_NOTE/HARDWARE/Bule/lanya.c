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
// PWM2 �ұ� �رտ�ʵ����ת
		i=USART_ReceiveData(USART1);
		bule=i;    //�������յ���ֵ
		OLED_ShowNum(60,4,bule,3,12);//����ֵ��ʾ
//		u16 zuobizhang,youbizhang;
//	    zuobizhang=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15);//������ߴ�����
//	    youbizhang=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14);
		TIM_SetCompare2(TIM3,1000);	
		
}







