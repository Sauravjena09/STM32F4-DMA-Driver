/*
 * stm32f407xx.h
 *
 *  Created on: 06-Mar-2026
 *      Author: saurav
 */
//FOR STM32F4XX DRIVER
#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stddef.h>
#include<stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))
//////////////MCU SPECIFIC PERIPHERALS/////////////////////
//ISER REGISTERS MACROS (SET ENABLE THE REGISTER)
#define NVIC_ISER0   ((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1   ((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2   ((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3   ((volatile uint32_t*)0xE000E10C)
//ICER REGISTERS MACROS (CLEAR ENABLE REGISTERS)
#define NVIC_ICER0    ((volatile uint32_t*)0XE000E180)
#define NVIC_ICER1    ((volatile uint32_t*)0XE000E184)
#define NVIC_ICER2    ((volatile uint32_t*)0XE000E188)
#define NVIC_ICER3    ((volatile uint32_t*)0XE000E18C)

#define NVIC_PR_BASE_ADDR  ((volatile uint32_t*)0xE000E400)
#define NO_PR_BITS_IMPLEMENTED    4
//MEMOERY MACROS
#define FLASH_BASEADDR  0x08000000UL //address of the flash
#define SRAM1_BASEADDR  0x20000000UL //address of the sram1 (112kb)
#define SRAM2_BASEADDR  0x2001C000UL //address of the sram2(16KB)
#define SRAM SRAM1_BASEADDR        //starting point of the SRAM(SRAM1+SRAM2)
#define ROM 0x1FFF0000UL           // ROM ADDRESS

//BUS MACROS
#define PERIPH_BASE 0x40000000UL
#define APB1PERIPH_BASEADDR PERIPH_BASE
#define APB2PERIPH_BASEADDR 0x40010000UL
#define AHB1PERIPH_BASEADDR 0x40020000UL
#define AHB2PERIPH_BASEADDR 0x50000000UL

//BASE ADDRESS OF THE PERIPHERALS WHICH ARE ATTACHED ON AHB1 BUS
#define GPIOA_BASEADDR   (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR   (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR   (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR   (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR   (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR   (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR   (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR   (AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR   (AHB1PERIPH_BASEADDR + 0x2000)
#define GPIOJ_BASEADDR   (AHB1PERIPH_BASEADDR + 0x2400)
#define GPIOK_BASEADDR   (AHB1PERIPH_BASEADDR + 0x2800)
#define RCC_BASEADDR     (AHB1PERIPH_BASEADDR + 0x3800)
#define DMA1_BASEADDR    (AHB1PERIPH_BASEADDR + 0x6000)
#define DMA2_BASEADDR    (AHB1PERIPH_BASEADDR + 0x6400)

//BASE ADDRESS OF THE PERIPHERALS WHICH ARE ATTACHED ON APB1 BUS

#define SPI2_BASEADDR     (APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR     (APB1PERIPH_BASEADDR + 0x3C00)
#define USART2_BASEADDR   (APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR   (APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR    (APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR    (APB1PERIPH_BASEADDR + 0x5000)
#define I2C1_BASEADDR     (APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR     (APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR     (APB1PERIPH_BASEADDR + 0x5C00)

//BASE ADDRESS OF THE PERIPHERALS WHICH ARE ATTACHED ON APB2 BUS

#define SPI1_BASEADDR     (APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR     (APB2PERIPH_BASEADDR + 0x3400)
#define USART1_BASEADDR   (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR   (APB2PERIPH_BASEADDR + 0x1400)
#define EXTI_BASEADDR     (APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR   (APB2PERIPH_BASEADDR + 0x3800)


/*******************************************************************************
 * Peripheral register definition structures
 * Note: Registers in peripherals are specific to the MCU.
 * The number of registers for a particular peripheral type may vary.
 * Always check the reference manual of the device.
 ******************************************************************************/

