//
// Created by ncc on 06/01/2023.
//
#include "stdio.h"
#ifndef CB17_NCCCOLOR_H
#define CB17_NCCCOLOR_H


void nccRed(){
    printf("\033[1;31m");
}


void nccYellow(){
    printf("\033[1;33m");

}

void nccReset(){

    printf("\033[0m");

}

void nccGreen(){


    printf("\033[0;32m");
}

void nccBlack(){

    printf("\033[0;30m");
}
void nccBlue(){
    printf("\033[0;34m");
}

void nccPurple(){

    printf("\033[0;35m");
}

void nccCyan(){
    printf("\033[0;36m");
}

void nccWhite(){
    printf("\033[0;37m");
}
#endif //CB17_NCCCOLOR_H
