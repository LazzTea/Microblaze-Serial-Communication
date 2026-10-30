#include <stdio.h>
#include <xil_printf.h>
#include <xgpio.h>
#include "xparameters.h"

int get_number() {
    char c = inbyte();  // Wait for and read a character
	int digit = c - '0';
    outbyte(c);        // Echo it back to the serial monitor so you can see it
	while (c != '\r')  // Wait until Enter key is pressed
	{
        c = inbyte();
        outbyte(c);    // Echo each character until Enter is pressed
		digit = digit * 10 + (c - '0');
	}
    return digit;    // Convert ASCII character to actual integer
}

int main() {
  int a;
  int b;
  int c;
  XGpio gpio;
  uint32_t led;

  XGpio_Initialize(&gpio, 0);
  XGpio_SetDataDirection(&gpio, 2, 0x00000000); 

  xil_printf("Please enter numbers in the form a/b. \n\r");
  a = get_number();    // Read first number
  outbyte('/');       // Echo the '/' character
  b = get_number();    // Read second number

  c = a * b;

  xil_printf("\n\rOutput %d\n\r", c);

  while (1) {
    if (c > 100) {
      led = 0xFFFFFFFF;
    } else {
      led = 0x00000000;
    }

    XGpio_DiscreteWrite(&gpio, 2, led);
  }
}