typedef struct
{
    volatile uint32_t MODER;    // 0x00: Mode register
    volatile uint32_t OTYPER;   // 0x04: Output type register
    volatile uint32_t OSPEEDR;  // 0x08: Output speed register
    volatile uint32_t PUPDR;    // 0x0C: Pull-up/pull-down register
    volatile uint32_t IDR;      // 0x10: Input data register
    volatile uint32_t ODR;      // 0x14: Output data register
    volatile uint32_t BSRR;     // 0x18: Bit set/reset register
    volatile uint32_t LCKR;     // 0x1C: Configuration lock register
    volatile uint32_t AFR[2];     // 0x20: Alternate function low register
} GPIO_RegDef_t;

#define GPIOA        (( GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB        (( GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC        (( GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD        (( GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE        (( GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF        (( GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG        (( GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH        (( GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI        (( GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ        (( GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK        (( GPIO_RegDef_t*)GPIOK_BASEADDR)

typedef struct {
	volatile uint32_t CR1;   //SPI control register
	volatile uint32_t CR2;   //SPI control register 2
	volatile uint32_t SR;    //SPI status register
	volatile uint32_t DR;    //SPI data register
	volatile uint32_t CRCPR;   //SPI CRC polynomial register
	volatile uint32_t RXCRCR;  //SPI RX CRC register
	volatile uint32_t TXCRCR;  //SPI TX CRC register
	volatile uint32_t I2SCFGR; //SPI_I2S configuration register
	volatile uint32_t I2SPR;  // prescaler register
}SPI_RegDef_t;

#define SPI1      ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2      ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3      ((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4      ((SPI_RegDef_t*)SPI4_BASEADDR)

//FOR RCC REGISTER
typedef struct
{
    volatile uint32_t CR;          // 0x00: Clock control register
    volatile uint32_t PLLCFGR;     // 0x04: PLL configuration register
    volatile uint32_t CFGR;        // 0x08: Clock configuration register
    volatile uint32_t CIR;         // 0x0C: Clock interrupt register
    volatile uint32_t AHB1RSTR;    // 0x10: AHB1 peripheral reset register
    volatile uint32_t AHB2RSTR;    // 0x14: AHB2 peripheral reset register
    volatile uint32_t AHB3RSTR;    // 0x18: AHB3 peripheral reset register
    uint32_t RESERVED0;            // 0x1C: Reserved
    volatile uint32_t APB1RSTR;    // 0x20: APB1 peripheral reset register
    volatile uint32_t APB2RSTR;    // 0x24: APB2 peripheral reset register
    uint32_t RESERVED1[2];         // 0x28–0x2C: Reserved
    volatile uint32_t AHB1ENR;     // 0x30: AHB1 peripheral clock enable register
    volatile uint32_t AHB2ENR;     // 0x34: AHB2 peripheral clock enable register
    volatile uint32_t AHB3ENR;     // 0x38: AHB3 peripheral clock enable register
    uint32_t RESERVED2;            // 0x3C: Reserved
    volatile uint32_t APB1ENR;     // 0x40: APB1 peripheral clock enable register
    volatile uint32_t APB2ENR;     // 0x44: APB2 peripheral clock enable register
    uint32_t RESERVED3[2];         // 0x48–0x4C: Reserved
    volatile uint32_t AHB1LPENR;   // 0x50: AHB1 peripheral clock enable in low power mode
    volatile uint32_t AHB2LPENR;   // 0x54: AHB2 peripheral clock enable in low power mode
    volatile uint32_t AHB3LPENR;   // 0x58: AHB3 peripheral clock enable in low power mode
    uint32_t RESERVED4;            // 0x5C: Reserved
    volatile uint32_t APB1LPENR;   // 0x60: APB1 peripheral clock enable in low power mode
    volatile uint32_t APB2LPENR;   // 0x64: APB2 peripheral clock enable in low power mode
    uint32_t RESERVED5[2];         // 0x68–0x6C: Reserved
    volatile uint32_t BDCR;        // 0x70: Backup domain control register
    volatile uint32_t CSR;         // 0x74: Clock control & status register
    uint32_t RESERVED6[2];         // 0x78–0x7C: Reserved
    volatile uint32_t SSCGR;       // 0x80: Spread spectrum clock generation register
    volatile uint32_t PLLI2SCFGR;  // 0x84: PLLI2S configuration register
    volatile uint32_t PLLSAICFGR;  // 0x88: PLLSAI configuration register
    volatile uint32_t DCKCFGR;     // 0x8C: Dedicated Clocks configuration register
} RCC_RegDef_t;
//struct define for rcc
#define RCC     ((RCC_RegDef_t*)RCC_BASEADDR)
typedef struct
{
    volatile uint32_t MEMRMP;       // 0x00: Memory remap register
    volatile uint32_t PMC;          // 0x04: Peripheral mode control register
    volatile uint32_t EXTICR[4];    // 0x08-0x14: External interrupt configuration registers
    uint32_t RESERVED[2];           // 0x18-0x1C: Reserved
    volatile uint32_t CMPCR;        // 0x20: Compensation cell control register
} SYSCFG_RegDef_t;


