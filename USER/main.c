#include "pbdata.h"


u8 dt=0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void delay(u32 nCount);

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
	RCC_Configuration();	//系统时钟初始化
	GPIO_Configuration();//端口初始化
	
	/* 初始化SX1278 */  
//	Radio = RadioDriverInit( );
//	Radio->Init( );
//	Radio->StartRx( );
   
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		delay_ms(1000);
		
		
	}
}

void delay(u32 nCount)
{
	for(;nCount!=0;nCount--);
}

void RCC_Configuration(void)
{
    //SystemInit();
	SystemClock_Config();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

