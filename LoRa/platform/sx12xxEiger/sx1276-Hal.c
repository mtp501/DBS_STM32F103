/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	sx1276-Hal.c
	*
	*	作者： 		有人物联网
	*
	*	日期： 		2018-01-11
	*
	*	版本： 		V1.0
	*
	*	说明： 		配置SX1276 RESET I/O 和 SX1276 DIO pins I/O
        *                       注意：DIO2、DIO3、DIO4、DIO5硬件EVK没有连接，常规通信无需使用
	*
	*	修改记录：	
	************************************************************
	************************************************************
	************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h> 
#include "platform.h"
#include "QS_public.h"

#define Bit_SET					    SET
#define Bit_RESET				    RESET

#if defined( USE_SX1276_RADIO )

#include "spi.h"
#include "../../radio/sx1276-Hal.h"

/*!
 * SX1276 RESET I/O definitions
 */
#define RESET_IOPORT                                GPIOB
#define RESET_PIN                                   GPIO_Pin_1

/*!
 * SX1276 DIO pins  I/O definitions
 */
#define DIO0_IOPORT                                 GPIOB
#define DIO0_PIN                                    GPIO_Pin_3

#define DIO1_IOPORT                                 GPIOB
#define DIO1_PIN                                    GPIO_Pin_2

#define DIO2_IOPORT                                 GPIOB       //EVK未连接
#define DIO2_PIN                                    GPIO_Pin_0

#define DIO3_IOPORT                                 GPIOD       //EVK未连接
#define DIO3_PIN    				    			GPIO_Pin_3

#define DIO4_IOPORT                                 GPIOD       //EVK未连接
#define DIO4_PIN                                    GPIO_Pin_2

#define DIO5_IOPORT                                 GPIOD       //EVK未连接
#define DIO5_PIN    				    			GPIO_Pin_1

/*
************************************************************
*	函数名称：	SX1276InitIo
*
*	函数功能：	SX1276 IO初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void SX1276InitIo( void )
{
//    // Configure radio DIO as inputs
//    GPIO_Init(DIO0_IOPORT, DIO0_PIN, GPIO_Mode_In_FL_No_IT);

//    // Configure radio DI1 as inputs
//    GPIO_Init(DIO1_IOPORT, DIO1_PIN, GPIO_Mode_In_FL_No_IT);

//    // Configure radio DI2 as inputs
//    GPIO_Init(DIO2_IOPORT, DIO2_PIN, GPIO_Mode_In_FL_No_IT);

//    // Configure radio DI3 as inputs
//    GPIO_Init(DIO3_IOPORT, DIO3_PIN, GPIO_Mode_In_FL_No_IT);

//    // Configure radio DI4 as inputs
//    GPIO_Init(DIO4_IOPORT, DIO4_PIN, GPIO_Mode_In_FL_No_IT);

//    // Configure radio DI5 as inputs
//    GPIO_Init(DIO5_IOPORT, DIO5_PIN, GPIO_Mode_In_FL_No_IT);
}

/*
************************************************************
*	函数名称：	SX1276SetReset
*
*	函数功能：	RESET置位或复位
*
*	入口参数：	state ：1为置位，0为复位
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void SX1276SetReset( uint8_t state )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if(state == RADIO_RESET_ON )
    {
		GPIO_InitStructure.GPIO_Pin = RESET_PIN;              //lora模块的RST引脚，即复位引脚
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init( RESET_IOPORT, &GPIO_InitStructure );    
		GPIO_WriteBit( RESET_IOPORT, RESET_PIN, Bit_RESET );  //将该引脚设置为低电平
    }
    else
    {
	    GPIO_InitStructure.GPIO_Pin =  RESET_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init( RESET_IOPORT, &GPIO_InitStructure );	
		GPIO_WriteBit( RESET_IOPORT, RESET_PIN, Bit_SET );    //将该引脚设置为高电平
    }
}

/*
************************************************************
*	函数名称：	SX1276Write
*
*	函数功能：	SX1276写函数
*
*	入口参数：	addr：地址，data：数据
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void SX1276Write( uint8_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

/*
************************************************************
*	函数名称：	SX1276Read
*
*	函数功能：	SX1276读函数
*
*	入口参数：	addr：地址，data：数据
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void SX1276Read( uint8_t addr, uint8_t *data )
{
    SX1276ReadBuffer( addr, data, 1 );
}

void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //CS = 0;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_RESET );

    SpiInOut( addr | 0x80 );
    for( i = 0; i < size; i++ )
    {
        SpiInOut( buffer[i] );
    }

    //CS = 1;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_SET );
}

void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //CS = 0;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_RESET );

    SpiInOut( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( 0 );
    }

    //CS = 1;
    GPIO_WriteBit( SPI_PORT, SPI_CS_PIN, Bit_SET );
}

void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
    SX1276WriteBuffer( 0, buffer, size );
}

void SX1276ReadFifo( uint8_t *buffer, uint8_t size )
{
    SX1276ReadBuffer( 0, buffer, size );
}

inline uint8_t SX1276ReadDio0( void )
{
    return GPIO_ReadInputDataBit( DIO0_IOPORT, DIO0_PIN );
}

inline uint8_t SX1276ReadDio1( void )
{
    return GPIO_ReadInputDataBit( DIO1_IOPORT, DIO1_PIN );
}

inline uint8_t SX1276ReadDio2( void )
{
    return GPIO_ReadInputDataBit( DIO2_IOPORT, DIO2_PIN );
}

inline uint8_t SX1276ReadDio3( void )
{
    return GPIO_ReadInputDataBit( DIO3_IOPORT, DIO3_PIN );
}

inline uint8_t SX1276ReadDio4( void )
{
    return GPIO_ReadInputDataBit( DIO4_IOPORT, DIO4_PIN );
}

inline uint8_t SX1276ReadDio5( void )
{
    return GPIO_ReadInputDataBit( DIO5_IOPORT, DIO5_PIN );
}

inline void SX1276WriteRxTx( uint8_t txEnable )
{
    //printf("*********SX1276WriteRxTx en:%d\r\n", txEnable);
}

#endif // USE_SX1276_RADIO
