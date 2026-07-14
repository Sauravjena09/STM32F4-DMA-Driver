/*
 * stm32f4xx_DMAx.c
 *
 *  Created on: Jun 28, 2026
 *      Author: sauraV
 */


#include<stm32f407xx.h>
#include<stm32f4xx_DMAx.h>
/*********************************************************************
@fn      		  - DMA_Init
@brief             - Initializes the DMA stream according to the
                configuration parameters in the DMA handle structure.
@param[in]         - pDMAHandle: Pointer to the DMA handle structure
                 containing configuration (direction, data sizes,
                 burst settings, FIFO mode, circular mode, etc.).
@return            - None
@Note              - Must enable the DMA peripheral clock before calling.
                 Ensure the DMA stream is disabled (EN bit = 0)
                 before applying these configuration changes.
*********************************************************************/

uint8_t DMA_Init(DMA_Handle_t *pDMAHandle){
//enabling the clock;
DMA_PeriClockControl(pDMAHandle->DMAx, ENABLE);
uint32_t control_bit=0;
uint32_t fifo_bit=0;
//clearing the DMA_LISR and DMA_HISR register
DMA_DeInit(pDMAHandle);
if (pDMAHandle->DMA_Config.Directionx == DMA_DIR_M2M) {
    if (pDMAHandle->DMAx != DMA2) return INIT_FAULT;
    if (pDMAHandle->DMA_Config.FIFOMode == DMA_FIFO_DISABLE) return INIT_FAULT;
}
if (pDMAHandle->DMA_Config.FIFOMode == DMA_FIFO_DISABLE) {
    // MSIZE and PSIZE must match
    if (pDMAHandle->DMA_Config.MemDataSize != pDMAHandle->DMA_Config.PeriphDataSize) {
        return INIT_FAULT;
    }
    // Bursts are not allowed in Direct Mode
    if (pDMAHandle->DMA_Config.MemBurst != 0 || pDMAHandle->DMA_Config.PeriphBurst != 0) {
        return INIT_FAULT;
    }
}

//configuring the dma channel(channel selection);
control_bit |= (pDMAHandle->DMA_Config.Channelx << DMA_SxCR_CHSEL);
//configuring the data transfer direction
control_bit |= (pDMAHandle->DMA_Config.Directionx << DMA_SxCR_DIR);
//configuring the mode {circular or normal mode}
control_bit |= (pDMAHandle->DMA_Config.NorCircMode << DMA_SxCR_CIRC);
//configuring the peripheral increment mode
control_bit |= (pDMAHandle->DMA_Config.PeriphInc << DMA_SxCR_PINC);
////configuring the memory increment mode
control_bit |= (pDMAHandle->DMA_Config.MemInc << DMA_SxCR_MINC);
//configuring the Peripheral data size
control_bit |= (pDMAHandle->DMA_Config.PeriphDataSize <<DMA_SxCR_PSIZE);
//configuring the memory  data size
control_bit |= (pDMAHandle->DMA_Config.MemDataSize <<DMA_SxCR_MSIZE);
//managing the priorty level of the channel
control_bit |= (pDMAHandle->DMA_Config.Priorty << DMA_SxCR_PL);
//manging the peripheral flow controller
control_bit |= (pDMAHandle->DMA_Config.Controller << DMA_SxCR_PFCTRL);
// Double buffer mode
control_bit |= (pDMAHandle->DMA_Config.DoubleBufferMode << DMA_SxCR_DBM);
// Peripheral burst transfer configuration
control_bit |= (pDMAHandle->DMA_Config.PeriphBurst << DMA_SxCR_PBURST);
// Memory burst transfer configuration
control_bit |= (pDMAHandle->DMA_Config.MemBurst << DMA_SxCR_MBURST);

pDMAHandle->pDMA_Stream->CR = control_bit;
// FIFO Alignment Check: Threshold vs Burst Size
if(pDMAHandle->DMA_Config.FIFOMode == DMA_FIFO_ENABLE) {
    const uint32_t burst_beats[] = {1, 4, 8, 16};
    const uint32_t size_bytes[]  = {1, 2, 4};
    const uint32_t fifo_thr[]    = {4, 8, 12, 16};

    uint8_t burst_beat, size_beat;

    // Grab the right burst and size based on direction

       burst_beat = burst_beats[pDMAHandle->DMA_Config.MemBurst];
       size_beat  = size_bytes[pDMAHandle->DMA_Config.MemDataSize];


    uint32_t burst_size_bytes = size_beat * burst_beat;
    uint32_t threshold_bytes = fifo_thr[pDMAHandle->DMA_Config.FIFOThreshold];

    // Check if threshold is a perfect multiple of the burst size
    if(((threshold_bytes % burst_size_bytes) == 0) && (burst_size_bytes <= 16)) {
        fifo_bit |= (pDMAHandle->DMA_Config.FIFOMode << DMA_SxFCR_DMDIS);
        fifo_bit |= (pDMAHandle->DMA_Config.FIFOThreshold << DMA_SxFCR_FTH);

        pDMAHandle->pDMA_Stream->FCR = fifo_bit;
    } else {
        return INIT_FAULT; // Configuration forbidden by hardware
    }
}


return INIT_OK;

}

