/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	sx12xxEiger.c
	*
	*	作者： 		有人物联网
	*
	*	日期： 		2018-01-11
	*
	*	版本： 		V1.0
	*
	*	说明： 		延时函数
	*
	*	修改记录：	
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
