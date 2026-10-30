#include <stdio.h>
#include <xil_printf.h>
#include <xgpio.h>
#include "xparameters.h"

int get_digit() {
    char c = inbyte();  // Wait for and read a character
    outbyte(c);        // Echo it back to the serial monitor so you can see it
    return c - '0';    // Convert ASCII character to actual integer
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
  a = get_digit();    // Read first number
  inbyte();           // Skip the '/' character
  outbyte('/');       // Echo the '/' character
  b = get_digit();    // Read second number

  c = a * b;

  xil_printf("\nOutput %d\n", c);

  while (1) {
    if (c > 100) {
      led = 0xFFFFFFFF;
    } else {
      led = 0x00000000;
    }

    XGpio_DiscreteWrite(&gpio, 2, led);
  }
}