/*********************************************************************
 * @fn      		  - DMA_PeriClockControl
 *
 * @brief             - Enables or disables the peripheral clock for a given DMA port.
 *
 * @param[in]         - pDMAx: Base address of the DMA peripheral.
 * @param[in]         - EnorDi: Enable or Disable macro (ENABLE/DISABLE).
 *
 * @return            - None
 *********************************************************************/
void DMA_PeriClockControl(DMA_RegDef_t *DMAx,uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(DMAx == DMA1){
			DMA1_PCLK_EN();

		}else if (DMAx == DMA2){
			DMA2_PCLK_EN();
		}
	}else{
	if(DMAx == DMA1){
		DMA1_PCLK_DI();

	}else if(DMAx == DMA2){
		DMA2_PCLK_DI();
}
	}
}

/*********************************************************************
 * @fn      		  - DMA_DeInit
 *
 * @brief             - Resets the DMA peripheral registers to their default
 *                      reset values.
 *
 * @param[in]         - pDMAHandle
 *
 * @return            - None
 *
 * @Note              - None
 *********************************************************************/
void DMA_DeInit(DMA_Handle_t *pDMAHandle) {
    // 1. Disable the stream
    pDMAHandle->pDMA_Stream->CR &= ~(1 << DMA_SxCR_EN);

    // 2. Wait until the EN bit is cleared (stream is fully disabled)
    while ((pDMAHandle->pDMA_Stream->CR) & (1 << DMA_SxCR_EN));

    // 3. Reset all stream-specific registers to 0
    pDMAHandle->pDMA_Stream->CR   = 0;
    pDMAHandle->pDMA_Stream->NDTR = 0;
    pDMAHandle->pDMA_Stream->PAR  = 0;
    pDMAHandle->pDMA_Stream->M0AR = 0;
    pDMAHandle->pDMA_Stream->M1AR = 0;
    pDMAHandle->pDMA_Stream->FCR  = 0x00000021U; // Default reset value for FCR


    uint8_t streamNumber = pDMAHandle->pDMA_Stream - pDMAHandle->DMAx->Stream;


    if (streamNumber <= 3) {

        uint8_t shifts[4] = {0, 6, 16, 22};
        pDMAHandle->DMAx->LIFCR = (0x3F << shifts[streamNumber]); // 0x3F clears all 6 flag bits
    } else {
        uint8_t shifts[4] = {0, 6, 16, 22};
        pDMAHandle->DMAx->HIFCR = (0x3F << shifts[streamNumber - 4]);
    }
}

