/*
����Ŀ��������������
����ʱ��2019.9.28��12.24
�����ˣ�Τ��
�Ŷ�ԭ��

������������ʵ�ֹ������£�
1�������������ݴ���      PA9 PA10
2��������������ģʽ�л�  PB5
3����������ת�١���ʱ    PB6��PB7
4���Զ�������˻��� 	    PA4
5��DHT11������ʪ�ȼ��   PB11
6��OLED��ʾ        	    PCout(14)//SCL   ����ʱ�� PCout(15)//SDA	
7�����ⱨ��װ�ã�		BEEP��  P12        LED2��PB13(��)��14(��ɫ)��15(��ɫ)
*/
#include "sys.h"
#include "delay.h"
#include "usart.h"	
#include "exti.h"
#include "led.h"    	/*��*/
#include "key.h"	/*����*/ 
#include "oled.h"    /*��Ļ*/
#include "dht11.h"	/*��ʪ��*/
#include "pwm.h"	/*����PWM*/
#include "stdlib.h"

u32 time=0;					  	  /*������ʱ��ʱ�䣬��λ����*/
DHT11_Data_TypeDef DHT11_Data;    /*��ʪ�����ݽṹ��*/
u8  temperature,humidity;  	  	  /*DHT11�¶���ʪ��*/
u8  Interface=0,Interface1=0;     /*�����л�����*/
u8  add=0,add1=0;    			/*����л���λ����*/
u16 receive=0;  		 		/*�������ջ���������*/
u16 Speed=0;     		 		/*���ת�ٱ�־��*/  
u16 buff=0;  				    /*�ٷֱȻ�������*/
u32 User_Time=0; 	 			/*�û���ʱ����*/
u8  Open_time=0; 				 /*1��ʱ����û����������ʱ���رշ��ȣ�2��ʱ�����������ƶ�ʱʱ�䣬3�Ǵ�ͳ��ʱ*/
u8  temp_up=0,temp_dowm=0;  	  /*�û��������ػ��¶�*/
u8  Receive_Buff[USART_REC_LEN];  /*���ջ�������*/
u8  timeBuff[3]; 	/*ʱ�仺������*/
u8  send_flag=0;  	/*DHT11�������ݱ�־��*/
u8  zhuansu=0;	 	//�¿�ת���ж�
u16 Sleep_pwmval=0; /*˯�߿��Ƶ�PWM����*/
u8 dir=1,dir1=0;	         /*˯�߿����Ƿ�������*/
u8 temperature_buff[2],Intelligence_time=0;//����ģʽ�µĻ�������
u8 time_DHT11=0,time1_DHT11=0,read_IO;//DHT11�����ӳ���  read_IO��ȡ������IO����

//�����ʼ��
void Init_face(){

	/*��ʼ������*/
	OLED_P6x8Str(9,1,"Mode : ");
	OLED_P6x8Str(9,3,"Time : ");
	OLED_P6x8Str(9,5,"Temp : ");
	OLED_P6x8Str(9,7,"water: ");
	OLED_P6x8Str(9+65,0,"Speed:");
	OLED_ShowChar(9+45+18,2,'H');	//��ʾСʱ
	OLED_ShowChar(9+75+18,2,'M');	//��ʾ����
	OLED_ShowChar(69,4,'.');	    //��ʾС����	
	OLED_ShowChar(69,6,'.');	    //��ʾС����	
	OLED_ShowChar(90,4,'C');	    //��ʾC
	OLED_ShowChar(90,6,'%');	    //��ʾ%	
}

/*ģʽ�л�ָʾ��*/
void LED_change(){

		LED_Green=!LED_Green;  /*ģʽ�л�ָʾ��*/
		delay_ms(500);
		LED_Green=!LED_Green;
		delay_ms(500);
}

/*�ɹ�����ָʾ����˸*/
void LED_Succeed(){

		LED_Blue=!LED_Blue;  /*ģʽ�л�ָʾ��*/
		delay_ms(100);
		LED_Blue=!LED_Blue;
		delay_ms(100);
		LED_Blue=!LED_Blue;  /*ģʽ�л�ָʾ��*/
		delay_ms(100);
		LED_Blue=!LED_Blue;
		delay_ms(100);
		LED_Blue=0;
	
}

