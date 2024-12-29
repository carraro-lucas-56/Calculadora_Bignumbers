#include "bignumber.h"

void* MALLOC(size_t tamanho) {
    
    // Aloca memória
    void* ponteiro = malloc(tamanho);
    
    // Verifica se a alocação foi bem-sucedida
    if (ponteiro == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    
    return ponteiro;
}

void print_bignumber(BigNumber A) {

    int i = 0;

    if(A->sinal == '-')
        printf("%c", A->sinal);

    //ignorando zeros a esquerda
    while(A->digitos[i] == 0) { 
        
        if(i == A->tamanho) {
            printf("%c\n", '0');
            return;
        }
        i++;        
    }

    //imprimindo os dígitos
    for(int j = i; j <= A->tamanho; j++)  
        printf("%d", A->digitos[j]);

    printf("\n");
}

char remover_zeros_esq() {

    // essa função devolve primeiro caractere do
    // buffer que for diferente de zero

    char c;
    while((c = getchar()) == '0')
        ;

    return c;
}

BigNumber le_bignumber(char inicio) {

    int mem = 10000; // variável que guarda a qte de memória alocada para os digitos

    BigNumber A = malloc(sizeof(struct bignumber));
    A->digitos = malloc(mem*sizeof(char));
    A->digitos[0] = CHAR_TO_DIGIT('0'); //posição reservada para caso de overflow
    
    //tamanho  vai  guardar em  que posicao  do vetor está o  último  dígito 
    //e não necessarimente isso será igual a qte de dígitos após realizarmos
    //operações com o número
    A->tamanho = 0;

    char aux = inicio;

    // se o primerio caractere lido não for '-', o número é positivo
    if(inicio == '-') { 
        A->sinal = '-';
        aux = remover_zeros_esq();
    }
    else {
        A->sinal = '+';
        if(inicio != '0') {
            A->digitos[1] = CHAR_TO_DIGIT(inicio);
            A->tamanho++;
            aux = getchar();
        }
        else
            aux = remover_zeros_esq();
    }

    //lendo os digitos
    if(aux != '\n') {
    
        do {
            if(A->tamanho+1 == mem) {

                //dobramos a qte de memória alocada sempre que ficarmos sem espaço
                A->digitos = realloc(A->digitos, (mem*2)*sizeof(char));
                mem = mem*2;
            }

            A->tamanho++;
            A->digitos[A->tamanho] = CHAR_TO_DIGIT(aux);

        } while((aux = getchar()) != '\n');   
    }

    //Caso em que o número é o próprio zero
    if(A->tamanho == 0) {
        A->digitos[1] = 0;
        A->tamanho++;
    }

    return A;
}

void free_bignumber(BigNumber A) {

    free(A->digitos);
    free(A);
}

void swap_bignumbers(BigNumber* A, BigNumber* B) {

    BigNumber aux;
    aux = *A;
    *A = *B;
    *B = aux;
}

BigNumber maior(BigNumber A, BigNumber B) {
    
    //função que retorna o número com maior MÓDULO

    if (A->tamanho > B->tamanho) 
        return A;

    else if(B->tamanho > A->tamanho)
        return B;

    // como os tamanhos são iguais, precisamos verificar os digitos
    
    for(int i = 1; i <= A->tamanho; i++) {

        if(A->digitos[i] > B->digitos[i])
            return A;

        else if (B->digitos[i] > A->digitos[i])
            return B;         
    }

    // números são exatamente iguais
    return A;
}

BigNumber bignumber_zero(int n) {

    //cria um binumber contendo n+1 zeros

    BigNumber A = malloc(sizeof(struct bignumber));
    A->digitos = calloc(n+1,sizeof(char));
    A->tamanho = n;
    A->sinal = '+';
    return A;
}

void left_shift(BigNumber A, int n) {

    if(n <= 0)
        return;

    char* novo = calloc(A->tamanho+n+1,sizeof(char));
    
    for(int i = A->tamanho; i >= 0; i--)
        novo[i] = A->digitos[i];

    free(A->digitos);
    A->digitos = novo;
    A->tamanho += n;
}

void inverter_sinal(BigNumber A) {

    if(A->sinal == '+')
        A->sinal = '-';
    else
        A->sinal = '+';
}

bool par(BigNumber A) {

    if(A->digitos[A->tamanho] % 2 == 0)
        return TRUE;
    else
        return FALSE;
}

bool impar(BigNumber A) {

    if(par(A))
        return FALSE;
    else
        return TRUE;
}

BigNumber bignumber_n(char n) {

    BigNumber C = malloc(sizeof(struct bignumber));
    C->digitos = calloc(2,sizeof(char));
    C->digitos[1] = CHAR_TO_DIGIT(n);
    C->sinal = '+';
    C->tamanho = 1;

    return C;
}

bool eh_zero(BigNumber A){

    int i = 1;

    while(A->digitos[i] == 0){ 
        i++;
        if(i > A->tamanho)
            break;
    }
    
    if(i == A->tamanho+1)
        return TRUE;
    else
        return FALSE;
}