#define SYSCFG    ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;

}EXTI_RegDef_t;
#define EXTI              ((EXTI_RegDef_t*)EXTI_BASEADDR)

typedef struct
{  volatile uint32_t CR1;
   volatile uint32_t CR2;
   volatile uint32_t OAR1;
   volatile uint32_t OAR2;
   volatile uint32_t DR;
   volatile uint32_t SR1;
   volatile uint32_t SR2;
   volatile uint32_t CCR;
   volatile uint32_t TRISE;
   volatile uint32_t FLTR;
}I2C_RegDef_t;
#define I2C1           ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2           ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3           ((I2C_RegDef_t*)I2C3_BASEADDR)


/***********DMA1/DMA2***************/
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t NDTR;
    volatile uint32_t PAR;
    volatile uint32_t M0AR;
    volatile uint32_t M1AR;
    volatile uint32_t FCR;
} DMA_Stream_RegDef_t;

typedef struct {
    volatile uint32_t LISR;
    volatile uint32_t HISR;
    volatile uint32_t LIFCR;
    volatile uint32_t HIFCR;
    DMA_Stream_RegDef_t Stream[8];
} DMA_RegDef_t;

#define DMA1 ((DMA_RegDef_t*)DMA1_BASEADDR)
#define DMA2 ((DMA_RegDef_t*)DMA2_BASEADDR)
/***********************ENABLING CLOCK MACROS**********************/
//CLOCK ENABLE FOR GPIOx peripherals

#define GPIOA_PCLK_EN()     (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()     (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()     (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()     (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()     (RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()     (RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()     (RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()     (RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()     (RCC->AHB1ENR |= (1<<8))
#define GPIOJ_PCLK_EN()     (RCC->AHB1ENR |= (1<<9))
#define GPIOK_PCLK_EN()     (RCC->AHB1ENR |= (1<<10))
//CLOCK ENABLE FOR THE DMAx Peripherals
#define DMA1_PCLK_EN()      (RCC->AHB1ENR |= (1<<21))
#define DMA2_PCLK_EN()      (RCC->AHB1ENR |= (1<<22))
// CLOCK ENABLE MACROS FOR I2Cx peripherals
#define I2C1_PCLK_EN()    (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()    (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()    (RCC->APB1ENR |= (1 << 23))

// CLOCK ENABLE MACROS FOR SPIx peripherals
#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR |= (1 << 15))

// CLOCK ENABLE MACROS FOR USART/UARTx peripherals
#define USART1_PCLK_EN()  (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()  (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()  (RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()   (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()   (RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()  (RCC->APB2ENR |= (1 << 5))

