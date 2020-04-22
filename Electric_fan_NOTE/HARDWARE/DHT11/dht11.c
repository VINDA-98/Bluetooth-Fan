//#include "dht11.h"
//#include "delay.h"

// //////////////////////////////////////////////////////////////////////////////////	 
////������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
////ALIENTEKս��STM32������
////DHT11������ʪ�ȴ�������������	   
////����ԭ��@ALIENTEK
////������̳:www.openedv.com
////�޸�����:2012/9/12
////�汾��V1.0
////��Ȩ���У�����ؾ���
////Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
////All rights reserved									  
////////////////////////////////////////////////////////////////////////////////////
//      
////��λDHT11
//void DHT11_Rst(void)	   
//{                 
//	DHT11_IO_OUT(); 	//SET OUTPUT
//    DHT11_DQ_OUT=0; 	//����DQ
//    delay_ms(20);    	//��������18ms
//    DHT11_DQ_OUT=1; 	//DQ=1 
//	delay_us(30);     	//��������20~40us
//}
////�ȴ�DHT11�Ļ�Ӧ
////����1:δ��⵽DHT11�Ĵ���
////����0:����
//u8 DHT11_Check(void) 	   
//{   
//	u8 retry=0;
//	DHT11_IO_IN();//SET INPUT	 
//    while (DHT11_DQ_IN&&retry<100)//DHT11������40~80us
//	{
//		retry++;
//		delay_us(1);
//	};	 
//	if(retry>=100)return 1;
//	else retry=0;
//    while (!DHT11_DQ_IN&&retry<100)//DHT11���ͺ���ٴ�����40~80us
//	{
//		retry++;
//		delay_us(1);
//	};
//	if(retry>=100)return 1;	    
//	return 0;
//}
////��DHT11��ȡһ��λ
////����ֵ��1/0
//u8 DHT11_Read_Bit(void) 			 
//{
// 	u8 retry=0;
//	while(DHT11_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
//	{
//		retry++;
//		delay_us(1);
//	}
//	retry=0;
//	while(!DHT11_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
//	{
//		retry++;
//		delay_us(1);
//	}
//	delay_us(40);//�ȴ�40us
//	if(DHT11_DQ_IN)return 1;
//	else return 0;		   
//}
////��DHT11��ȡһ���ֽ�
////����ֵ������������
//u8 DHT11_Read_Byte(void)    
//{        
//    u8 i,dat;
//    dat=0;
//	for (i=0;i<8;i++) 
//	{
//   		dat<<=1; 
//	    dat|=DHT11_Read_Bit();
//    }						    
//    return dat;
//}
////��DHT11��ȡһ������
////temp:�¶�ֵ(��Χ:0~50��)
////humi:ʪ��ֵ(��Χ:20%~90%)
////����ֵ��0,����;1,��ȡʧ��
//u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
//{        
// 	u8 buf[5];
//	u8 i;
//	DHT11_Rst();
//	if(DHT11_Check()==0)
//	{
//		for(i=0;i<5;i++)//��ȡ40λ����
//		{
//			buf[i]=DHT11_Read_Byte();
//		}
//		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
//		{
//			*humi=buf[0];
//			*temp=buf[2];
//		}
//	}else return 1;
//	return 0;	    
//}
////��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
////����1:������
////����0:����    	 
//u8 DHT11_Init(void)
//{	 
// 	GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PG�˿�ʱ��
//	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //PG11�˿�����
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);				 //��ʼ��IO��
// 	GPIO_SetBits(GPIOB,GPIO_Pin_11);						 //PG11 �����
//			    
//	DHT11_Rst();  //��λDHT11
//	return DHT11_Check();//�ȴ�DHT11�Ļ�Ӧ
//} 



#include "dht11.h"



/*
 * ��������DHT11_GPIO_Config
 * ����  ������DHT11�õ���I/O��
 * ����  ����
 * ���  ����
 */

 
 
void DHT11_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����DHT11_PORT������ʱ��*/
	RCC_APB2PeriphClockCmd(DHT11_CLK, ENABLE); 

	/*ѡ��Ҫ���Ƶ�DHT11_PORT����*/															   
  	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��DHT11_PORT*/
  	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);		  

	/* ����GPIOB10	*/
	GPIO_SetBits(DHT11_PORT, GPIO_Pin_10);	 
}

