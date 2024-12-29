#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <stdio.h>
#include <stdlib.h>
#define CHAR_TO_DIGIT(c) ((int)c - 48)
#define bool int
#define TRUE 1
#define FALSE 0

typedef struct bignumber {
    char sinal;
    char* digitos;
    int tamanho; 
}* BigNumber;

void swap_bignumbers(BigNumber* A, BigNumber* B);

BigNumber bignumber_zero(int n);

void print_bignumber(BigNumber A);

BigNumber le_bignumber(char inicio);

void free_bignumber(BigNumber A);

void left_shift(BigNumber A, int n);

bool impar(BigNumber A);

bool par(BigNumber A);

BigNumber bignumber_n(char n);

BigNumber maior(BigNumber A, BigNumber B);

bool eh_zero(BigNumber A);

void inverter_sinal(BigNumber A);

#endif