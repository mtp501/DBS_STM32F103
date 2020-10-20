/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	sx12xxEiger.c
	*
	*	���ߣ� 		����������
	*
	*	���ڣ� 		2018-01-11
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		��ʱ����
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/
#include "pbdata.h"
#include "sx12xxEiger.h"

volatile uint32_t TickCounter = 0;

void Delay ( uint32_t delay )
{
    uint32_t startTick = TickCounter;
    while( ( TickCounter - startTick ) < delay );   
}

void LongDelay ( uint8_t delay )
{
    uint32_t longDelay;
    uint32_t startTick;

    longDelay = delay * 1000;

    // Wait delay s
    startTick = TickCounter;
    while( ( TickCounter - startTick ) < longDelay );   
}
