#include "pbdata.h"

/****************************************************
函数名 SystemClock_Config
功能   配置时钟
参数   无
返回值 无

设置时钟流程： 
1.将RCC寄存器重新设置为默认值          RCC_DeInit 
2.打开外部高速时钟晶振HSE              RCC_HSEConfig(RCC_HSE_ON); 
3.等待外部高速时钟晶振工作             HSEStartUpStatus = RCC_WaitForHSEStartUp(); 
4.设置AHB时钟                          RCC_HCLKConfig;
5.设置高速APB2时钟                     RCC_PCLK2Config; 
6.设置低速速APB1时钟                   RCC_PCLK1Config 
7.设置PLL                              RCC_PLLConfig 
8.打开PLL                              RCC_PLLCmd(ENABLE); 
9.等待PLL工作 				while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)  
10.设置系统时钟                        RCC_SYSCLKConfig 
11.判断是否PLL是系统时钟               while(RCC_GetSYSCLKSource() != 0x08) 
12.打开要使用的外设时钟                RCC_APB2PeriphClockCmd()/RCC_APB1PeriphClockCmd（） 
至此我们就将STM32的系统时钟配置好了，系统时钟72MHz，APH 72MHz，APB2 72MHz，APB1 32MHz，USB 48MHz 
其他至于ADC什么的先用不管，用到时再设置，本次只是大体先熟悉下STM32的时钟配置流程，便于以后程序的编写

******************************************************/
void SystemClock_Config(void) 
{ 
	ErrorStatus HSEStartUpStatus; 
	//SystemInit();                                                    //完全可以使用此函数配置，但是为了学习先不用 
	RCC_DeInit();                                                      //复位RCC模块的寄存器,复位成缺省值 
	RCC_HSEConfig(RCC_HSE_ON);                    //开启HSE时钟,用HSE的时钟作为PLL的时钟源 
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); //获取HSE启动状态
	if(HSEStartUpStatus == SUCCESS)                      //如果HSE启动成功         
	{ 
		FLASH_PrefetchBufferCmd(ENABLE);          //开启FLASH的预取功能                   
		FLASH_SetLatency(FLASH_Latency_2);      //FLASH延迟2个周期    
		RCC_HCLKConfig(RCC_SYSCLK_Div1);        //配置HCLK,PCLK2,PCLK1,PLL 
		RCC_PCLK2Config(RCC_HCLK_Div1); 
		RCC_PCLK1Config(RCC_HCLK_Div2); 
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9); 
		RCC_PLLCmd(ENABLE);                              //启动PLL       
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);//等待PLL启动完成 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  //配置系统时钟 
		while(RCC_GetSYSCLKSource() !=0x08);//检查是否将HSE 9倍频后作为系统时钟 
	} 
} 



/****************************************************************************
* 名    称：delay_us(u32 nus)
* 功    能：微秒延时函数
* 入口参数：u32  nus
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void delay_us(u32 nus)
{
	 u32 temp;
	 SysTick->LOAD = 9*nus;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}

/****************************************************************************
* 名    称：delay_ms(u16 nms)
* 功    能：毫秒延时函数
* 入口参数：u16 nms
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void delay_ms(u16 nms)
{
     //注意 delay_ms函数输入范围是1-1863
	 //所以最大延时为1.8秒

	 u32 temp;
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}