/*��ʱ�ر�����*/
void LED_Close(){
	 BEEP=!BEEP;
	 LED_RED=!LED_RED;            //û�˴��ڵ�ʱ���Ʊ���
	 delay_ms(200);
	 BEEP=!BEEP;
	 LED_RED=!LED_RED;            //û�˴��ڵ�ʱ���Ʊ��
	 delay_ms(200);
}

//����ģʽ
void Intelligence_Mode(){

	/*1�������¶ȸı�PWM��� 15-40�� PWM��Χ��
	   2����Ъ�Դ���*/
	Intelligence_time++;
	delay_ms(30);
	if(Intelligence_time%100==0)  //ÿ3S��ȡһ��
	{
				Intelligence_time=0;
				//DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
				temperature_buff[0]	= temperature;			/*���ػ���*/
				
				OLED_ShowNum(65,4,temperature,2,16);	    //��ʾ�¶�	
				OLED_ShowNum(65,6,humidity,2,16);				//��ʾʪ��	
				
				//�ٶ������¶ȱ仯�ı�PWM
		
				if(temperature_buff[0]==15){
						Speed =0;
						OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
						TIM_SetCompare1(TIM3,0);
				}
				if(temperature_buff[0]<15){
						Speed = 1100/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
						TIM_SetCompare1(TIM3,1100);
				}
				
				if(temperature_buff[0]>15&&temperature_buff[0]>20){
					   Speed = 1200/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
						TIM_SetCompare1(TIM3,1200); 
				}
				
				if(temperature_buff[0]>20&&temperature_buff[0]>25){
					    Speed = 1250/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�						
						TIM_SetCompare1(TIM3,1250);  
				}
				
				if(temperature_buff[0]>25&&temperature_buff[0]>30){
						Speed = 1300/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
						TIM_SetCompare1(TIM3,1300); 
				}
				
				if(temperature_buff[0]>30&&temperature_buff[0]>35){
						Speed = 1380/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
						TIM_SetCompare1(TIM3,1380);   
				}

				if(temperature_buff[0]>35){
						Speed = 1420/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
						TIM_SetCompare1(TIM3,1420);  
				}
	}
}

//��������ת�١���ʱ  PB6��PB7
void Shift_PWM(){

	/*PB6���£�������λ*/ 
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)
	{
		delay_ms(120);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)
		{			
			add+=1;
			if(add>3)add=0;
		}
	}
	
	/*PB7���£���ͳ��ʱ��ť*/ 
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0){
		delay_ms(120);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)
		{			
			/*��ͳ��ʱÿ�ΰ��¶�ʮ���ӣ�ֻ��1-3Сʱ*/
			User_Time+=10;
			if(User_Time<60)
			{
				TIM_Cmd(TIM2, ENABLE);
				Open_time=3;
				timeBuff[1]=0;
				timeBuff[2]=User_Time;
			}
			
			if(User_Time>60&&User_Time<120){
				TIM_Cmd(TIM2, ENABLE);
				Open_time=3;
				timeBuff[1]=1;
				timeBuff[2]=60-(120-User_Time);
			}
			
			if(User_Time>120&&User_Time<180){
				TIM_Cmd(TIM2, ENABLE);
				Open_time=3;
				timeBuff[1]=2;
				timeBuff[2]=60-(180-User_Time);
			}
			
			switch(User_Time){
				case 60:
				TIM_Cmd(TIM2, ENABLE);
				Open_time=3;
				timeBuff[1]=1;
				timeBuff[2]=0;break;
				case 120:
				TIM_Cmd(TIM2, ENABLE);
				Open_time=3;
				timeBuff[1]=2;
				timeBuff[2]=0;break;
				case 180:
				TIM_Cmd(TIM2, ENABLE);
				Open_time=3;
				timeBuff[1]=3;
				timeBuff[2]=0;break;
			}
			
			if(User_Time>180){
				TIM_Cmd(TIM2, DISABLE);
				User_Time=0;
				timeBuff[1]=0;
				timeBuff[2]=0;
			}	
			
			OLED_ShowNum(9+45,2,timeBuff[1],2,16); //Сʱ
			OLED_ShowNum(9+75,2,timeBuff[2],2,16); //����
			printf("��ʱʱ�䣺 %dH,%dmin\r\n",timeBuff[1],timeBuff[2]);					
		}
	}
	
	//0��ʱ�򲻶���1��ʱ��һ����2��ʱ�������3��ʱ������
	if(add==0)
	{
		if(add1==0){
			add1=1;
			Speed = 0;
			OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
			TIM_SetCompare1(TIM3,Speed);  	  //����
			printf("�ػ�\r\n");					
		}
	}
	//һ��
	if(add==1)
	{
		if(add1==1){
			add1=2;
			Speed = 30;
			OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
			TIM_SetCompare1(TIM3,Speed*38);   //һ��
			printf("һ��\r\n");						
		}
	}
	//����
	if(add==2)
	{
		if(add1==2){
			add1=3;
			Speed = 60;
			OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
			TIM_SetCompare1(TIM3,Speed*21);   //����
			printf("����\r\n");				
		}
	}
	//����
	if(add==3)
	{
		if(add1==3){
			add1=0;
			Speed = 90;
			OLED_ShowNum(9+100,0,Speed,2,16); //�ٶ�
			TIM_SetCompare1(TIM3,Speed*15.5);  //����
			printf("����\r\n");	
		}
	}
}