// CLOCK ENABLE MACROS FOR SYSCFG
#define SYSCFG_PCLK_EN()  (RCC->APB2ENR |= (1 << 14))

// GPIO Disable
#define GPIOA_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 8))
#define GPIOJ_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 9))
#define GPIOK_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 10))
// I2C Disable
#define I2C1_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 23))

// SPI Disable
#define SPI1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 15))

// UART/USART Disable
#define USART1_PCLK_DI()  (RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()  (RCC->APB2ENR &= ~(1 << 5))
//CLOCK ENABLE FOR THE DMAx Peripherals
#define DMA1_PCLK_DI()      (RCC->AHB1ENR &= ~(1<<21))
#define DMA2_PCLK_DI()      (RCC->AHB1ENR &= ~(1<<22))

#define USART1  			((USART_RegDef_t*)USART1_BASEADDR)
#define USART2  			((USART_RegDef_t*)USART2_BASEADDR)
#define USART3  			((USART_RegDef_t*)USART3_BASEADDR)
#define UART4  				((USART_RegDef_t*)UART4_BASEADDR)
#define UART5  				((USART_RegDef_t*)UART5_BASEADDR)
#define USART6  			((USART_RegDef_t*)USART6_BASEADDR)

#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET
#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW
#define FLAG_RESET   RESET
#define FLAG_SET     SET
typedef struct
{
	__vo uint32_t SR;         /*!< TODO,     										Address offset: 0x00 */
	__vo uint32_t DR;         /*!< TODO,     										Address offset: 0x04 */
	__vo uint32_t BRR;        /*!< TODO,     										Address offset: 0x08 */
	__vo uint32_t CR1;        /*!< TODO,     										Address offset: 0x0C */
	__vo uint32_t CR2;        /*!< TODO,     										Address offset: 0x10 */
	__vo uint32_t CR3;        /*!< TODO,     										Address offset: 0x14 */
	__vo uint32_t GTPR;       /*!< TODO,     										Address offset: 0x18 */
} USART_RegDef_t;

/*********************** RESETTING GPIOx PERIPHERALS **********************/
#define GPIOA_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 0));  (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 1));  (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 2));  (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 3));  (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 4));  (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 5));  (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 6));  (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 7));  (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)
#define GPIOI_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 8));  (RCC->AHB1RSTR &= ~(1 << 8)); }while(0)
#define GPIOJ_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 9));  (RCC->AHB1RSTR &= ~(1 << 9)); }while(0)
#define GPIOK_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 10)); (RCC->AHB1RSTR &= ~(1 << 10)); }while(0)
/***************RESETING DMAx Peripherals*************************/
#define DMA1_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 21)); (RCC->AHB1RSTR &= ~(1 << 21)); }while(0)
#define DMA2_REG_RESET()    do{ (RCC->AHB1RSTR |= (1 << 22)); (RCC->AHB1RSTR &= ~(1 << 22)); }while(0)
/*DMA_SxCR Register Bit Positions*/
#define DMA_SxCR_EN              (0U)   /* Stream enable */
#define DMA_SxCR_DMEIE           (1U)   /* Direct mode error interrupt enable */
#define DMA_SxCR_TEIE            (2U)   /* Transfer error interrupt enable */
#define DMA_SxCR_HTIE            (3U)   /* Half transfer interrupt enable */
#define DMA_SxCR_TCIE            (4U)   /* Transfer complete interrupt enable */
#define DMA_SxCR_PFCTRL          (5U)   /* Peripheral flow controller */
#define DMA_SxCR_DIR             (6U)   /* Data transfer direction [7:6] */
#define DMA_SxCR_CIRC            (8U)   /* Circular mode */
#define DMA_SxCR_PINC            (9U)   /* Peripheral increment mode */
#define DMA_SxCR_MINC            (10U)  /* Memory increment mode */
#define DMA_SxCR_PSIZE           (11U)  /* Peripheral data size [12:11] */
#define DMA_SxCR_MSIZE           (13U)  /* Memory data size [14:13] */
#define DMA_SxCR_PINCOS          (15U)  /* Peripheral increment offset size */
#define DMA_SxCR_PL              (16U)  /* Priority level [17:16] */
#define DMA_SxCR_DBM             (18U)  /* Double buffer mode */
#define DMA_SxCR_CT              (19U)  /* Current target (M0/M1) */
#define DMA_SxCR_PBURST          (21U)  /* Peripheral burst transfer [22:21] */
#define DMA_SxCR_MBURST          (23U)  /* Memory burst transfer [24:23] */
#define DMA_SxCR_CHSEL           (25U)  /* Channel selection [27:25] */