/*
 * ��������DHT11_Mode_IPU
 * ����  ��ʹDHT11-DATA���ű�Ϊ��������ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  	/*ѡ��Ҫ���Ƶ�DHT11_PORT����*/	
	  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;

	   /*��������ģʽΪ��������ģʽ*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 

	  /*���ÿ⺯������ʼ��DHT11_PORT*/
	  GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

/*
 * ��������DHT11_Mode_Out_PP
 * ����  ��ʹDHT11-DATA���ű�Ϊ�������ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*ѡ��Ҫ���Ƶ�DHT11_PORT����*/															   
  	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*���ÿ⺯������ʼ��DHT11_PORT*/
  	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 	 
}

/* 
 * ��DHT11��ȡһ���ֽڣ�MSB����
 */
static uint8_t Read_Byte(void)
{
	uint8_t i, temp=0;

	for(i=0;i<8;i++)    
	{	 
		/*ÿbit��50us�͵�ƽ���ÿ�ʼ����ѯֱ���ӻ����� ��50us �͵�ƽ ����*/  
		while(DHT11_DATA_IN()==Bit_RESET);

		/*DHT11 ��26~28us�ĸߵ�ƽ��ʾ��0������70us�ߵ�ƽ��ʾ��1����
		 *ͨ����� x us��ĵ�ƽ��������������״ ��x ���������ʱ 
		 */
		delay_us(40); //��ʱx us �����ʱ��Ҫ��������0������ʱ�伴��	   	  

		if(DHT11_DATA_IN()==Bit_SET)/* x us����Ϊ�ߵ�ƽ��ʾ���ݡ�1�� */
		{
			/* �ȴ�����1�ĸߵ�ƽ���� */
			while(DHT11_DATA_IN()==Bit_SET);

			temp|=(uint8_t)(0x01<<(7-i));  //�ѵ�7-iλ��1��MSB���� 
		}
		else	 // x us��Ϊ�͵�ƽ��ʾ���ݡ�0��
		{			   
			temp&=(uint8_t)~(0x01<<(7-i)); //�ѵ�7-iλ��0��MSB����
		}
	}
	return temp;
}
/*
 * һ�����������ݴ���Ϊ40bit����λ�ȳ�
 * 8bit ʪ������ + 8bit ʪ��С�� + 8bit �¶����� + 8bit �¶�С�� + 8bit У��� 
 */
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  
	/*���ģʽ*/
	DHT11_Mode_Out_PP();
	/*��������*/
	DHT11_DATA_OUT(LOW);
	/*��ʱ18ms*/
	//Delay_ms(18);
	delay_us(18000);

	/*�������� ������ʱ30us*/
	DHT11_DATA_OUT(HIGH); 

	delay_us(30);   //��ʱ30us

	/*������Ϊ���� �жϴӻ���Ӧ�ź�*/ 
	DHT11_Mode_IPU();

	/*�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������*/   
	if(DHT11_DATA_IN()==Bit_RESET)     
	{
		/*��ѯֱ���ӻ����� ��80us �͵�ƽ ��Ӧ�źŽ���*/  
		while(DHT11_DATA_IN()==Bit_RESET);

		/*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ���*/
		while(DHT11_DATA_IN()==Bit_SET);

		/*��ʼ��������*/   
		DHT11_Data->humi_int= Read_Byte();

		DHT11_Data->humi_deci= Read_Byte();

		DHT11_Data->temp_int= Read_Byte();

		DHT11_Data->temp_deci= Read_Byte();

		DHT11_Data->check_sum= Read_Byte();


		/*��ȡ���������Ÿ�Ϊ���ģʽ*/
		DHT11_Mode_Out_PP();
		/*��������*/
		DHT11_DATA_OUT(HIGH);

		/*����ȡ�������Ƿ���ȷ*/
		if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci)
			return SUCCESS;
		else 
			return ERROR;
	}
	else
	{		
		return ERROR;
	}   
}

	  


/*************************************END OF FILE******************************/