void Read_Peopel(){

	//����Ƿ����˶�ȡ����ŵ�ֵ
		read_IO=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
		//LED1=0;  	 	 /*LED=0��������˼*/ 
		if(read_IO==0){
			LED_RED=0;   	 /*�͵�ƽ��ʱ����û���˵ģ��ߵ�ƽ�����˵ģ�û�˵�ʱ��Ĭ�Ϲر�*/
			Open_time=1;/*���ж϶�ʱ����������Ϊ1��Open_time=1��ʾ��ʱ����*/
			TIM_Cmd(TIM2, ENABLE);  //û��ʱ��򿪶�ʱ��		
			printf("��������\r\n");								
		}
		else{
			//����ģʽ������Ѿ�������ʱģʽ�����˵������ҲҪ�򿪶�ʱ��
			if(Open_time==2)TIM_Cmd(TIM2, ENABLE);   	    //��������Ѿ���ʱ��
			
			else if(Open_time==3)TIM_Cmd(TIM2, ENABLE);   //�����ͳ�Ѿ���ʱ
			
			else TIM_Cmd(TIM2, DISABLE); 		     	  //Ҫ��������������������ڵ�ʱ��رն�ʱ��
			LED_RED=1;  				 	 			  /*���˵�ʱ��LED=0��ʼ������*/
			printf("��������\r\n");
		}	
}

//DHT11�����ϴ�
void DHT11_Start(){

	if(send_flag==1)
		{
			Read_DHT11(&DHT11_Data);//��ȡ��ʪ��ֵ	
			//DHT11_Read_Data(&temperature,&humidity);					    
			OLED_ShowNum(65,4,DHT11_Data.temp_int,2,16);		//��ʾ�¶�	
			OLED_ShowNum(65,6,DHT11_Data.humi_int,2,16);		//��ʾʪ��
			USART_SendData(USART1,0x52);  					//��⵽0x52���㿪ʼ
			delay_ms(100);  
			USART_SendData(USART1,DHT11_Data.temp_int); //�����¶ȵ�ʮ������
			delay_ms(1000);
			USART_SendData(USART1,DHT11_Data.humi_int);	//����ʪ�ȵ�ʮ������
			delay_ms(100);
			USART_SendData(USART1,0x53);//��⵽0x53�������
			delay_ms(100);
		if(zhuansu==1)
		{
			if(temperature>temp_up)  /*�����¶�����*/
			{
				TIM_SetCompare1(TIM3,1500);
			}
			
			if(temperature<temp_dowm) /*�����¶�����*/
			{
				TIM_SetCompare1(TIM3,1100);
			}
		}
	}
		//	printf("�����¶�Ϊ��%d��\r\n",temperature);	
		//	printf("����ʪ��Ϊ��%d%%\r\n",humidity);
}