/*DMA_SxNDTR Register Bit Positions*/
#define DMA_SxNDTR_NDT           (0U)   /* Number of data items to transfer [15:0] */

/*DMA_SxFCR Register Bit Positions*/
#define DMA_SxFCR_FTH            (0U)   /* FIFO threshold selection [1:0] */
#define DMA_SxFCR_DMDIS          (2U)   /* Direct mode disable */
#define DMA_SxFCR_FS             (3U)   /* FIFO status [5:3] */
#define DMA_SxFCR_FEIE           (7U)   /* FIFO error interrupt enable */
#define DMA_LISR_FEIF0_Pos      (0U)
#define DMA_LISR_DMEIF0_Pos     (2U)
#define DMA_LISR_TEIF0_Pos      (3U)
#define DMA_LISR_HTIF0_Pos      (4U)
#define DMA_LISR_TCIF0_Pos      (5U)

#define DMA_LISR_FEIF1_Pos      (6U)
#define DMA_LISR_DMEIF1_Pos     (8U)
#define DMA_LISR_TEIF1_Pos      (9U)
#define DMA_LISR_HTIF1_Pos      (10U)
#define DMA_LISR_TCIF1_Pos      (11U)

#define DMA_LISR_FEIF2_Pos      (16U)
#define DMA_LISR_DMEIF2_Pos     (18U)
#define DMA_LISR_TEIF2_Pos      (19U)
#define DMA_LISR_HTIF2_Pos      (20U)
#define DMA_LISR_TCIF2_Pos      (21U)

#define DMA_LISR_FEIF3_Pos      (22U)
#define DMA_LISR_DMEIF3_Pos     (24U)
#define DMA_LISR_TEIF3_Pos      (25U)
#define DMA_LISR_HTIF3_Pos      (26U)
#define DMA_LISR_TCIF3_Pos      (27U)

/* DMA High Interrupt Status Register (DMA_HISR) bit positions */
#define DMA_HISR_FEIF4_Pos      (0U)
#define DMA_HISR_DMEIF4_Pos     (2U)
#define DMA_HISR_TEIF4_Pos      (3U)
#define DMA_HISR_HTIF4_Pos      (4U)
#define DMA_HISR_TCIF4_Pos      (5U)

#define DMA_HISR_FEIF5_Pos      (6U)
#define DMA_HISR_DMEIF5_Pos     (8U)
#define DMA_HISR_TEIF5_Pos      (9U)
#define DMA_HISR_HTIF5_Pos      (10U)
#define DMA_HISR_TCIF5_Pos      (11U)

#define DMA_HISR_FEIF6_Pos      (16U)
#define DMA_HISR_DMEIF6_Pos     (18U)
#define DMA_HISR_TEIF6_Pos      (19U)
#define DMA_HISR_HTIF6_Pos      (20U)
#define DMA_HISR_TCIF6_Pos      (21U)

