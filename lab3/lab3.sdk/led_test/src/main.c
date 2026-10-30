#include <stdio.h>
#include <xil_printf.h>
#include <xgpio.h>
#include "xparameters.h"

int main() {
  int a;
  int b;
  int c;
  XGpio gpio;
  uint32_t led;

  XGpio_Initialize(&gpio, 0);
  XGpio_SetDataDirection(&gpio, 2, 0x00000000); 

  xil_printf("Please enter numbers in the form a/b. \n\r");
  scanf("%d/%d", &a, &b);

  c = a * b;

  xil_printf("Output %d", c);

  while (1) {
    if (c > 100) {
      led = 0xFFFFFFFF;
    } else {
      led = 0x00000000;
    }

    XGpio_DiscreteWrite(&gpio, 2, led);
  }
}