//�Զ���⺯�� DHT11��ʾ1min
void Check(){
	delay_ms(10);
	time_DHT11++;   //ÿ������10ms��һ��Ҫ����һ�ٴ� 10ms*10 = 100ms
	if(time_DHT11==15)
	{
		time_DHT11=0; /*����0����*/
		time1_DHT11++;
		//time_DHT11=10��time1_DHT11=120 �����ʱ��45S
		if(time1_DHT11==200)  // time1_DHT11=200��time_DHT11==15�õ�116S  ���������
		{
			time1_DHT11=0;
			send_flag=1;       /*DHT11ȷ����������*/
			Read_Peopel();  //��ȡ�����Ƿ��⵽��
			DHT11_Start();	//DHT11�¶���ʾ
			send_flag=0;         /*DHT11�رչ�������*/
		}	
	}
}

//˯��ģʽ
void Sleep_Mode(){
		//��Ъ�Դ���
		Intelligence_time++;
		if(Intelligence_time%100==0)  //ÿ3S��ȡһ��
		{
					//��Ъ�Դ���
					//ȷ���¶Ȳ�ֵ
					Read_DHT11(&DHT11_Data);//��ȡ��ʪ��ֵ					    
					OLED_ShowNum(65,4,DHT11_Data.temp_int,2,16);		//��ʾ�¶�	
					OLED_ShowNum(65,6,DHT11_Data.humi_int,2,16);		//��ʾʪ��
					temperature_buff[0]	= DHT11_Data.temp_int;/*���ػ���*/
		}
		if(temperature_buff[0]<15)dir1=1;
		if(temperature_buff[0]>35)dir1=2;
		if(temperature_buff[0]>15&&temperature_buff[0]<35)dir1=0;
		switch(dir1){
			case 0:			
			delay_ms(50);	 
			if(dir)Sleep_pwmval+=50;
			else Sleep_pwmval-=50;	
			TIM_SetCompare1(TIM3,Sleep_pwmval);
			if(Sleep_pwmval>1400)
			{
			TIM_SetCompare1(TIM3,1400);
			delay_ms(5000);
			dir=0;		
			}			
			if(Sleep_pwmval==0)
			{	
			TIM_SetCompare1(TIM3,Sleep_pwmval);
			delay_ms(5000);
			dir=1;	
			}break;

			case 1:	TIM_SetCompare1(TIM3,0);break;
			case 2:	TIM_SetCompare1(TIM3,1500);break;
		}	
}

	
//���������ӳ���
void Bluetooth(){
//��ͳģʽ������ģʽ��˯��ģʽ�л�
	//��ע��һ��Ҫ�ǵ���0D 0A������֡β����Ȼʶ����������ݲ�������
	u8 len,t;
	if(USART_RX_STA&0x8000)
	{				
			/*������	     ʮ����	ʮ������ 	ͼ��
			  0011 0000	   48	    30	     0*/
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			//printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				Receive_Buff[t]=USART_RX_BUF[t];
				//USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
				//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			
			OLED_ShowNum(9+45,0,Receive_Buff[0],2,16);	  /*��ʾ���ν���ģʽ*/
			//������֧����
			switch(Receive_Buff[0])
			{	
				//0x01:�򿪷��ȵ��;
				case 1:TIM_SetCompare1(TIM3,1200);break;
				
				//0x02:�رշ��ȵ��
				case 2:TIM_SetCompare1(TIM3,0); TIM_Cmd(TIM2, DISABLE);send_flag=0;break;
				
				//0x03:�鿴DHT11��ʪ��
				case 3:DHT11_Start();send_flag=1;break; 
				
				//0x10:���ذ�ť���鿴
				case 10:send_flag=0;break; 
				
				//0x04:���ȿ��ƴ�ͳ���ת��1-3��
				case 4:add+=1;if(add>3)add=0;break; 
				
				/*0x05: ���ȿ��ưٷֱȵ��ת�� 0-99%
				  �ٷֱȿ��Ƶ��ת�� Receive_Buff[1]�Ĳο���ΧΪ��0-99
				  ����һ��0x05�����������ֻ��˴����İٷ���*/
				case 5:				
				if(Receive_Buff[1]==0){
					buff=0;/*���0*/
					Speed=0;
				}
				else {
				Speed=Receive_Buff[1];
				OLED_ShowNum(9+100,0,Speed,2,16); 	//�ٶ�//��ʾ�ٶȰٷֱ� 
				buff = (Receive_Buff[1]*1.5)+1200;  /*���ưٷֱ�*/
				}
				TIM_SetCompare1(TIM3,buff);break;
				
				/*
				����1��0x06,����2���¶����ޣ�����3���¶�����
				�¶����޾�һֱ���ת�٣����޾��ǹرշ���**/
				case 6:Open_time=2;
					   temp_up   = Receive_Buff[1];
					   temp_dowm = Receive_Buff[2];				
					   break;
				
				//0x07:��׼��ʱ:1-12H
				//�뵥λ��ʱ������һ��07������������Ҫ��ʱ��Сʱ��������������Ҫ��ʱ�ķ�����
				case 7:Open_time=2;/*���ж϶�ʱ����������Ϊ2*/	
					   User_Time=(Receive_Buff[1]*60+Receive_Buff[2]); /*���㶨ʱ�ܷ�����*/
					   OLED_ShowNum(9+45,2,Receive_Buff[1],2,16); //Сʱ
					   OLED_ShowNum(9+75,2,Receive_Buff[2],2,16); //����
					   TIM_Cmd(TIM2, ENABLE);break;

				/*0x08:����ģʽ:�����¶��Զ����ڷ��١�����ʱ���Զ��ر�*/
				case 8:				
				send_flag=1;//�¶ȿ�
				zhuansu=1;  //ת�ٿ�
				break; 
				
				/*˯��ģʽ*/
				case 9:
				/*1�������¶ȸı�PWM���
				  2����Ъ�Դ���*/
				Sleep_Mode();
				break;
			}
			//printf("\r\n�����͵ĳ���Ϊ:%d\r\n\r\n",len);
			//printf("\r\n");//���뻻��
			USART_RX_STA=0;
			LED_Succeed();  /*�ɹ�����ָʾ����˸*/
	}

}



