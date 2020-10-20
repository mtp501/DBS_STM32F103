#ifndef __USR_PUBLIC__
#define __USR_PUBLIC__

#include "pbdata.h"
//#include "wh_gpio.h"
//#include "wh_usart.h"
//#include "wh_spi.h"
//#include "wh_tim.h"
//#include "string.h"
//#include "stdio.h"
//#include "stdlib.h"

#include "radio.h"
#include "sx1276-LoRa.h"
#include "sx1276-LoRaMisc.h"
#include "sx1276-Hal.h"

#define LORA_BUF_LEN    128
#define USART_BUF_LEN   (LORA_BUF_LEN + 1)

#ifdef USR_MAIN
	#define MAIN_EXT
#else
	#define MAIN_EXT extern
#endif


/* UART Tx/Rx */
MAIN_EXT uint8_t RxBuffer[USART_BUF_LEN];
MAIN_EXT uint16_t UartRxLen;
MAIN_EXT bool UartRxDone;
MAIN_EXT uint8_t TxBuffer[USART_BUF_LEN];
MAIN_EXT bool UartTxBusy;

/* LoRa */
MAIN_EXT uint16_t LoRaBufSize;			// RF buffer size
MAIN_EXT uint8_t LoRaBuffer[LORA_BUF_LEN];	// RF buffer
MAIN_EXT tRadioDriver *Radio;
MAIN_EXT bool TxBusy;

//void Delay_ms(uint16_t nCount);



#endif

