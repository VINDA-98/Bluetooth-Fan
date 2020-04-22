#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED1 PCout(13)// PC13
#define BEEP PBout(12)// PB13
#define HC_SR501 PAin(4)  //PAI(4)��λ�󶨣���������õģ�
	
/*	15����
	14����
	13����*/
#define LED_RED    PBout(13)	// PB15
#define LED_Green  PBout(14)	// PB14
#define LED_Blue   PBout(15)	// PB13

void LED_Init(void);//��ʼ��
void HC_SR501Init(void);
void show_ThreeLED(void);
void show_BlueLED(void);
void show_GreenLED(void);
void show_RedLED(void);
u8 HC_SR501_Statue(void);//��Ϊ���ж�PA0����״̬������������ˣ�˵�����˽�����		 				    
#endif