void Keyscanf(){	
//���������صĺ���
		/*����ģʽ�л�����*/ 
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
		{
			delay_ms(100);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
			{			
				Interface+=1;
				if(Interface>2)Interface=0;
			}

		}
				/*������ģʽ����ͳģʽ*/
		if(Interface==0)
		{
			if(Interface1==0)
			{
				Interface1=1;
				printf("������ģʽ\r\n");
				LED_change();   /*�л��ɹ�ָʾ��*/
				OLED_P6x8Str(0,0,"0");	        //�����������
			}
			//ÿ��������ʾ�¶ȣ�ÿ�����Ӽ��һ���Ƿ�������
			//Check();	
		if(Read_DHT11(&DHT11_Data)==1){	
			OLED_ShowNum(55,6,DHT11_Data.humi_int,2,16);	//��ʾʪ��	
			OLED_ShowNum(75,6,DHT11_Data.humi_deci,1,16);	//��ʾʪ��		
			OLED_ShowNum(55,4,DHT11_Data.temp_int,2,16);	//��ʾ�¶�
			OLED_ShowNum(75,4,DHT11_Data.temp_deci,1,16);	//��ʾ�¶�
			
		}
		
	}
		
		
		/*����ģʽ*/
		if(Interface==1)
		{
			if(Interface1==1)
			{
					Interface1=2;
					OLED_P6x8Str(0,0,"1");	 //�����������
					LED_change();   /*�л��ɹ�ָʾ��*/
					printf("����ģʽ\r\n");
					
			}		
			Intelligence_Mode();     //��������ģʽ
		}	
		
		/*˯��ģʽ*/
		if(Interface==2)
		{
			if(Interface1==2)
			{
					Interface1=0;
					OLED_P6x8Str(0,0,"2");	 
					LED_change();   /*�л��ɹ�ָʾ��*/
					printf("˯��ģʽ\r\n");
					
			}	
			Sleep_Mode();     		//����˯��ģʽ			
		}	
		
}
void We_are_Team(){

	/*
	1���������ƴ�ͳת��
	2���������ƴ�ͳ��ʱ
	3������ָ��
	4������ʱ���Զ��رգ�ÿ1min���һ��
	5��DHT11��ʾ��ÿ1min��ȡһ��
	*/
	
	//������ģʽ:0���� 1�� ���򿪵�ʱ������������Զ���⣬�򿪵�ʱ������ģʽ��
	Keyscanf();
	
	//�������ƴ�ͳת�١���ͳ��ʱ
	Shift_PWM();
	
	//����ָ��
	Bluetooth();
	
	//�����Ӽ���Ƿ����˴��ڣ�����ÿ1Min��ʾDHT11�¶ȣ��Ѿ��ŵ�����ģʽ���ж�����
	//Check();
	
}




