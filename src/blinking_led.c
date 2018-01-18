#include "msp430g2452.h"

#define LED    BIT0
#define LED2   BIT6
#define BUTTON BIT3

int main(void){
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR |= LED+LED2;
	P1REN |= BUTTON; // Enable resistors
	P1OUT |= BUTTON; // choose the pull-up resistor
	P1IES |= BUTTON; // trigger on falling edge (press button)
	P1IE  |= BUTTON; // mask interrupt only on this pin

	__enable_interrupt();
	unsigned int i;
	for(;;) {
		P1OUT ^= LED2;
		i = 10000;
		do{
			i--;
		} while (i > 0);
	}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	P1OUT ^= LED; // Toggle LED
	P1IFG &= ~BUTTON; // clear interrupt flag
}
