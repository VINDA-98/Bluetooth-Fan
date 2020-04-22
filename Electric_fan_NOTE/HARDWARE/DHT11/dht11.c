//#include "dht11.h"
//#include "delay.h"

// //////////////////////////////////////////////////////////////////////////////////	 
////本程序只供学习使用，未经作者许可，不得用于其它任何用途
////ALIENTEK战舰STM32开发板
////DHT11数字温湿度传感器驱动代码	   
////正点原子@ALIENTEK
////技术论坛:www.openedv.com
////修改日期:2012/9/12
////版本：V1.0
////版权所有，盗版必究。
////Copyright(C) 广州市星翼电子科技有限公司 2009-2019
////All rights reserved									  
////////////////////////////////////////////////////////////////////////////////////
//      
////复位DHT11
//void DHT11_Rst(void)	   
//{                 
//	DHT11_IO_OUT(); 	//SET OUTPUT
//    DHT11_DQ_OUT=0; 	//拉低DQ
//    delay_ms(20);    	//拉低至少18ms
//    DHT11_DQ_OUT=1; 	//DQ=1 
//	delay_us(30);     	//主机拉高20~40us
//}
////等待DHT11的回应
////返回1:未检测到DHT11的存在
////返回0:存在
//u8 DHT11_Check(void) 	   
//{   
//	u8 retry=0;
//	DHT11_IO_IN();//SET INPUT	 
//    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us
//	{
//		retry++;
//		delay_us(1);
//	};	 
//	if(retry>=100)return 1;
//	else retry=0;
//    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
//	{
//		retry++;
//		delay_us(1);
//	};
//	if(retry>=100)return 1;	    
//	return 0;
//}
////从DHT11读取一个位
////返回值：1/0
//u8 DHT11_Read_Bit(void) 			 
//{
// 	u8 retry=0;
//	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
//	{
//		retry++;
//		delay_us(1);
//	}
//	retry=0;
//	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
//	{
//		retry++;
//		delay_us(1);
//	}
//	delay_us(40);//等待40us
//	if(DHT11_DQ_IN)return 1;
//	else return 0;		   
//}
////从DHT11读取一个字节
////返回值：读到的数据
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
////从DHT11读取一次数据
////temp:温度值(范围:0~50°)
////humi:湿度值(范围:20%~90%)
////返回值：0,正常;1,读取失败
//u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
//{        
// 	u8 buf[5];
//	u8 i;
//	DHT11_Rst();
//	if(DHT11_Check()==0)
//	{
//		for(i=0;i<5;i++)//读取40位数据
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
////初始化DHT11的IO口 DQ 同时检测DHT11的存在
////返回1:不存在
////返回0:存在    	 
//u8 DHT11_Init(void)
//{	 
// 	GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PG端口时钟
//	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //PG11端口配置
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);				 //初始化IO口
// 	GPIO_SetBits(GPIOB,GPIO_Pin_11);						 //PG11 输出高
//			    
//	DHT11_Rst();  //复位DHT11
//	return DHT11_Check();//等待DHT11的回应
//} 



#include "dht11.h"



/*
 * 函数名：DHT11_GPIO_Config
 * 描述  ：配置DHT11用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */

 
 
void DHT11_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启DHT11_PORT的外设时钟*/
	RCC_APB2PeriphClockCmd(DHT11_CLK, ENABLE); 

	/*选择要控制的DHT11_PORT引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化DHT11_PORT*/
  	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);		  

	/* 拉高GPIOB10	*/
	GPIO_SetBits(DHT11_PORT, GPIO_Pin_10);	 
}

/*
 * 函数名：DHT11_Mode_IPU
 * 描述  ：使DHT11-DATA引脚变为上拉输入模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  	/*选择要控制的DHT11_PORT引脚*/	
	  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;

	   /*设置引脚模式为浮空输入模式*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 

	  /*调用库函数，初始化DHT11_PORT*/
	  GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

/*
 * 函数名：DHT11_Mode_Out_PP
 * 描述  ：使DHT11-DATA引脚变为推挽输出模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*选择要控制的DHT11_PORT引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化DHT11_PORT*/
  	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 	 
}

/* 
 * 从DHT11读取一个字节，MSB先行
 */
static uint8_t Read_Byte(void)
{
	uint8_t i, temp=0;

	for(i=0;i<8;i++)    
	{	 
		/*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/  
		while(DHT11_DATA_IN()==Bit_RESET);

		/*DHT11 以26~28us的高电平表示“0”，以70us高电平表示“1”，
		 *通过检测 x us后的电平即可区别这两个状 ，x 即下面的延时 
		 */
		delay_us(40); //延时x us 这个延时需要大于数据0持续的时间即可	   	  

		if(DHT11_DATA_IN()==Bit_SET)/* x us后仍为高电平表示数据“1” */
		{
			/* 等待数据1的高电平结束 */
			while(DHT11_DATA_IN()==Bit_SET);

			temp|=(uint8_t)(0x01<<(7-i));  //把第7-i位置1，MSB先行 
		}
		else	 // x us后为低电平表示数据“0”
		{			   
			temp&=(uint8_t)~(0x01<<(7-i)); //把第7-i位置0，MSB先行
		}
	}
	return temp;
}
/*
 * 一次完整的数据传输为40bit，高位先出
 * 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
 */
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  
	/*输出模式*/
	DHT11_Mode_Out_PP();
	/*主机拉低*/
	DHT11_DATA_OUT(LOW);
	/*延时18ms*/
	//Delay_ms(18);
	delay_us(18000);

	/*总线拉高 主机延时30us*/
	DHT11_DATA_OUT(HIGH); 

	delay_us(30);   //延时30us

	/*主机设为输入 判断从机响应信号*/ 
	DHT11_Mode_IPU();

	/*判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行*/   
	if(DHT11_DATA_IN()==Bit_RESET)     
	{
		/*轮询直到从机发出 的80us 低电平 响应信号结束*/  
		while(DHT11_DATA_IN()==Bit_RESET);

		/*轮询直到从机发出的 80us 高电平 标置信号结束*/
		while(DHT11_DATA_IN()==Bit_SET);

		/*开始接收数据*/   
		DHT11_Data->humi_int= Read_Byte();

		DHT11_Data->humi_deci= Read_Byte();

		DHT11_Data->temp_int= Read_Byte();

		DHT11_Data->temp_deci= Read_Byte();

		DHT11_Data->check_sum= Read_Byte();


		/*读取结束，引脚改为输出模式*/
		DHT11_Mode_Out_PP();
		/*主机拉高*/
		DHT11_DATA_OUT(HIGH);

		/*检查读取的数据是否正确*/
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








