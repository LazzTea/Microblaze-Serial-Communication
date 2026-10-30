#include <stdio.h>
#include <xil_printf.h>
#include <xgpio.h>
#include "xparameters.h"

int get_number() {
  char c = inbyte();
  outbyte(c);
	int digit = c - '0';
  

	while (c != '\r')
	{
    c = inbyte();
    if (c <= '0' || c >= '9') continue;
    outbyte(c);
		digit = digit * 10 + (c - '0');
	}

  return digit;
}

int main() {
  int a;
  int b;
  int c;
  XGpio gpio;
  uint32_t led;

  XGpio_Initialize(&gpio, 0);
  XGpio_SetDataDirection(&gpio, 2, 0x00000000); 

  while (1) {
    xil_printf("Please enter numbers in the form a/b. \n\r");
    a = get_number();    // Read first number
    outbyte('\n');
    outbyte('\r');
    b = get_number();    // Read second number

    c = a * b;

    xil_printf("\n\rOutput %d\n\r", c);

    if (c > 100) {
      led = 0xFFFFFFFF;
    } else {
      led = 0x00000000;
    }

    XGpio_DiscreteWrite(&gpio, 2, led);
  }
}