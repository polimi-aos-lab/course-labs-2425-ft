
#include "registers.h"

//Minimal code that blinks an LED on an stm32f4-discovery board
//PD14: red led

void delay()
{
	volatile int i;
	for(i=0;i<1000000;i++) ;
}

int kernel_boot()
{
	// Here we should continue the boot of the kernel
	// but for simplicity this is a self-contained example
	// that just stops in an infinite loop and blinks an LED
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= 1<<28;
	for(;;)
	{
		GPIOD->BSRR=1<<14;
		delay();
		GPIOD->BSRR=1<<(14+16);
		delay();
	}
}
