/*
´ó´´ÏîÄ¿£ºÖÇÄÜÀ¶ÑÀ·çÉÈ
´´½¨Ê±¼ä2019.9.28£¬12.24
´´½¨ÈË£ºÎ¤´ï
ÍÅ¶ÓÔ­´´

ÖÇÄÜÀ¶ÑÀ·çÉÈÊµÏÖ¹¦ÄÜÈçÏÂ£º
1¡¢À¶ÑÀ¿ØÖÆÊı¾İ´«Êä      PA9 PA10
2¡¢°´¼ü¿ØÖÆÖÇÄÜÄ£Ê½ÇĞ»»  PB5
3¡¢°´¼ü¿ØÖÆ×ªËÙ¡¢¶¨Ê±    PB6¡¢PB7
4¡¢×Ô¶¯¼ì²âÎŞÈË»·¾³ 	    PA4
5¡¢DHT11»·¾³ÎÂÊª¶È¼ì²é   PB11
6¡¢OLEDÏÔÊ¾        	    PCout(14)//SCL   ´®ĞĞÊ±ÖÓ PCout(15)//SDA	
7¡¢Éù¹â±¨¾¯×°ÖÃ£º		BEEP£º  P12        LED2£ºPB13(ºì)¡¢14(ÂÌÉ«)¡¢15(À¶É«)
*/
#include "sys.h"
#include "delay.h"
#include "usart.h"	
#include "exti.h"
#include "led.h"    	/*µÆ*/
#include "key.h"	/*°´¼ü*/ 
#include "oled.h"    /*ÆÁÄ»*/
#include "dht11.h"	/*ÎÂÊª¶È*/
#include "pwm.h"	/*·çÉÈPWM*/
#include "stdlib.h"

u32 time=0;					  	  /*ÓÃÀ´¶¨Ê±µÄÊ±¼ä£¬µ¥Î»£ºÃë*/
DHT11_Data_TypeDef DHT11_Data;    /*ÎÂÊª¶ÈÊı¾İ½á¹¹Ìå*/
u8  temperature,humidity;  	  	  /*DHT11ÎÂ¶ÈÓëÊª¶È*/
u8  Interface=0,Interface1=0;     /*½çÃæÇĞ»»±äÁ¿*/
u8  add=0,add1=0;    			/*µç»úÇĞ»»µ²Î»±äÁ¿*/
u16 receive=0;  		 		/*À¶ÑÀ½ÓÊÕ»ØÀ´µÄÊı¾İ*/
u16 Speed=0;     		 		/*µç»ú×ªËÙ±êÖ¾Á¿*/  
u16 buff=0;  				    /*°Ù·Ö±È»ù´¡ÊıÁ¿*/
u32 User_Time=0; 	 			/*ÓÃ»§¶¨Ê±±äÁ¿*/
u8  Open_time=0; 				 /*1µÄÊ±ºòÊÇÃ»ÓĞÈËÆô¶¯¶¨Ê±Æ÷¹Ø±Õ·çÉÈ£¬2µÄÊ±ºòÊÇÀ¶ÑÀ¿ØÖÆ¶¨Ê±Ê±¼ä£¬3ÊÇ´«Í³¶¨Ê±*/
u8  temp_up=0,temp_dowm=0;  	  /*ÓÃ»§´«»ØÀ´¹Ø»úÎÂ¶È*/
u8  Receive_Buff[USART_REC_LEN];  /*½ÓÊÕ»º´æÊı×é*/
u8  timeBuff[3]; 	/*Ê±¼ä»º´æÊı×é*/
u8  send_flag=0;  	/*DHT11·¢ËÍÊı¾İ±êÖ¾Á¿*/
u8  zhuansu=0;	 	//ÎÂ¿Ø×ªËÙÅĞ¶Ï
u16 Sleep_pwmval=0; /*Ë¯Ãß¿ØÖÆµÄPWM±äÁ¿*/
u8 dir=1,dir1=0;	         /*Ë¯Ãß¿ØÖÆÊÇ·ñ¹¤×÷±äÁ¿*/
u8 temperature_buff[2],Intelligence_time=0;//ÖÇÄÜÄ£Ê½ÏÂµÄ»º´æÊı×é
u8 time_DHT11=0,time1_DHT11=0,read_IO;//DHT11Æô¶¯×Ó³ÌĞò  read_IO¶ÁÈ¡ºìÍâ¼ì²âIO±äÁ¿

