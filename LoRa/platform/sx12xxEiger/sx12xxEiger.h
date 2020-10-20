#ifndef __SX12XXEIGER_H__
#define __SX12XXEIGER_H__

#include "pbdata.h"

extern volatile uint32_t TickCounter;

/*!
 * Delay code execution for "delay" ms
 */
void Delay ( uint32_t delay );
void LongDelay ( uint8_t delay );

#endif // __SX12XXEIGER_H__
