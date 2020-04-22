#include "led.h"
#include "delay.h"

void LED_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
	 //ѡ��˿�
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PC13�˿�����
	//ѡ��ģʽ
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	//ѡ�����ٶ�
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	//�������ȷ�ϳ�ʼ��ѡ�ж˿�
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��PC13.5
	//���е�ѹ����û�е�ѹ
	 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PB.5 �����	
	//GPIO_ResetBits
	
	/*15����
	  14����
	  13����*/
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//LED0-->PB.5 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);						 //�����趨������ʼ��GPIOB.5
	 GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //�ص�������
	 GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //�ص�	
	 GPIO_ResetBits(GPIOB,GPIO_Pin_14);						 //�ص�	
	 GPIO_ResetBits(GPIOB,GPIO_Pin_15);						 //�ص�	
}

/*������ɫ��ʾ*/
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

/*���*/
void show_RedLED(void){
	LED_RED=1;
	delay_ms(500);
	LED_RED=0;
	delay_ms(500);
}

/*�̵�*/
void show_GreenLED(void){
	LED_Green=1;
	delay_ms(500);
	LED_Green=0;
	delay_ms(500);
}

/*����*/
void show_BlueLED(void){
	LED_Blue=1;
	delay_ms(500);
	LED_Blue=0;
	delay_ms(500);
}


/*ʹ�ú���GPIO_ReadInputData(GPIOE)�ɽ�E�ڵ���������һ�ζ��أ�
Ҳ����ʹ��GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)�������ŵ�������*/
void HC_SR501Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);//��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//ѡ��0����
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPD;//����Ϊ��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);						 //PB.4 �����
}

u8 HC_SR501_Statue(void)
{
	if(HC_SR501==1){
		return 1;
	}else return 0;
}