//½çÃæ³õÊ¼»¯
void Init_face(){

	/*³õÊ¼»¯½çÃæ*/
	OLED_P6x8Str(9,1,"Mode : ");
	OLED_P6x8Str(9,3,"Time : ");
	OLED_P6x8Str(9,5,"Temp : ");
	OLED_P6x8Str(9,7,"water: ");
	OLED_P6x8Str(9+65,0,"Speed:");
	OLED_ShowChar(9+45+18,2,'H');	//ÏÔÊ¾Ğ¡Ê±
	OLED_ShowChar(9+75+18,2,'M');	//ÏÔÊ¾·ÖÖÓ
	OLED_ShowChar(69,4,'.');	    //ÏÔÊ¾Ğ¡Êıµã	
	OLED_ShowChar(69,6,'.');	    //ÏÔÊ¾Ğ¡Êıµã	
	OLED_ShowChar(90,4,'C');	    //ÏÔÊ¾C
	OLED_ShowChar(90,6,'%');	    //ÏÔÊ¾%	
}

/*Ä£Ê½ÇĞ»»Ö¸Ê¾µÆ*/
void LED_change(){

		LED_Green=!LED_Green;  /*Ä£Ê½ÇĞ»»Ö¸Ê¾µÆ*/
		delay_ms(500);
		LED_Green=!LED_Green;
		delay_ms(500);
}

/*³É¹¦½ÓÊÕÖ¸Ê¾µÆÉÁË¸*/
void LED_Succeed(){

		LED_Blue=!LED_Blue;  /*Ä£Ê½ÇĞ»»Ö¸Ê¾µÆ*/
		delay_ms(100);
		LED_Blue=!LED_Blue;
		delay_ms(100);
		LED_Blue=!LED_Blue;  /*Ä£Ê½ÇĞ»»Ö¸Ê¾µÆ*/
		delay_ms(100);
		LED_Blue=!LED_Blue;
		delay_ms(100);
		LED_Blue=0;
	
}

/*¶¨Ê±¹Ø±ÕÌáĞÑ*/
void LED_Close(){
	 BEEP=!BEEP;
	 LED_RED=!LED_RED;            //Ã»ÈË´æÔÚµÄÊ±ºòºìµÆ±¨¾¯
	 delay_ms(200);
	 BEEP=!BEEP;
	 LED_RED=!LED_RED;            //Ã»ÈË´æÔÚµÄÊ±ºòºìµÆ±¨¾
	 delay_ms(200);
}

//ÖÇÄÜÄ£Ê½
void Intelligence_Mode(){

	/*1¡¢Ëæ×ÅÎÂ¶È¸Ä±äPWMÊä³ö 15-40¶È PWM·¶Î§£º
	   2¡¢¼äĞªĞÔ´µ·ç*/
	Intelligence_time++;
	delay_ms(30);
	if(Intelligence_time%100==0)  //Ã¿3S¶ÁÈ¡Ò»´Î
	{
				Intelligence_time=0;
				//DHT11_Read_Data(&temperature,&humidity);	//¶ÁÈ¡ÎÂÊª¶ÈÖµ
				temperature_buff[0]	= temperature;			/*¼ÓÔØ»º´æ*/
				
				OLED_ShowNum(65,4,temperature,2,16);	    //ÏÔÊ¾ÎÂ¶È	
				OLED_ShowNum(65,6,humidity,2,16);				//ÏÔÊ¾Êª¶È	
				
				//ËÙ¶ÈËæ×ÅÎÂ¶È±ä»¯¸Ä±äPWM
		
				if(temperature_buff[0]==15){
						Speed =0;
						OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
						TIM_SetCompare1(TIM3,0);
				}
				if(temperature_buff[0]<15){
						Speed = 1100/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
						TIM_SetCompare1(TIM3,1100);
				}
				
				if(temperature_buff[0]>15&&temperature_buff[0]>20){
					   Speed = 1200/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
						TIM_SetCompare1(TIM3,1200); 
				}
				
				if(temperature_buff[0]>20&&temperature_buff[0]>25){
					    Speed = 1250/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È						
						TIM_SetCompare1(TIM3,1250);  
				}
				
				if(temperature_buff[0]>25&&temperature_buff[0]>30){
						Speed = 1300/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
						TIM_SetCompare1(TIM3,1300); 
				}
				
				if(temperature_buff[0]>30&&temperature_buff[0]>35){
						Speed = 1380/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
						TIM_SetCompare1(TIM3,1380);   
				}

				if(temperature_buff[0]>35){
						Speed = 1420/32;
						OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
						TIM_SetCompare1(TIM3,1420);  
				}
	}
}

