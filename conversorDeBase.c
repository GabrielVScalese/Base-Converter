#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct no {
    int valor;
    struct no *prox;
};

struct list {
    struct no *primeiro;
    struct no *fim;
    int tamanho;
};

void inicializarLista (struct list *lista)
{
    lista->tamanho = 0;
    lista->primeiro = NULL;
    lista->fim = NULL;
}

void inserirNoInicio (struct list *lista, int valor)
{
    struct no *novoNo = malloc(4);
    novoNo->valor = valor;
    if (lista->primeiro == NULL)
    {
        novoNo->prox = NULL;
        lista->primeiro = novoNo;
        lista->fim = lista->primeiro;
        lista->tamanho++;
    }
    else
    {
        novoNo->prox = lista->primeiro;
        lista->primeiro = novoNo;
        lista->tamanho++;
    }
}

char* getCharArray (struct list *lista)
{
    char *charArray = malloc (lista->tamanho * sizeof(char));
    struct no *aux = lista->primeiro;
    int cont = 0;
    while (aux != NULL)
    {
        char valorChar [1];
        sprintf(valorChar, "%i", aux->valor);
        charArray[cont] = valorChar[0];
        aux = aux->prox;
        cont++;
    }

    return charArray;
}

char* converterParaBase (int valor, int baseConversao)
{
    int quociente = valor;
    int result;
    struct list *lista = malloc(4);
    inicializarLista(lista);

    while (quociente != 0)
    {
        int resto = quociente % baseConversao;
        inserirNoInicio(lista, resto);
        quociente = (int) quociente / baseConversao;
    }

    return getCharArray(lista);
}

int converterParaDez (char valor [], int baseValor)
{
    double result;
    int i = strlen(valor) - 1;
    int cont = 0;

    for (; i >= 0 ; i--)
    {
        int digito = valor[i] - '0';
        double potencia = pow (baseValor, cont);
        result += digito * potencia;
        cont++;
    }

    return result;
}

char* converter (char *valor, int baseValor, int baseConversao)
{
    char *result = malloc (4);
    int auxResult;
    auxResult = converterParaDez(valor, baseValor);
    if (baseConversao != 10)
        result = converterParaBase(auxResult, baseConversao);
    else
        sprintf(result, "%i", auxResult);

    return result;
}

int main ()
{
    char valor [1000];
    int baseValor;
    int baseConversao;
    printf ("Conversor de bases numericas\n");

    printf ("\nDigite o valor a ser convertido:\n");
    fflush(stdout);

    scanf("%s", valor);
    fflush(stdin);

    printf ("\nDigite a base do valor:\n");
    fflush(stdout);

    scanf("%i", &baseValor);
    fflush(stdin);

    printf ("\nDigite a base para a conversao:\n");
    fflush(stdout);

    scanf("%i", &baseConversao);
    fflush(stdin);

    char* result = converter(valor, baseValor, baseConversao);

    printf("\nR: Valor da conversao = %s", result);

    return 0;
}
