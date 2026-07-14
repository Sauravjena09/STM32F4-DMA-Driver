/*
 * stm32f4xx_rcc_driver.c
 *
 *  Created on: 15-May-2026
 *      Author: saurav
 */
#include "stm32f407xx.h"

// --- Global Arrays for Division Factors ---
// These translate the hardware bit patterns into actual math numbers
uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint8_t APB1_PreScaler[4] = {2, 4, 8, 16};


/*********************************************************************
 * @fn      		  - RCC_GetPLLOutputClock
 * @brief             - Calculates the output frequency of the Main PLL
 * @return            - uint32_t: Clock frequency in Hz
 *********************************************************************/
uint32_t RCC_GetPLLOutputClock(void) {
    uint32_t pllsrc, pllm, plln, pllp, vco_input, vco_output, pll_output;

    // 1. Find the PLL clock source (Bit 22 in PLLCFGR)
    if ((RCC->PLLCFGR >> 22) & 1) {
        pllsrc = 8000000;  // HSE (Assuming 8MHz on STM32F4 Discovery)
    } else {
        pllsrc = 16000000; // HSI (16MHz Internal)
    }

    // 2. Extract PLLM (Bits 0 to 5)
    pllm = (RCC->PLLCFGR & 0x3F);

    // 3. Extract PLLN (Bits 6 to 14)
    plln = ((RCC->PLLCFGR >> 6) & 0x1FF);

    // 4. Extract PLLP (Bits 16 to 17)
    // Formula maps 00->2, 01->4, 10->6, 11->8
    uint8_t pllp_bits = ((RCC->PLLCFGR >> 16) & 0x3);
    pllp = (pllp_bits + 1) * 2;

    // 5. Calculate final PLL speed
    vco_input = pllsrc / pllm;
    vco_output = vco_input * plln;
    pll_output = vco_output / pllp;

    return pll_output;
}


/*********************************************************************
 * @fn      		  - RCC_GetPCLK1Value
 * @brief             - Calculates the frequency of the APB1 Bus (Low Speed)
 * @return            - uint32_t: Clock frequency in Hz
 *********************************************************************/
uint32_t RCC_GetPCLK1Value(void) {
    uint32_t pclk1, systemclk;
    uint8_t clksrc, temp, ahbp, apb1p;

    // 1. Find the System Clock Source
    clksrc = ((RCC->CFGR >> 2) & 0x3);

    if(clksrc == 0) {
        systemclk = 16000000; // HSI
    } else if(clksrc == 1) {
        systemclk = 8000000;  // HSE
    } else if (clksrc == 2) {
        systemclk = RCC_GetPLLOutputClock(); // PLL
    }

    // 2. Find the AHB Prescaler (Bits 4 to 7)
    temp = ((RCC->CFGR >> 4) & 0xF);
    if(temp < 8) {
        ahbp = 1;
    } else {
        ahbp = AHB_PreScaler[temp - 8];
    }

    // 3. Find the APB1 Prescaler (Bits 10 to 12)
    temp = ((RCC->CFGR >> 10) & 0x7);
    if(temp < 4) {
        apb1p = 1;
    } else {
        apb1p = APB1_PreScaler[temp - 4];
    }

    // 4. Calculate final PCLK1
    pclk1 = (systemclk / ahbp) / apb1p;
    return pclk1;
}


/*********************************************************************
 * @fn      		  - RCC_GetPCLK2Value
 * @brief             - Calculates the frequency of the APB2 Bus (High Speed)
 * @return            - uint32_t: Clock frequency in Hz
 *********************************************************************/
uint32_t RCC_GetPCLK2Value(void) {
    uint32_t pclk2, systemclk;
    uint8_t clksrc, temp, ahbp, apb2p;

    // 1. Find the System Clock Source
    clksrc = ((RCC->CFGR >> 2) & 0x3);

    if(clksrc == 0) {
        systemclk = 16000000;
    } else if(clksrc == 1) {
        systemclk = 8000000;
    } else if (clksrc == 2) {
        systemclk = RCC_GetPLLOutputClock();
    }

    // 2. Find the AHB Prescaler (Bits 4 to 7)
    temp = ((RCC->CFGR >> 4) & 0xF);
    if(temp < 8) {
        ahbp = 1;
    } else {
        ahbp = AHB_PreScaler[temp - 8];
    }

    // 3. Find the APB2 Prescaler (Bits 13 to 15)
    // NOTE: We shift by 13 here, not 10!
    temp = ((RCC->CFGR >> 13) & 0x7);
    if(temp < 4) {
        apb2p = 1;
    } else {
        // APB1 and APB2 use the exact same division math,
        // so we can just reuse the APB1 array here.
        apb2p = APB1_PreScaler[temp - 4];
    }

    // 4. Calculate final PCLK2
    pclk2 = (systemclk / ahbp) / apb2p;
    return pclk2;
}