//°´¼ü¿ØÖÆ×ªËÙ¡¢¶¨Ê±  PB6¡¢PB7
void Shift_PWM(){

	/*PB6°´ÏÂ£º¸ü»»µ²Î»*/ 
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)
	{
		delay_ms(120);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)
		{			
			add+=1;
			if(add>3)add=0;
		}
	}
	
	/*PB7°´ÏÂ£º´«Í³¶¨Ê±°´Å¥*/ 
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0){
		delay_ms(120);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)
		{			
			/*´«Í³¶¨Ê±Ã¿´Î°´ÏÂ¶àÊ®·ÖÖÓ£¬Ö»ÄÜ1-3Ğ¡Ê±*/
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
			
			OLED_ShowNum(9+45,2,timeBuff[1],2,16); //Ğ¡Ê±
			OLED_ShowNum(9+75,2,timeBuff[2],2,16); //·ÖÖÓ
			printf("¶¨Ê±Ê±¼ä£º %dH,%dmin\r\n",timeBuff[1],timeBuff[2]);					
		}
	}
	
	//0µÄÊ±ºò²»¶¯£¬1µÄÊ±ºòÒ»µµ£¬2µÄÊ±ºò¶şµµ£¬3µÄÊ±ºòÈıµµ
	if(add==0)
	{
		if(add1==0){
			add1=1;
			Speed = 0;
			OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
			TIM_SetCompare1(TIM3,Speed);  	  //²»¶¯
			printf("¹Ø»ú\r\n");					
		}
	}
	//Ò»µµ
	if(add==1)
	{
		if(add1==1){
			add1=2;
			Speed = 30;
			OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
			TIM_SetCompare1(TIM3,Speed*38);   //Ò»µµ
			printf("Ò»µµ\r\n");						
		}
	}
	//¶şµµ
	if(add==2)
	{
		if(add1==2){
			add1=3;
			Speed = 60;
			OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
			TIM_SetCompare1(TIM3,Speed*21);   //¶şµµ
			printf("¶şµµ\r\n");				
		}
	}
	//Èıµµ
	if(add==3)
	{
		if(add1==3){
			add1=0;
			Speed = 90;
			OLED_ShowNum(9+100,0,Speed,2,16); //ËÙ¶È
			TIM_SetCompare1(TIM3,Speed*15.5);  //Èıµµ
			printf("Èıµµ\r\n");	
		}
	}
}