#define DMA_HISR_FEIF7_Pos      (22U)
#define DMA_HISR_DMEIF7_Pos     (24U)
#define DMA_HISR_TEIF7_Pos      (25U)
#define DMA_HISR_HTIF7_Pos      (26U)
#define DMA_HISR_TCIF7_Pos      (27U)
#define GPIO_BASEADDR_TO_CODE(x)    ( (x == GPIOA)?0 :\
		                              (x == GPIOB)?1 :\
				                      (x == GPIOC)?2 :\
						              (x == GPIOD)?3  :\
								      (x == GPIOE)?4 :\
									  (x == GPIOF)?5 :\
									  (x == GPIOG)?6 :\
									  (x == GPIOH)?7 :\
									 (x == GPIOI)?8 :0)


#define IRQ_NO_EXTI0     6
#define IRQ_NO_EXTI1     7
#define IRQ_NO_EXTI2     8
#define IRQ_NO_EXTI3     9
#define IRQ_NO_EXTI4     10
#define IRQ_NO_EXTI9_5   23
#define IRQ_NO_EXTI5_10  40
#define IRQ_NO_SPI1      35
#define IRQ_NO_SPI2      36
#define IRQ_NO_SPI3      51
#define IRQ_NO_I2C1_EV   31
#define IRQ_NO_I2C1_ER   32
#define IRQ_NO_I2C2_EV   33
#define IRQ_NO_I2C2_ER   34
#define IRQ_NO_I2C3_EV   79
#define IRQ_NO_I2C3_ER   80
#define IRQ_NO_DMA1_S0   11U
#define IRQ_NO_DMA1_S1   12U
#define IRQ_NO_DMA1_S2   13U
#define IRQ_NO_DMA1_S3   14U
#define IRQ_NO_DMA1_S4   15U
#define IRQ_NO_DMA1_S5   16U
#define IRQ_NO_DMA1_S6   17U
#define IRQ_NO_DMA1_S7   47U
#define IRQ_N0_DMA2_S0   56U
#define IRQ_N0_DMA2_S1   57U
#define IRQ_N0_DMA2_S2   58U
#define IRQ_N0_DMA2_S3   59U
#define IRQ_N0_DMA2_S4   60U
#define IRQ_N0_DMA2_S5   68U
#define IRQ_N0_DMA2_S6   69U
#define IRQ_N0_DMA2_S7   70U

/*
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0  0
#define NVIC_IRQ_PRI1  1
#define NVIC_IRQ_PRI2  2
#define NVIC_IRQ_PRI3  3
#define NVIC_IRQ_PRI4  4
#define NVIC_IRQ_PRI5  5
#define NVIC_IRQ_PRI6  6
#define NVIC_IRQ_PRI7  7
#define NVIC_IRQ_PRI8  8
#define NVIC_IRQ_PRI9  9
#define NVIC_IRQ_PRI10 10
#define NVIC_IRQ_PRI11 11
#define NVIC_IRQ_PRI12 12
#define NVIC_IRQ_PRI13 13
#define NVIC_IRQ_PRI14 14
#define NVIC_IRQ_PRI15 15

/*
 * Bit position macros for SPI_CR1 register
 */
#define SPI_CR1_CPHA         0
#define SPI_CR1_CPOL         1
#define SPI_CR1_MSTR         2
#define SPI_CR1_BR           3  // Note: This is a 3-bit field (bits 3, 4, 5)
#define SPI_CR1_SPE          6
#define SPI_CR1_LSBFIRST     7
#define SPI_CR1_SSI          8
#define SPI_CR1_SSM          9
#define SPI_CR1_RXONLY       10
#define SPI_CR1_DFF          11
#define SPI_CR1_CRCNEXT      12
#define SPI_CR1_CRCEN        13
#define SPI_CR1_BIDIOE       14
#define SPI_CR1_BIDIMODE     15
/*
 * Bit position macros for SPI_CR2 register
 */
