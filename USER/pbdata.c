#include "pbdata.h"

/****************************************************
������ SystemClock_Config
����   ����ʱ��
����   ��
����ֵ ��

����ʱ�����̣� 
1.��RCC�Ĵ�����������ΪĬ��ֵ          RCC_DeInit 
2.���ⲿ����ʱ�Ӿ���HSE              RCC_HSEConfig(RCC_HSE_ON); 
3.�ȴ��ⲿ����ʱ�Ӿ�����             HSEStartUpStatus = RCC_WaitForHSEStartUp(); 
4.����AHBʱ��                          RCC_HCLKConfig;
5.���ø���APB2ʱ��                     RCC_PCLK2Config; 
6.���õ�����APB1ʱ��                   RCC_PCLK1Config 
7.����PLL                              RCC_PLLConfig 
8.��PLL                              RCC_PLLCmd(ENABLE); 
9.�ȴ�PLL���� 				while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)  
10.����ϵͳʱ��                        RCC_SYSCLKConfig 
11.�ж��Ƿ�PLL��ϵͳʱ��               while(RCC_GetSYSCLKSource() != 0x08) 
12.��Ҫʹ�õ�����ʱ��                RCC_APB2PeriphClockCmd()/RCC_APB1PeriphClockCmd���� 
�������Ǿͽ�STM32��ϵͳʱ�����ú��ˣ�ϵͳʱ��72MHz��APH 72MHz��APB2 72MHz��APB1 32MHz��USB 48MHz 
��������ADCʲô�����ò��ܣ��õ�ʱ�����ã�����ֻ�Ǵ�������Ϥ��STM32��ʱ���������̣������Ժ����ı�д

******************************************************/
void SystemClock_Config(void) 
{ 
	ErrorStatus HSEStartUpStatus; 
	//SystemInit();                                                    //��ȫ����ʹ�ô˺������ã�����Ϊ��ѧϰ�Ȳ��� 
	RCC_DeInit();                                                      //��λRCCģ��ļĴ���,��λ��ȱʡֵ 
	RCC_HSEConfig(RCC_HSE_ON);                    //����HSEʱ��,��HSE��ʱ����ΪPLL��ʱ��Դ 
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); //��ȡHSE����״̬
	if(HSEStartUpStatus == SUCCESS)                      //���HSE�����ɹ�         
	{ 
		FLASH_PrefetchBufferCmd(ENABLE);          //����FLASH��Ԥȡ����                   
		FLASH_SetLatency(FLASH_Latency_2);      //FLASH�ӳ�2������    
		RCC_HCLKConfig(RCC_SYSCLK_Div1);        //����HCLK,PCLK2,PCLK1,PLL 
		RCC_PCLK2Config(RCC_HCLK_Div1); 
		RCC_PCLK1Config(RCC_HCLK_Div2); 
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9); 
		RCC_PLLCmd(ENABLE);                              //����PLL       
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);//�ȴ�PLL������� 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  //����ϵͳʱ�� 
		while(RCC_GetSYSCLKSource() !=0x08);//����Ƿ�HSE 9��Ƶ����Ϊϵͳʱ�� 
	} 
} 



/****************************************************************************
* ��    �ƣ�delay_us(u32 nus)
* ��    �ܣ�΢����ʱ����
* ��ڲ�����u32  nus
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_us(u32 nus)
{
	 u32 temp;
	 SysTick->LOAD = 9*nus;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}

/****************************************************************************
* ��    �ƣ�delay_ms(u16 nms)
* ��    �ܣ�������ʱ����
* ��ڲ�����u16 nms
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_ms(u16 nms)
{
     //ע�� delay_ms�������뷶Χ��1-1863
	 //���������ʱΪ1.8��

	 u32 temp;
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}



