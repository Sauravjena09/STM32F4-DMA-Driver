/*
 * stm32f4xx_DMAx.h
 *
 *  Created on: Jun 28, 2026
 *      Author: saura
 */

#ifndef STM32F4XX_DMAX_H_
#define STM32F4XX_DMAX_H_


#include "stm32f407xx.h"
typedef enum{
	DMA_PL_LOW,
	DMA_PL_MEDIUM,
	DMA_PL_HIGH,
	DMA_PL_VERYHIGH,
}DMA_SPL;
typedef enum{
	DMA_DIR_P2M,
	DMA_DIR_M2P,
	DMA_DIR_M2M,
}Direction;

typedef enum{
	DMA_DSIZE_BYTE,
	DMA_DSIZE_HALFWORD,
	DMA_DSIZE_WORD,
}Data_Size;

typedef enum{
	DMA_INC_DISABLE,
	DMA_INC_ENABLE,
}MEM_INC;

typedef enum{
	DMA_CHANNEL_0,
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7,
}Channel;

typedef enum{
	DMA_MODE_NORMAL,
	DMA_MODE_CIRCULAR,
}Mode;
typedef enum{
	DMA_FCONTROLLER,
	PERI_FCONTROLLER
}DMA_FCONTROL;
// Burst Mode (Memory and Peripheral)
typedef enum {
    DMA_BURST_SINGLE = 0,
    DMA_BURST_INCR4,
    DMA_BURST_INCR8,
    DMA_BURST_INCR16
} DMA_Burst_t;

// FIFO Mode (Direct mode disable)
typedef enum {
    DMA_FIFO_DISABLE = 0,
    DMA_FIFO_ENABLE
} DMA_FIFO_Mode_t;

typedef enum {
    DMA_FIFO_TH_1QUARTER = 0,
    DMA_FIFO_TH_HALF,
    DMA_FIFO_TH_3QUARTER,
    DMA_FIFO_TH_FULL
} DMA_FIFO_Threshold_t;
typedef struct{
	Channel Channelx;
	Direction Directionx;
	Data_Size MemDataSize;
	Data_Size PeriphDataSize;
	MEM_INC MemInc;
	MEM_INC PeriphInc;
	Mode NorCircMode;
	DMA_SPL Priorty;
	DMA_FCONTROL Controller;
	DMA_Burst_t MemBurst;
	DMA_Burst_t PeriphBurst;
	DMA_FIFO_Mode_t FIFOMode;
	DMA_FIFO_Threshold_t FIFOThreshold;
	uint8_t DoubleBufferMode;
}DMA_Config_t;

typedef struct{
	DMA_RegDef_t *DMAx;
	DMA_Stream_RegDef_t *pDMA_Stream;
	DMA_Config_t DMA_Config;
}DMA_Handle_t;
/****************API*******************/
uint8_t DMA_Init(DMA_Handle_t *pDMAHandle);
void DMA_DeInit(DMA_Handle_t *pDMAHandle);

uint8_t DMA_StartTransfer(DMA_Handle_t *pDMAHandle,uint32_t src_addr,uint32_t dest_addr,uint32_t memory2_addr,uint32_t length);
void DMA_IRQHandling(DMA_Handle_t *pDMAHandle);
void DMA_PeriClockControl(DMA_RegDef_t *DMAx,uint8_t EnorDi);
uint8_t DMA_StartTransfer_IT(DMA_Handle_t *pDMAHandle, uint32_t src_addr, uint32_t dest_addr,uint32_t memory2_addr, uint32_t length);
void DMA_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);
void DMA_InterruptConfig(uint8_t IRQNumber,uint8_t EnorDi);
__attribute__((weak)) void DMA_ApplicationEventCallback(DMA_Handle_t *pDMAHandle,uint8_t AppEv);
//macros of application event//
#define DMA_HALFTRANS_HTIF   0U
#define DMA_COMPLETE_TCIF    1U
#define DMA_ERROR_TEIF       2U
#define DMA_OVUN_FEIF        3U
#define DMA_MERRROR_DMEIF    4U
/**************************/

#endif /* STM32F4XX_DMAX_H_ */
