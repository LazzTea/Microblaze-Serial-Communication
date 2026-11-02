#include <stdio.h>
#include <xil_printf.h>
#include <xgpio.h>
#include "xparameters.h"

#include "PmodKYPD.h"
#include "sleep.h"
#include "xil_cache.h"

void KYPD_Initialize();
void KYPD_Cleanup();
void DisableCaches();
void EnableCaches();
void DemoSleep(u32 millis);

PmodKYPD myDevice;


// keytable is determined as follows (indices shown in Keypad position below)
// 12 13 14 15
// 8  9  10 11
// 4  5  6  7
// 0  1  2  3
#define DEFAULT_KEYTABLE "0FED789C456B123A"

void KYPD_Initialize() {
   EnableCaches();
   KYPD_begin(&myDevice, XPAR_PMODKYPD_0_AXI_LITE_GPIO_BASEADDR);
   KYPD_loadKeyTable(&myDevice, (u8*) DEFAULT_KEYTABLE);
}

int get_number() {
  char c = inbyte();
  outbyte(c);
	int digit = c - '0';

  return digit;
}

int main() {
  int playerPC;
  int playerFPGA;

  // Initialize Keyboard
  u16 keystate;
  XStatus status, last_status = KYPD_NO_KEY;
  u8 key, last_key = 'x';

  // Initialize GPIO
  XGpio gpio;
  uint32_t led;

  XGpio_Initialize(&gpio, 0);
  XGpio_SetDataDirection(&gpio, 2, 0x00000000); 
  KYPD_Initialize();

  // Connect Keyboard to GPIO
  Xil_Out32(myDevice.GPIO_addr, 0xF);

  xil_printf("Player 1 Pick your reponse by number Rock (1), Paper (2), Scissors (3). \n\r");
  playerPC = get_number();

  // Get Button Press on keypad
  keystate = KYPD_getKeyStates(&myDevice);
  status = KYPD_getKeyPressed(&myDevice, keystate, &key);

  // Print key detect if a new key is pressed or if status has changed
  if (status == KYPD_SINGLE_KEY && (status != last_status || key != last_key)) {
    xil_printf("Key Pressed on Keypard: %c\r\n", (char) key);
    playerFPGA = key;
    last_key = key;
  } else if (status == KYPD_MULTI_KEY && status != last_status) {
    xil_printf("Error: Multiple keys pressed\r\n");
    continue;
  }

  last_status = status;

  switch(playerPC) {
    case 0: 
      switch(playerFPGA) {
        case 0: xil_printf("It's a tie, rock = rock"); break;
        case 1: xil_printf("FPGA won!, paper > rock"); break;
        case 2: xil_printf("PC won!, scissors < rock"); break;
        default: xil_printf("Error Invalid Input");
      }
      break;

    case 1:
      switch(playerFPGA) {
        case 0: xil_printf("PC won! rock < paper"); break;
        case 1: xil_printf("It's a tie, paper = paper"); break;
        case 2: xil_printf("FPGA won!, scissors > paper"); break;
        default: xil_printf("Error Invalid Input");
      }
      break;

    case 2:
      switch(playerFPGA) {
        case 0: xil_printf("FPGA won!, rock > scissors"); break;
        case 1: xil_printf("PC won!, paper < scissors"); break;
        case 2: xil_printf("It's a tie, scissors = scissors"); break;
        default: xil_printf("Error Invalid Input");
      }
      break;

    default:
      xil_printf("Error Invalid Input");
  }

  KYPD_Cleanup();
  return 0;
}


void KYPD_Cleanup() {
  DisableCaches();
}

void EnableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheEnable();
#endif
#endif
}

void DisableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheDisable();
#endif
#endif
}
