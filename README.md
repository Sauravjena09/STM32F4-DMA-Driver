
# STM32F4 Bare-Metal DMA Driver

## Overview

This repository contains a custom bare-metal Direct Memory Access (DMA) driver written for the STM32F4 series (specifically tested on the STM32F407G). It is designed to handle high-speed, continuous data transfers for a wide range of embedded applications, facilitating efficient communication between standard hardware peripherals (such as ADCs, SPI, USART, or timers) and system memory.

## What is DMA?

Direct Memory Access (DMA) is a hardware subsystem that transfers data between peripherals and memory (or from memory to memory) without involving the CPU. By offloading these repetitive data-moving tasks, the CPU is free to execute other instructions. This is critical for preventing bottlenecks and maintaining system responsiveness during heavy data payloads, such as handling continuous sensor data or high-speed communication protocols.

## About the Code

This driver provides a direct hardware abstraction for the STM32F4 dual-DMA controller matrix. It was written from scratch to avoid the bloat of standard HAL libraries while strictly enforcing the architectural constraints defined in the ST RM0090 reference manual.

Key features and safety checks include:

* **Strict Burst Alignment Validation:** Mathematical validation for memory and peripheral burst sizes against `MSIZE` and `PSIZE` to prevent silent bus faults.
* **NDTR Modulo Enforcement:** Prevents erratic hardware behavior by ensuring `NDTR` aligns perfectly with burst beat counts.
* **Transfer Modes:** Full configuration support for Normal, Circular, and Double Buffer Mode (DBM) continuous flows.
* **Direction Handling:** Complete routing for Memory-to-Peripheral (M2P), Peripheral-to-Memory (P2M), and Memory-to-Memory (M2M) transfers.
* **Optimized IRQ Handling:** Direct register-level manipulation for `LISR`/`HISR` flags using modulo-based stream offsets.

## File Location

The core driver files are contained entirely within the `drivers/` directory:

* `drivers/stm32f4xx_DMAx.c` — Main source file containing the initialization logic, stream setup, and interrupt handlers.
* `drivers/stm32f4xx_DMAx.h` — Header file containing register definitions, configuration structures, and function prototypes.

## Author

Saurav Ashutosh Jena