int main(void){	 
//	u8 i=0;
	SystemInit();		 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	//��ʱ��2�������ƶ���ʱ��
	TIM2_Int_Init(7199,9999);//1s	((1+arr )/72M)*(1+psc )=((1+7199)/72M)*(1+9999)=1��	
	TIM_Cmd(TIM2, DISABLE);  //Ĭ�Ϲر�TIM2	
	 
	//��ʱ��3�������Ʒ���ת��	
	PWM_Init(1999,0);
	TIM_Cmd(TIM3, ENABLE);  	//Ĭ�ϴ�TIM3	
	TIM_SetCompare1(TIM3,0);    //A6���ȹرյ��
	//EXTIX_Init();				/*�ⲿ�жϰ���*/
	
	//���ڳ�ʼ�����ڶ�ʱ�����棬��Ȼ��ӡ���ݲ���
	uart_init(115200);	/*���ڳ�ʼ��Ϊ115200*/

	LED_Init();		  	/*LEDģ���ʼ�� C��B�ڶ�����*/
	KEY_Init();	 		//�����˿ڳ�ʼ��  B��
	OLED_Init();	  	/*OLEDģ���ʼ��  C��*/
	Init_face();		//�����ʼ��
	
	HC_SR501Init();   	/*��������ʼ��  A��*/
	
	
	//����ǰ�ȴ�1S
	delay_ms(1000);
	//DHT11��ʼ��
	if(Read_DHT11(&DHT11_Data)==1){	
		OLED_ShowNum(55,6,DHT11_Data.humi_int,2,16);	//��ʾʪ��	
		OLED_ShowNum(75,6,DHT11_Data.humi_deci,1,16);	//��ʾʪ��		
		OLED_ShowNum(55,4,DHT11_Data.temp_int,2,16);	//��ʾ�¶�
		OLED_ShowNum(75,4,DHT11_Data.temp_deci,1,16);	//��ʾ�¶�
		show_GreenLED();
	}
	OLED_ShowChar(105,6,'O');	    
	OLED_ShowChar(110,6,'K');
	show_ThreeLED();
	while(1)
	{	

		if(HC_SR501_Statue()==1)show_GreenLED();
		else {
			show_RedLED();
		}
		
		We_are_Team();
		delay_ms(500);
	}	
}	



//��ʱ��2�жϷ������
void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		time++;  /*��ʱʱ�䵽��֮�󣬿�ʼ�رշ��ȹ���*/
		}
		if(Open_time==1)
		{
			if(time==30)        		 /*���˴��ڵ�ʱ��رշ��ȣ���ʱ���ְ룺150S����Ϊ�Զ��������������*/
			{	
			time=0;
			TIM_SetCompare1(TIM3,0);  	 //A6	
		    TIM_Cmd(TIM2,DISABLE);  	 //��ʱ�����ر�TIM2		
			LED_Close();  /*���ⱨ��*/
			} 
		}
		
		if(Open_time==2)
		{
			if(time==(User_Time*60-1))   /*��������û���ʱʱ�䣬��ô�͹ػ�*/
			{	
			time=0;
			TIM_SetCompare1(TIM3,0);  	 //A6�ر�	
			LED_Close();  /*���ⱨ��*/
		    TIM_Cmd(TIM2,DISABLE);  	 //��ʱ�����ر�TIM2		
			} 
		}
		
		if(Open_time==3)
		{
			if(time==(User_Time*60-1))      /*��ͳ��ʱ������û��������ʮ���ӣ�ֻ�ܶ�ʱ10-180min*/
			{	
			time=0;
			TIM_SetCompare1(TIM3,0);  	  	//A6�ر�	
			LED_Close();  /*���ⱨ��*/
		    TIM_Cmd(TIM2,DISABLE);  	 	//��ʱ�����ر�TIM2		
			} 
		}
}



////�ⲿ�жϷ������
//void EXTI9_5_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line5)!= RESET)  
//		{  
//		EXTI_ClearITPendingBit(EXTI_Line5);
//		delay_ms(100);//����
//		/*����ģʽ�л�����*/ 
//		Interface+=1;
//		if(Interface>1)Interface=0;
//		} 
//}

