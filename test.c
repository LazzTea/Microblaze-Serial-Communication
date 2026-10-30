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

#include <stdio.h>
#include <xil_printf.h>
#include <xgpio.h>
#include "xparameters.h"

int main() {
  int playerPC;
  int playerFPGA;

  XGpio gpio;
  uint32_t led;

  XGpio_Initialize(&gpio, 0);
  XGpio_SetDataDirection(&gpio, 2, 0x00000000); 

  xil_printf("Player 1 Pick your reponse by number Rock (1), Paper (2), Scissors (3). \n\r");
  scanf("%d", &playerPC);

  switch(playerPC) {
    case 0: 
      switch(playerFPGA) {
        case 0: xil_printf("It's a tie, rock = rock"); break;
        case 1: xil_printf("FPGA won!, paper > rock"); break;
        case 2: xil_printf("PC won!, scissors < rock"); break;
      }
      break;

    case 1:
      switch(playerFPGA) {
        case 0: xil_printf("PC won! rock < paper"); break;
        case 1: xil_printf("It's a tie, paper = paper"); break;
        case 2: xil_printf("FPGA won!, scissors > paper"); break;
      }
      break;

    case 2:
      switch(playerFPGA) {
        case 0: xil_printf("FPGA won!, rock > scissors"); break;
        case 1: xil_printf("PC won!, paper < scissors"); break;
        case 2: xil_printf("It's a tie, scissors = scissors"); break;
      }
      break;

    default:
      xil_printf("Error Invalid Input");
  }
}