static uint8_t DMA_SetupStream(DMA_Handle_t *pDMAHandle,uint32_t src_addr,uint32_t dest_addr,uint32_t memory2_addr,uint32_t length){
	//CHECKING IF ALREADY THERE IS STREAM ENABLE OR NOT
	if(pDMAHandle->pDMA_Stream->CR &(1 << DMA_SxCR_EN))return INIT_FAULT;
	const uint32_t size_bytes[]  = {1, 2, 4}; // Byte=1, HalfWord=2, Word=4
	const uint32_t burst_beats[] = {1, 4, 8, 16};

	// Get the actual values from the registers
	uint32_t m_burst = burst_beats[pDMAHandle->DMA_Config.MemBurst];
	uint32_t m_size  = size_bytes[pDMAHandle->DMA_Config.MemDataSize];
	uint32_t p_size  = size_bytes[pDMAHandle->DMA_Config.PeriphDataSize];
	uint8_t direction = pDMAHandle->DMA_Config.Directionx;

	if (direction == DMA_DIR_P2M) {
		pDMAHandle->pDMA_Stream->PAR  = src_addr;
		pDMAHandle->pDMA_Stream->M0AR = dest_addr;
	}
	else if (direction == DMA_DIR_M2P) {
		pDMAHandle->pDMA_Stream->M0AR = src_addr;
		pDMAHandle->pDMA_Stream->PAR  = dest_addr;
	}
	else if (direction == DMA_DIR_M2M) {
		pDMAHandle->pDMA_Stream->PAR  = src_addr;
		pDMAHandle->pDMA_Stream->M0AR = dest_addr;
	}

	// 2. Handle Double Buffer Mode safely using Bitwise AND (&)
	if (pDMAHandle->pDMA_Stream->CR & (1 << DMA_SxCR_DBM)) {
		pDMAHandle->pDMA_Stream->M1AR = memory2_addr;
	}
	//aligment checking for the burst
	if (direction == DMA_DIR_M2P || direction == DMA_DIR_M2M) {
		if ((src_addr % m_size) != 0) return INIT_FAULT;
		if ((dest_addr % p_size) != 0) return INIT_FAULT;
	}else{
		if ((src_addr % p_size) != 0) return INIT_FAULT;
		if ((dest_addr % m_size) != 0) return INIT_FAULT;

	}
	uint32_t p_burst = burst_beats[pDMAHandle->DMA_Config.PeriphBurst];

	if (p_burst > 1) {
		if ((length % p_burst) != 0) {
			return INIT_FAULT;
		}
	}

	if(pDMAHandle->pDMA_Stream->CR & (1 << DMA_SxCR_CIRC)){



		// The Rule: (Length * PSize) must be a multiple of (Burst * MSize)
		// We avoid division entirely by checking:
		// (Length * PSize) % (MBurst * MSize) == 0

		uint32_t required_alignment = m_burst * m_size;
		uint32_t total_transfer_bytes = length * p_size;

		if ((total_transfer_bytes % required_alignment) == 0) {
			pDMAHandle->pDMA_Stream->NDTR = length;
		} else {
			return INIT_FAULT; // Alignment constraint violated!
		}
	}else{
		pDMAHandle->pDMA_Stream->NDTR = length;
	}

	//CLEARLING THE FLAGS
	uint32_t streamNumber = pDMAHandle->pDMA_Stream - pDMAHandle->DMAx->Stream;
	uint8_t shifts[4] = {0, 6, 16, 22};

	if (streamNumber <= 3) {
		pDMAHandle->DMAx->LIFCR = (0x3F << shifts[streamNumber]);
	} else {
		pDMAHandle->DMAx->HIFCR = (0x3F << shifts[streamNumber - 4]);
	}
	return INIT_OK;
}

uint8_t DMA_StartTransfer(DMA_Handle_t *pDMAHandle,uint32_t src_addr,uint32_t dest_addr,uint32_t memory2_addr,uint32_t length){
	if (!DMA_SetupStream(pDMAHandle, src_addr, dest_addr, memory2_addr, length)) return INIT_FAULT;
	   	    pDMAHandle->pDMA_Stream->CR |= (1 << DMA_SxCR_EN);
return INIT_OK;

}
uint8_t DMA_StartTransfer_IT(DMA_Handle_t *pDMAHandle, uint32_t src_addr, uint32_t dest_addr,uint32_t memory2_addr, uint32_t length){
	if (!DMA_SetupStream(pDMAHandle, src_addr, dest_addr, memory2_addr, length)) return INIT_FAULT;



       pDMAHandle->pDMA_Stream->CR |= (1 << DMA_SxCR_DMEIE) | (1 << DMA_SxCR_TCIE) |
                                           (1 << DMA_SxCR_HTIE) | (1 << DMA_SxCR_TEIE);
       if(pDMAHandle->DMA_Config.FIFOMode == DMA_FIFO_ENABLE){
    	   pDMAHandle->pDMA_Stream->FCR |= (1 << DMA_SxFCR_FEIE);
       }
       //handling the interrupt part;
	    pDMAHandle->pDMA_Stream->CR |= (1 << DMA_SxCR_EN);
   return INIT_OK;
}