#define SPI_CR2_RXDMAEN      0   // Rx buffer DMA enable
#define SPI_CR2_TXDMAEN      1   // Tx buffer DMA enable
#define SPI_CR2_SSOE         2   // SS output enable
#define SPI_CR2_FRF          4   // Frame format
#define SPI_CR2_ERRIE        5   // Error interrupt enable
#define SPI_CR2_RXNEIE       6   // RX buffer not empty interrupt enable
#define SPI_CR2_TXEIE        7   // Tx buffer empty interrupt enable

/*
 * Bit position macros for SPI_SR (Status Register)
 */
#define SPI_SR_RXNE          0   // Receive buffer not empty
#define SPI_SR_TXE           1   // Transmit buffer empty
#define SPI_SR_CHSIDE        2   // Channel side
#define SPI_SR_UDR           3   // Underrun flag
#define SPI_SR_CRCERR        4   // CRC error flag
#define SPI_SR_MODF          5   // Mode fault
#define SPI_SR_OVR           6   // Overrun flag
#define SPI_SR_BSY           7   // Busy flag
#define SPI_SR_FRE           8   // TI frame format error


/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 					8
#define I2C_CR1_STOP  				 	9
#define I2C_CR1_ACK 				 	10
#define I2C_CR1_SWRST  				 	15
#define I2C_CR1_POS                     11
/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ				 	0
#define I2C_CR2_ITERREN				 	8
#define I2C_CR2_ITEVTEN				 	9
#define I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			 	15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15
/*
 * STATUS REGISTER USE
 */
#define I2C_SR1  1
#define I2C_SR2  2

/*************************reseting the spix register**********************/
#define SPI1_REG_RESET()   do { (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); } while(0)
#define SPI2_REG_RESET()   do { (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); } while(0)
#define SPI3_REG_RESET()   do { (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); } while(0)
/************************* Resetting the I2Cx registers **********************/
#define I2C1_REG_RESET()   do { (RCC->APB1RSTR |=  (1 << 21)); \
                                (RCC->APB1RSTR &= ~(1 << 21)); } while(0)

#define I2C2_REG_RESET()   do { (RCC->APB1RSTR |=  (1 << 22)); \
                                (RCC->APB1RSTR &= ~(1 << 22)); } while(0)

#define I2C3_REG_RESET()   do { (RCC->APB1RSTR |=  (1 << 23)); \
                                (RCC->APB1RSTR &= ~(1 << 23)); } while(0)

/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10
#define USART_CR3_ONEBIT   				11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS                    9


// USART/UART Reset Macros
#define USART1_REG_RESET()   do { (RCC->APB2RSTR |= (1 << 4));  (RCC->APB2RSTR &= ~(1 << 4)); } while(0)
#define USART2_REG_RESET()   do { (RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); } while(0)
#define USART3_REG_RESET()   do { (RCC->APB1RSTR |= (1 << 18)); (RCC->APB1RSTR &= ~(1 << 18)); } while(0)
#define UART4_REG_RESET()    do { (RCC->APB1RSTR |= (1 << 19)); (RCC->APB1RSTR &= ~(1 << 19)); } while(0)
#define UART5_REG_RESET()    do { (RCC->APB1RSTR |= (1 << 20)); (RCC->APB1RSTR &= ~(1 << 20)); } while(0)
#define USART6_REG_RESET()   do { (RCC->APB2RSTR |= (1 << 5));  (RCC->APB2RSTR &= ~(1 << 5)); } while(0)
// Standard AHB and APB Prescaler values defined by the STM32F407 Reference Manual
// Inside stm32f407xx.h
extern uint16_t AHB_PreScaler[8];
extern uint8_t APB1_PreScaler[4];

uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);
uint32_t RCC_GetPLLOutputClock(void);
//ERROR HANDLING MACROS
#define INIT_OK  1U
#define INIT_FAULT 0U
#include<stm32f4xx_gpio_driver.h>
//#include<stm32f4xx_I2C_driver.h>
#include<stm32f4xx_DMAx.h>




#endif /* INC_STM32F407XX_H_ */