void Read_Peopel(){

	//¼ì²âÊÇ·ñÓĞÈË¶ÁÈ¡ºìÍâ½ÅµÄÖµ
		read_IO=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
		//LED1=0;  	 	 /*LED=0ÊÇÁÁµÄÒâË¼*/ 
		if(read_IO==0){
			LED_RED=0;   	 /*µÍµçÆ½µÄÊ±ºòÊÇÃ»ÓĞÈËµÄ£¬¸ßµçÆ½ÊÇÓĞÈËµÄ£¬Ã»ÈËµÄÊ±ºòÄ¬ÈÏ¹Ø±Õ*/
			Open_time=1;/*´ò¿ªÅĞ¶Ï¶¨Ê±Æ÷¹¤×÷±äÁ¿Îª1£¬Open_time=1±íÊ¾´ËÊ±ÎŞÈË*/
			TIM_Cmd(TIM2, ENABLE);  //Ã»ÈËÊ±ºò´ò¿ª¶¨Ê±Æ÷		
			printf("ÏÖÔÚÎŞÈË\r\n");								
		}
		else{
			//ÖÇÄÜÄ£Ê½ÏÂÈç¹ûÒÑ¾­¿ªÆô¶¨Ê±Ä£Ê½£¬ÓĞÈËµÄÇé¿öÏÂÒ²Òª´ò¿ª¶¨Ê±Æ÷
			if(Open_time==2)TIM_Cmd(TIM2, ENABLE);   	    //Èç¹ûÀ¶ÑÀÒÑ¾­¶¨Ê±Æ÷
			
			else if(Open_time==3)TIM_Cmd(TIM2, ENABLE);   //Èç¹û´«Í³ÒÑ¾­¶¨Ê±
			
			else TIM_Cmd(TIM2, DISABLE); 		     	  //ÒªÊÇÉÏÃæÁ½ÖÖÇé¿ö¶¼²»ÊôÓÚµÄÊ±ºò¹Ø±Õ¶¨Ê±Æ÷
			LED_RED=1;  				 	 			  /*ÓĞÈËµÄÊ±ºòLED=0¿ªÊ¼ÁÁÆğÀ´*/
			printf("ÏÖÔÚÓĞÈË\r\n");
		}	
}

//DHT11Êı¾İÉÏ´«
void DHT11_Start(){

	if(send_flag==1)
		{
			Read_DHT11(&DHT11_Data);//¶ÁÈ¡ÎÂÊª¶ÈÖµ	
			//DHT11_Read_Data(&temperature,&humidity);					    
			OLED_ShowNum(65,4,DHT11_Data.temp_int,2,16);		//ÏÔÊ¾ÎÂ¶È	
			OLED_ShowNum(65,6,DHT11_Data.humi_int,2,16);		//ÏÔÊ¾Êª¶È
			USART_SendData(USART1,0x52);  					//¼ì²âµ½0x52²ÅËã¿ªÊ¼
			delay_ms(100);  
			USART_SendData(USART1,DHT11_Data.temp_int); //·¢ËÍÎÂ¶ÈµÄÊ®Áù½øÖÆ
			delay_ms(1000);
			USART_SendData(USART1,DHT11_Data.humi_int);	//·¢ËÍÊª¶ÈµÄÊ®Áù½øÖÆ
			delay_ms(100);
			USART_SendData(USART1,0x53);//¼ì²âµ½0x53²ÅËã½áÊø
			delay_ms(100);
		if(zhuansu==1)
		{
			if(temperature>temp_up)  /*³¬¹ıÎÂ¶ÈÉÏÏŞ*/
			{
				TIM_SetCompare1(TIM3,1500);
			}
			
			if(temperature<temp_dowm) /*³¬¹ıÎÂ¶ÈÏÂÏŞ*/
			{
				TIM_SetCompare1(TIM3,1100);
			}
		}
	}
		//	printf("ÏÖÔÚÎÂ¶ÈÎª£º%d¡ã\r\n",temperature);	
		//	printf("ÏÖÔÚÊª¶ÈÎª£º%d%%\r\n",humidity);
}

//×Ô¶¯¼ì²âº¯Êı DHT11ÏÔÊ¾1min
void Check(){
	delay_ms(10);
	time_DHT11++;   //Ã¿´ÎÔö¼Ó10ms£¬Ò»¹²ÒªÔö¼ÓÒ»°Ù´Î 10ms*10 = 100ms
	if(time_DHT11==15)
	{
		time_DHT11=0; /*µÈÓÚ0ÔÙÀ´*/
		time1_DHT11++;
		//time_DHT11=10£¬time1_DHT11=120 Õâ¸ö¶¨Ê±ÊÇ45S
		if(time1_DHT11==200)  // time1_DHT11=200£¬time_DHT11==15µÃµ½116S  ²î²»¶àÁ½·ÖÖÓ
		{
			time1_DHT11=0;
			send_flag=1;       /*DHT11È·¶¨¹¤×÷±äÁ¿*/
			Read_Peopel();  //¶ÁÈ¡ºìÍâÊÇ·ñ¼ì²âµ½ÈË
			DHT11_Start();	//DHT11ÎÂ¶ÈÏÔÊ¾
			send_flag=0;         /*DHT11¹Ø±Õ¹¤×÷±äÁ¿*/
		}	
	}
}

