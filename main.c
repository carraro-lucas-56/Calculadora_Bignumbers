#include "operations.h"

void faz_operacao(BigNumber A, BigNumber B, char op) {

    //Em algumas operações é conveniente que A aponte para o maior número 
    if(op != '/' && op != '^' && op != '%') {

        if(maior(A,B) == B) {
            swap_bignumbers(&A,&B);

            // no caso da subtracao é necessário fazer alguns ajustes após o swap
            if(op == '-') {
                inverter_sinal(A);
                op = '+';
            }
        }
    }

    if(op == '+') {

        if(A->sinal == B->sinal)
            soma(A,B);
        else 
            subtracao(A,B);
        print_bignumber(A);
    }

    else if(op == '-'){

        if(A->sinal == B->sinal)
            subtracao(A,B);
        else
            soma(A,B);
        print_bignumber(A);
    }

    else if (op == '*') {

        BigNumber C = multiplicacao(A,B);
        print_bignumber(C);
        free_bignumber(C);
    }

    else if(op == '/') {

        BigNumber C = divisao(A,B);
        print_bignumber(C);
        free_bignumber(C);
    }

    else if(op == '^') {

        BigNumber C = potenciacao(A,B);
        print_bignumber(C);
        free_bignumber(C);
    }

    else if(op == '%') {
        divisao(A,B);
        print_bignumber(A);
    }

    else
        printf("Operação inválida!");
} 

int main() {

    char inicio, operacao;

    while((inicio = getchar()) != EOF) {
    
        BigNumber A = le_bignumber(inicio);
        BigNumber B = le_bignumber(getchar());

        operacao = getchar();
        getchar();

        faz_operacao(A,B,operacao);

        free_bignumber(A);  
        free_bignumber(B);
    }

    return 0;
}