void DMA_IRQHandling(DMA_Handle_t *pDMAHandle){
	uint32_t streamNumber = pDMAHandle->pDMA_Stream - pDMAHandle->DMAx->Stream;
	uint8_t Interrupt_streamnumber = streamNumber % 4;

	// 2. Base bit offsets for Streams 0/4, 1/5, 2/6, 3/7
	uint8_t bits[4] = {0, 6, 16, 22};
	uint8_t base_bit = bits[Interrupt_streamnumber];

	uint8_t FEIFx  = base_bit + 0;
	uint8_t DMEIFx = base_bit + 2;
	uint8_t TEIFx  = base_bit + 3;
	uint8_t HTIFx  = base_bit + 4;
	uint8_t TCIFx  = base_bit + 5;

	// 3. Handle Streams 0 to 3 (Low Registers)
	if (streamNumber <= 3) {

	    if (pDMAHandle->DMAx->LISR & (1 << FEIFx)) {
	        pDMAHandle->DMAx->LIFCR = (1 << FEIFx); // Write 1 to clear!
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_OVUN_FEIF);
	    }
	    if (pDMAHandle->DMAx->LISR & (1 << DMEIFx)) {
	        pDMAHandle->DMAx->LIFCR = (1 << DMEIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_MERRROR_DMEIF);
	    }
	    if (pDMAHandle->DMAx->LISR & (1 << TEIFx)) {
	        pDMAHandle->DMAx->LIFCR = (1 << TEIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_ERROR_TEIF);
	    }
	    if (pDMAHandle->DMAx->LISR & (1 << HTIFx)) {
	        pDMAHandle->DMAx->LIFCR = (1 << HTIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_HALFTRANS_HTIF);
	    }
	    if (pDMAHandle->DMAx->LISR & (1 << TCIFx)) {
	        pDMAHandle->DMAx->LIFCR = (1 << TCIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_COMPLETE_TCIF);
	    }

	}
	// 4. Handle Streams 4 to 7 (High Registers)
	else {

	    if (pDMAHandle->DMAx->HISR & (1 << FEIFx)) {
	        pDMAHandle->DMAx->HIFCR = (1 << FEIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_OVUN_FEIF);
	    }
	    if (pDMAHandle->DMAx->HISR & (1 << DMEIFx)) {
	        pDMAHandle->DMAx->HIFCR = (1 << DMEIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_MERRROR_DMEIF);
	    }
	    if (pDMAHandle->DMAx->HISR & (1 << TEIFx)) {
	        pDMAHandle->DMAx->HIFCR = (1 << TEIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_ERROR_TEIF);
	    }
	    if (pDMAHandle->DMAx->HISR & (1 << HTIFx)) {
	        pDMAHandle->DMAx->HIFCR = (1 << HTIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_HALFTRANS_HTIF);
	    }
	    if (pDMAHandle->DMAx->HISR & (1 << TCIFx)) {
	        pDMAHandle->DMAx->HIFCR = (1 << TCIFx);
	        DMA_ApplicationEventCallback(pDMAHandle, DMA_COMPLETE_TCIF);
	    }
	}

}
/*********************************************************************
 * @fn      		  - DMA_InterruptConfig
 *
 * @brief             - Configures the interrupt for a specific DMA peripheral.
 *
 * @param[in]         - IRQNumber: Interrupt request number associated with DMA.
 * @param[in]         - EnorDi: Enable or Disable macro (ENABLE/DISABLE).
 *
 * @return            - None
 *
 * @Note              - NVIC registers are configured in this function.
 *********************************************************************/
void DMA_InterruptConfig(uint8_t IRQNumber,uint8_t EnorDi){
	if(EnorDi == ENABLE)
	  {
		  if(IRQNumber <=31U){
	         *NVIC_ISER0 = (1U << IRQNumber);

		  }else if(IRQNumber >31U && IRQNumber< 64U){
			  *NVIC_ISER1 = (1U << (IRQNumber%32));
		  }else if(IRQNumber >= 64U && IRQNumber < 96U){
			  *NVIC_ISER2 = (1U << (IRQNumber%32));
		  }
	  }else{
		  if(IRQNumber <=31U){
		          *NVIC_ICER0 = (1U << (IRQNumber));
		          }else if(IRQNumber >31 && IRQNumber< 64){
		 		  *NVIC_ICER1 = (1U << (IRQNumber%32));
		 	  }else if(IRQNumber >= 64 && IRQNumber < 96){
		 		  *NVIC_ICER2 = (1U << (IRQNumber%32));
		 	  }

		  }

}
/*********************************************************************
 * @fn      		  - DMA_IRQPriorityConfig
 *
 * @brief             - Configures the priority of a given DMA interrupt.
 *
 * @param[in]         - IRQNumber: Interrupt request number.
 * @param[in]         - IRQPriority: Priority level for the interrupt.
 *
 * @return            - None
 *
 * @Note              - NVIC priority registers are configured in this function.
 *********************************************************************/
void DMA_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority){
	//1. first lets find out the ipr register
		uint8_t iprx = IRQNumber / 4;
		uint8_t iprx_section  = IRQNumber %4 ;

		uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

		*( (volatile uint32_t*)(NVIC_PR_BASE_ADDR + iprx) ) |= (IRQPriority << shift_amount);

}
