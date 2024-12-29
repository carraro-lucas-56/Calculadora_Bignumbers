#include "bignumber.h"

void soma(BigNumber A, BigNumber B) {
    
    int diff = A->tamanho - B->tamanho;
    int sum, carry = 0, i = A->tamanho;

    while(i-diff >= 0 || carry == 1){

        if(i-diff >= 0) {

            sum = A->digitos[i] + B->digitos[i-diff] + carry;
            
            //checagem de overflow
            if(sum >= 10) {
                sum -= 10;
                carry = 1;
            }
            else 
                carry = 0;
        }

        else {
            sum = A->digitos[i] + carry;
            
            //checagem de overflow
            if(sum >= 10) {
                sum -= 10;
                carry = 1;
            }
            else 
                carry = 0;
        }

        A->digitos[i] = sum;
        i--;
    }
}

void pegar_emprestado(char* digitos, int index) {

    while(digitos[index] == 0) { 
        digitos[index] = 9;
        index --;
    }

    digitos[index]--;
}

void subtracao(BigNumber A, BigNumber B) {

    int diff = A->tamanho - B->tamanho;
    int aux, i = A->tamanho;

    while(i-diff >= 0) {
    
        aux = A->digitos[i] - B->digitos[i-diff];
        
        if(aux < 0) {
            pegar_emprestado(A->digitos,i-1);
            aux += 10;
        }

        A->digitos[i] = aux;
        i--;
    }
}

void soma_n_vezes(BigNumber A, BigNumber B, int n) {

    //faz A + n*B

    int diff = A->tamanho - B->tamanho;
    int sum, carry = 0, i = A->tamanho;

    while(i-diff >= 0 || carry >= 1){

        if(i-diff >= 0) {

            sum = A->digitos[i] + n*B->digitos[i-diff] + carry;
            
            //checagem de overflow
            if(sum >= 10) {
                carry = sum/10;
                sum = sum%10;
            }
            else 
                carry = 0;
        }

        else {
            sum = A->digitos[i] + carry;
            
            //checagem de overflow
            if(sum >= 10) {
                carry = sum/10;
                sum = sum%10;
            }
            else 
                carry = 0;
        }

        A->digitos[i] = sum;
        i--;
    }
}

BigNumber multiplicacao(BigNumber A, BigNumber B) {

    BigNumber C;

    C = bignumber_zero(A->tamanho+B->tamanho);
    int aux = 0;

    //ajustando o sinal
    if(A->sinal == B->sinal)
        C->sinal = '+';
    else
        C->sinal = '-';

    for(int i = B->tamanho; i >= 1; i--) {

        if(B->digitos[i] == 0) {
            C->tamanho--;
            aux++;
            continue;
        }

        soma_n_vezes(C,A,B->digitos[i]);

        //note que mudar o tamanho de C antes das
        // somas  simula um shift  esquerdo em A.
        C->tamanho--;
        aux++;
    }

    C->tamanho += aux;
    return C;
}

void soma1(BigNumber A) {

    int i = A->tamanho;

    while(1) {

        if(A->digitos[i] < 9) {
            A->digitos[i]++;
            break;
        }
        else {
            A->digitos[i] = 0;
        }
        i--;
    }
}

BigNumber maior_div(BigNumber A, BigNumber B, int n) {

    /*
      'maior_div' é basicamente a função 
      'maior' um pouco  adapatada para o
      caso de não podermos  fazer uso do 
      tamanho  do  números  diretamente, 
      lembre  que  n guarda a posição do 
      dígito mais significativo de A. 
    */

    int i = 1, diff = A->tamanho-B->tamanho;

    //verificando indiretamente se A tem mais dígitos que B
    if(n <= diff)
        return A;

    //verificando indiretamente se A tem menos dígitos que B
    else if(n > diff+1)
        return B;

    //se chegamos até aqui A e B tem a mesma qte de dígitos
    while(1) {

        if(A->digitos[diff+i] > B->digitos[i])
            return A;

        else if(A->digitos[diff+i] < B->digitos[i])
            return B;
        
        i++;

        //caso em que os números são exatamente iguais
        if(i == B->tamanho+1)
            return A;
    }
}

BigNumber divisao(BigNumber A, BigNumber B) {

    BigNumber C = bignumber_zero(A->tamanho);

    if(maior(A,B) == B) 
        return C;
    
    //ajustando do sinal do resultado final
    if(A->sinal != B->sinal)
        C->sinal = '-';
    else
        C->sinal = '+';

    int aux , i = 1; //i guarda a posição do dígito mais significativo de A

    aux = B->tamanho;
    C->tamanho = C->tamanho - (A->tamanho-B->tamanho);
    left_shift(B,A->tamanho-B->tamanho);

    //esse laço é necessário para quando formos
    //utilizar a divisao durante  a potenciação
    while(A->digitos[i] == 0) {
        i++;
        if(i > A->tamanho)
            break;
    }

    while(1) {

        //removendo indiretamente o shift feito em B caso necessário
        while(B->tamanho > aux && maior_div(A,B,i) == B) {
            B->tamanho--;
            C->tamanho++;
        }

        if(maior_div(A,B,i) == B && B->tamanho == aux)
            break;

        subtracao(A,B);
        soma1(C);

        //atualizando a posição do dígito mais significativo
        while(A->digitos[i] == 0) {
            i++;
            if(i > A->tamanho)
                break;
        }
    }

    return C;
}

void sub1(BigNumber A) {

    int i = A->tamanho;

    if(A->digitos[i] > 0)
        A->digitos[i]--;
    else
        pegar_emprestado(A->digitos,i-1);
}

BigNumber potenciacao(BigNumber A, BigNumber B) {

    BigNumber C, D, E;
     
    if(eh_zero(B)) 
        return bignumber_n('1');

    else if(impar(B)){
        sub1(B);
        C = potenciacao(A,B);
        D = multiplicacao(A,C);
       
        free_bignumber(C);
        return D;
    }

    else {
        BigNumber DOIS = bignumber_n('2');
       
        C = divisao(B,DOIS);
        D = potenciacao(A,C);
        E = multiplicacao(D,D);

        free_bignumber(DOIS);
        free_bignumber(C);
        free_bignumber(D);
        return E;
    }
}