//Ë¯ÃßÄ£Ê½
void Sleep_Mode(){
		//¼äĞªĞÔ´µ·ç
		Intelligence_time++;
		if(Intelligence_time%100==0)  //Ã¿3S¶ÁÈ¡Ò»´Î
		{
					//¼äĞªĞÔ´µ·ç
					//È·¶¨ÎÂ¶È²îÖµ
					Read_DHT11(&DHT11_Data);//¶ÁÈ¡ÎÂÊª¶ÈÖµ					    
					OLED_ShowNum(65,4,DHT11_Data.temp_int,2,16);		//ÏÔÊ¾ÎÂ¶È	
					OLED_ShowNum(65,6,DHT11_Data.humi_int,2,16);		//ÏÔÊ¾Êª¶È
					temperature_buff[0]	= DHT11_Data.temp_int;/*¼ÓÔØ»º´æ*/
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

	
//À¶ÑÀ¿ØÖÆ×Ó³ÌĞò
void Bluetooth(){
//´«Í³Ä£Ê½¡¢ÖÇÄÜÄ£Ê½ºÍË¯ÃßÄ£Ê½ÇĞ»»
	//±¸×¢£ºÒ»¶¨Òª¼ÇµÃÊÇ0D 0AµÄÊı¾İÖ¡Î²£¬²»È»Ê¶±ğ³öÀ´µÄÊı¾İ²»¹»ÍêÕû
	u8 len,t;
	if(USART_RX_STA&0x8000)
	{				
			/*¶ş½øÖÆ	     Ê®½øÖÆ	Ê®Áù½øÖÆ 	Í¼ĞÎ
			  0011 0000	   48	    30	     0*/
			len=USART_RX_STA&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			//printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				Receive_Buff[t]=USART_RX_BUF[t];
				//USART_SendData(USART1, USART_RX_BUF[t]);//Ïò´®¿Ú1·¢ËÍÊı¾İ
				//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
			}
			
			OLED_ShowNum(9+45,0,Receive_Buff[0],2,16);	  /*ÏÔÊ¾±¾´Î½ÓÊÜÄ£Ê½*/
			//À¶ÑÀ·ÖÖ§¿ØÖÆ
			switch(Receive_Buff[0])
			{	
				//0x01:´ò¿ª·çÉÈµç»ú;
				case 1:TIM_SetCompare1(TIM3,1200);break;
				
				//0x02:¹Ø±Õ·çÉÈµç»ú
				case 2:TIM_SetCompare1(TIM3,0); TIM_Cmd(TIM2, DISABLE);send_flag=0;break;
				
				//0x03:²é¿´DHT11ÎÂÊª¶È
				case 3:DHT11_Start();send_flag=1;break; 
				
				//0x10:·µ»Ø°´Å¥²»²é¿´
				case 10:send_flag=0;break; 
				
				//0x04:·çÉÈ¿ØÖÆ´«Í³µç»ú×ªËÙ1-3µµ
				case 4:add+=1;if(add>3)add=0;break; 
				
				/*0x05: ·çÉÈ¿ØÖÆ°Ù·Ö±Èµç»ú×ªËÙ 0-99%
				  °Ù·Ö±È¿ØÖÆµç»ú×ªËÙ Receive_Buff[1]µÄ²Î¿¼·¶Î§Îª£º0-99
				  ²ÎÊıÒ»£º0x05£¬²ÎÊı¶ş£ºÊÖ»ú¶Ë´«À´µÄ°Ù·ÖÊı*/
				case 5:				
				if(Receive_Buff[1]==0){
					buff=0;/*Êä³ö0*/
					Speed=0;
				}
				else {
				Speed=Receive_Buff[1];
				OLED_ShowNum(9+100,0,Speed,2,16); 	//ËÙ¶È//ÏÔÊ¾ËÙ¶È°Ù·Ö±È 
				buff = (Receive_Buff[1]*1.5)+1200;  /*¿ØÖÆ°Ù·Ö±È*/
				}
				TIM_SetCompare1(TIM3,buff);break;
				
				/*
				²ÎÊı1£º0x06,²ÎÊı2£ºÎÂ¶ÈÉÏÏŞ£¬²ÎÊı3£ºÎÂ¶ÈÏÂÏŞ
				ÎÂ¶ÈÉÏÏŞ¾ÍÒ»Ö±×î¸ß×ªËÙ£¬ÏÂÏŞ¾ÍÊÇ¹Ø±Õ·çÉÈ**/
				case 6:Open_time=2;
					   temp_up   = Receive_Buff[1];
					   temp_dowm = Receive_Buff[2];				
					   break;
				
				//0x07:¾«×¼¶¨Ê±:1-12H
				//Ãëµ¥Î»¶¨Ê±£º²ÎÊıÒ»£º07£¬²ÎÊı¶ş£ºĞèÒª¶¨Ê±µÄĞ¡Ê±Êı£¬²ÎÊıÈı£ºĞèÒª¶¨Ê±µÄ·ÖÖÓÊı
				case 7:Open_time=2;/*´ò¿ªÅĞ¶Ï¶¨Ê±Æ÷¹¤×÷±äÁ¿Îª2*/	
					   User_Time=(Receive_Buff[1]*60+Receive_Buff[2]); /*¼ÆËã¶¨Ê±×Ü·ÖÖÓÊı*/
					   OLED_ShowNum(9+45,2,Receive_Buff[1],2,16); //Ğ¡Ê±
					   OLED_ShowNum(9+75,2,Receive_Buff[2],2,16); //·ÖÖÓ
					   TIM_Cmd(TIM2, ENABLE);break;

				/*0x08:ÖÇÄÜÄ£Ê½:¸ù¾İÎÂ¶È×Ô¶¯µ÷½Ú·çËÙ¡¢ÎŞÈËÊ±ºò×Ô¶¯¹Ø±Õ*/
				case 8:				
				send_flag=1;//ÎÂ¶È¿ª
				zhuansu=1;  //×ªËÙ¿ª
				break; 
				
				/*Ë¯ÃßÄ£Ê½*/
				case 9:
				/*1¡¢Ëæ×ÅÎÂ¶È¸Ä±äPWMÊä³ö
				  2¡¢¼äĞªĞÔ´µ·ç*/
				Sleep_Mode();
				break;
			}
			//printf("\r\nÄú·¢ËÍµÄ³¤¶ÈÎª:%d\r\n\r\n",len);
			//printf("\r\n");//²åÈë»»ĞĞ
			USART_RX_STA=0;
			LED_Succeed();  /*³É¹¦½ÓÊÕÖ¸Ê¾µÆÉÁË¸*/
	}

}



void Keyscanf(){	
//Ö÷º¯Êı¼ÓÔØµÄº¯Êı
		/*ÖÇÄÜÄ£Ê½ÇĞ»»°´¼ü*/ 
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
		{
			delay_ms(100);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
			{			
				Interface+=1;
				if(Interface>2)Interface=0;
			}

		}
				/*·ÇÖÇÄÜÄ£Ê½£¬´«Í³Ä£Ê½*/
		if(Interface==0)
		{
			if(Interface1==0)
			{
				Interface1=1;
				printf("·ÇÖÇÄÜÄ£Ê½\r\n");
				LED_change();   /*ÇĞ»»³É¹¦Ö¸Ê¾µÆ*/
				OLED_P6x8Str(0,0,"0");	        //ÖÇÄÜÓë·ÇÖÇÄÜ
			}
			//Ã¿Á½·ÖÖÓÏÔÊ¾ÎÂ¶È£¬Ã¿Á½·ÖÖÓ¼ì²âÒ»ÏÂÊÇ·ñÓĞÈËÔÚ
			//Check();	
		if(Read_DHT11(&DHT11_Data)==1){	
			OLED_ShowNum(55,6,DHT11_Data.humi_int,2,16);	//ÏÔÊ¾Êª¶È	
			OLED_ShowNum(75,6,DHT11_Data.humi_deci,1,16);	//ÏÔÊ¾Êª¶È		
			OLED_ShowNum(55,4,DHT11_Data.temp_int,2,16);	//ÏÔÊ¾ÎÂ¶È
			OLED_ShowNum(75,4,DHT11_Data.temp_deci,1,16);	//ÏÔÊ¾ÎÂ¶È
			
		}
		
	}
		
		
		/*ÖÇÄÜÄ£Ê½*/
		if(Interface==1)
		{
			if(Interface1==1)
			{
					Interface1=2;
					OLED_P6x8Str(0,0,"1");	 //ÖÇÄÜÓë·ÇÖÇÄÜ
					LED_change();   /*ÇĞ»»³É¹¦Ö¸Ê¾µÆ*/
					printf("ÖÇÄÜÄ£Ê½\r\n");
					
			}		
			Intelligence_Mode();     //½øÈëÖÇÄÜÄ£Ê½
		}	
		
		/*Ë¯ÃßÄ£Ê½*/
		if(Interface==2)
		{
			if(Interface1==2)
			{
					Interface1=0;
					OLED_P6x8Str(0,0,"2");	 
					LED_change();   /*ÇĞ»»³É¹¦Ö¸Ê¾µÆ*/
					printf("Ë¯ÃßÄ£Ê½\r\n");
					
			}	
			Sleep_Mode();     		//½øÈëË¯ÃßÄ£Ê½			
		}	
		
}
void We_are_Team(){

	/*
	1¡¢°´¼ü¿ØÖÆ´«Í³×ªËÙ
	2¡¢°´¼ü¿ØÖÆ´«Í³¶¨Ê±
	3¡¢À¶ÑÀÖ¸Áî
	4¡¢ÎŞÈËÊ±ºò×Ô¶¯¹Ø±Õ£¬Ã¿1min¼ì²âÒ»´Î
	5¡¢DHT11ÏÔÊ¾£¬Ã¿1min¶ÁÈ¡Ò»´Î
	*/
	
	//´ò¿ªÖÇÄÜÄ£Ê½:0²»´ò¿ª 1´ò¿ª ²»´ò¿ªµÄÊ±ºò¼ÓÔØÁ½·ÖÖÓ×Ô¶¯¼ì²â£¬´ò¿ªµÄÊ±ºò°´ÖÇÄÜÄ£Ê½À´
	Keyscanf();
	
	//°´¼ü¿ØÖÆ´«Í³×ªËÙ¡¢´«Í³¶¨Ê±
	Shift_PWM();
	
	//À¶ÑÀÖ¸Áî
	Bluetooth();
	
	//Á½·ÖÖÓ¼ì²âÊÇ·ñÓĞÈË´æÔÚ£¬²¢ÇÒÃ¿1MinÏÔÊ¾DHT11ÎÂ¶È£¬ÒÑ¾­·Åµ½ÖÇÄÜÄ£Ê½µÄÅĞ¶ÏÏÂÁË
	//Check();
	
}




int main(void){	 
//	u8 i=0;
	SystemInit();		 
	delay_init();	    	 //ÑÓÊ±º¯Êı³õÊ¼»¯	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	
	//¶¨Ê±Æ÷2ÓÃÀ´¿ØÖÆ¶¨ÖÆÊ±¼ä
	TIM2_Int_Init(7199,9999);//1s	((1+arr )/72M)*(1+psc )=((1+7199)/72M)*(1+9999)=1Ãë	
	TIM_Cmd(TIM2, DISABLE);  //Ä¬ÈÏ¹Ø±ÕTIM2	
	 
	//¶¨Ê±Æ÷3ÓÃÀ´¿ØÖÆ·çÉÈ×ªËÙ	
	PWM_Init(1999,0);
	TIM_Cmd(TIM3, ENABLE);  	//Ä¬ÈÏ´ò¿ªTIM3	
	TIM_SetCompare1(TIM3,0);    //A6£¬ÏÈ¹Ø±Õµç»ú
	//EXTIX_Init();				/*Íâ²¿ÖĞ¶Ï°´¼ü*/
	
	//´®¿Ú³õÊ¼»¯·ÅÔÚ¶¨Ê±Æ÷ºóÃæ£¬²»È»´òÓ¡Êı¾İ²»µÃ
	uart_init(115200);	/*´®¿Ú³õÊ¼»¯Îª115200*/

	LED_Init();		  	/*LEDÄ£¿é³õÊ¼»¯ C¡¢B¿Ú¶¼¿ªÁË*/
	KEY_Init();	 		//°´¼ü¶Ë¿Ú³õÊ¼»¯  B¿Ú
	OLED_Init();	  	/*OLEDÄ£¿é³õÊ¼»¯  C¿Ú*/
	Init_face();		//½çÃæ³õÊ¼»¯
	
	HC_SR501Init();   	/*ÈËÌåºìÍâ³õÊ¼»¯  A¿Ú*/
	
	
	//²âÊÔÇ°µÈ´ı1S
	delay_ms(1000);
	//DHT11³õÊ¼»¯
	if(Read_DHT11(&DHT11_Data)==1){	
		OLED_ShowNum(55,6,DHT11_Data.humi_int,2,16);	//ÏÔÊ¾Êª¶È	
		OLED_ShowNum(75,6,DHT11_Data.humi_deci,1,16);	//ÏÔÊ¾Êª¶È		
		OLED_ShowNum(55,4,DHT11_Data.temp_int,2,16);	//ÏÔÊ¾ÎÂ¶È
		OLED_ShowNum(75,4,DHT11_Data.temp_deci,1,16);	//ÏÔÊ¾ÎÂ¶È
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



//¶¨Ê±Æ÷2ÖĞ¶Ï·şÎñ³ÌĞò
void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //¼ì²éÖ¸¶¨µÄTIMÖĞ¶Ï·¢ÉúÓë·ñ:TIM ÖĞ¶ÏÔ´ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //Çå³ıTIMxµÄÖĞ¶Ï´ı´¦ÀíÎ»:TIM ÖĞ¶ÏÔ´ 
		time++;  /*¼ÆÊ±Ê±¼äµ½ÁËÖ®ºó£¬¿ªÊ¼¹Ø±Õ·çÉÈ¹¤×÷*/
		}
		if(Open_time==1)
		{
			if(time==30)        		 /*ÎŞÈË´æÔÚµÄÊ±ºò¹Ø±Õ·çÉÈ£¬¶¨Ê±Á½·Ö°ë£º150S£¬ÒòÎª×Ô¶¯¼ì²âÓÃÁËÁ½·ÖÖÓ*/
			{	
			time=0;
			TIM_SetCompare1(TIM3,0);  	 //A6	
		    TIM_Cmd(TIM2,DISABLE);  	 //¼ÆÊ±½áÊø¹Ø±ÕTIM2		
			LED_Close();  /*Éù¹â±¨¾¯*/
			} 
		}
		
		if(Open_time==2)
		{
			if(time==(User_Time*60-1))   /*Èç¹ûµ½ÁËÓÃ»§¶¨Ê±Ê±¼ä£¬ÄÇÃ´¾Í¹Ø»ú*/
			{	
			time=0;
			TIM_SetCompare1(TIM3,0);  	 //A6¹Ø±Õ	
			LED_Close();  /*Éù¹â±¨¾¯*/
		    TIM_Cmd(TIM2,DISABLE);  	 //¼ÆÊ±½áÊø¹Ø±ÕTIM2		
			} 
		}
		
		if(Open_time==3)
		{
			if(time==(User_Time*60-1))      /*´«Í³¶¨Ê±£¬°´¼üÃ»°´ÏÂÔö¼ÓÊ®·ÖÖÓ£¬Ö»ÄÜ¶¨Ê±10-180min*/
			{	
			time=0;
			TIM_SetCompare1(TIM3,0);  	  	//A6¹Ø±Õ	
			LED_Close();  /*Éù¹â±¨¾¯*/
		    TIM_Cmd(TIM2,DISABLE);  	 	//¼ÆÊ±½áÊø¹Ø±ÕTIM2		
			} 
		}
}



////Íâ²¿ÖĞ¶Ï·şÎñ³ÌĞò
//void EXTI9_5_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line5)!= RESET)  
//		{  
//		EXTI_ClearITPendingBit(EXTI_Line5);
//		delay_ms(100);//Ïû¶¶
//		/*ÖÇÄÜÄ£Ê½ÇĞ»»°´¼ü*/ 
//		Interface+=1;
//		if(Interface>1)Interface=0;
//		} 
//}

