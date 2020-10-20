/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	sx1276-Hal.c
	*
	*	���ߣ� 		����������
	*
	*	���ڣ� 		2018-01-11
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		����SX1276 RESET I/O �� SX1276 DIO pins I/O
        *                       ע�⣺DIO2��DIO3��DIO4��DIO5Ӳ��EVKû�����ӣ�����ͨ������ʹ��
	*
	*	�޸ļ�¼��	
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

#define DIO2_IOPORT                                 GPIOB       //EVKδ����
#define DIO2_PIN                                    GPIO_Pin_0

#define DIO3_IOPORT                                 GPIOD       //EVKδ����
#define DIO3_PIN    				    			GPIO_Pin_3

#define DIO4_IOPORT                                 GPIOD       //EVKδ����
#define DIO4_PIN                                    GPIO_Pin_2

#define DIO5_IOPORT                                 GPIOD       //EVKδ����
#define DIO5_PIN    				    			GPIO_Pin_1

/*
************************************************************
*	�������ƣ�	SX1276InitIo
*
*	�������ܣ�	SX1276 IO��ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
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
*	�������ƣ�	SX1276SetReset
*
*	�������ܣ�	RESET��λ��λ
*
*	��ڲ�����	state ��1Ϊ��λ��0Ϊ��λ
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void SX1276SetReset( uint8_t state )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if(state == RADIO_RESET_ON )
    {
		GPIO_InitStructure.GPIO_Pin = RESET_PIN;              //loraģ���RST���ţ�����λ����
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init( RESET_IOPORT, &GPIO_InitStructure );    
		GPIO_WriteBit( RESET_IOPORT, RESET_PIN, Bit_RESET );  //������������Ϊ�͵�ƽ
    }
    else
    {
	    GPIO_InitStructure.GPIO_Pin =  RESET_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init( RESET_IOPORT, &GPIO_InitStructure );	
		GPIO_WriteBit( RESET_IOPORT, RESET_PIN, Bit_SET );    //������������Ϊ�ߵ�ƽ
    }
}

/*
************************************************************
*	�������ƣ�	SX1276Write
*
*	�������ܣ�	SX1276д����
*
*	��ڲ�����	addr����ַ��data������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void SX1276Write( uint8_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

/*
************************************************************
*	�������ƣ�	SX1276Read
*
*	�������ܣ�	SX1276������
*
*	��ڲ�����	addr����ַ��data������
*
*	���ز�����	��
*
*	˵����		
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
