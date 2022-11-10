#include <stdint.h>
#include <stdio.h>
#include "UART.h"
//jeljel
// Print a character to UART.
int fputc(int ch, FILE *f){
  if((ch == LF) || (ch == CR)){
    UART_OutChar(CR);
    UART_OutChar(LF);
    return 1;
  }
  UART_OutChar(ch);
  return 1;
}
// Get input from UART with echo
int fgetc (FILE *f){
  char ch = UART_InChar();  // receive from keyboard
  UART_OutChar(ch);            // echo
  return ((int) ch);
}
// Function called when file error occurs.
int ferror(FILE *f){
  /* Your implementation of ferror */
  return EOF;
}

