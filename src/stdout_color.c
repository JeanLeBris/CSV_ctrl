#include <stdio.h>
#include <stdlib.h>
#include "../lib/stdout_color.h"

void StdoutColorBlack(void){
    printf("\033[0;30m");
}
void StdoutColorRed(void){
    printf("\033[0;31m");
}
void StdoutColorGreen(void){
    printf("\033[0;32m");
}
void StdoutColorYellow(void){
    printf("\033[0;33m");
}
void StdoutColorBlue(void){
    printf("\033[0;34m");
}
void StdoutColorPurple(void){
    printf("\033[0;35m");
}
void StdoutColorCyan(void){
    printf("\033[0;36");
}
void StdoutColorWhite(void){
    printf("\033[0;37m");
}

void StdoutColorReset(void){
    printf("\033[0m");
}
