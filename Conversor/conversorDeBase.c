#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct no {
    int valor;
    struct no *prox;
};

struct lista {
    struct no *primeiro;
    struct no *fim;
    int tamanho;
};

void inicializarLista (struct lista *lista)
{
    lista->tamanho = 0;
    lista->primeiro = NULL;
    lista->fim = NULL;
}

void inserirNoInicio (struct lista *lista, int valor)
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

void inserirNoFim (struct lista *lista, int valor)
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
        novoNo->prox = NULL;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->tamanho++;
    }
}

char* getCharArray (struct lista *lista)
{
    char *charArray = malloc (lista->tamanho * sizeof(char));
    struct no *aux = lista->primeiro;
    int cont = 0;
    char *valorChar = malloc (4);
    strcpy(charArray, "");

    while (aux != NULL)
    {
        sprintf(valorChar, "%i", aux->valor);
        strcat(charArray, valorChar);
        aux = aux->prox;
        cont++;
    }

    free (valorChar);
    return charArray;
}

void removaChar (char *string, char carac)
{
    int i = 0;
    int j = 0;

    while (string[i])
    {
        if (string[i] != carac)
        {
            string[j++] = string[i];
        }

        i++;
    }

    string[j] = '\0';
}

char* converterParaBase (double valor, unsigned int baseConversao)
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

double converterParaDez (char valor [], unsigned int baseValor)
{
    double result = 0;
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

char* converterParaBaseFrac (double valor, unsigned int baseConversao)
{
    int parteInteira = (int) valor;
    double parteDecimal = valor - parteInteira;

    int quociente = parteInteira;
    int aux = 0;
    struct list *listaResto = malloc(4);
    inicializarLista(listaResto);
    struct list *listaDecimal = malloc(4);
    inicializarLista(listaDecimal);

    if (quociente == 0)
        inserirNoInicio(listaResto, 0);

    while (quociente != 0)
    {
        int resto = quociente % baseConversao;
        inserirNoInicio(listaResto, resto);
        quociente = (int) quociente / baseConversao;
    }

    while (aux < 1)
    {
        aux = parteDecimal * baseConversao;
        inserirNoFim(listaDecimal, aux);
        parteDecimal = parteDecimal - aux;
    }

    char *parteInteiraChar = getCharArray(listaResto);
    char *parteDecimalChar = getCharArray(listaDecimal);

    strcat(parteInteiraChar, ",");
    strcat(parteInteiraChar, parteDecimalChar);

    return parteInteiraChar;
}

double converterParaDezFrac (char valor[], unsigned int baseValor)
{
    char delim [] = ",";
    char *split = strtok(valor, delim);
    char aux [10];
    strcpy(aux, split);
    double parteInteira = converterParaDez(aux, baseValor);

    split = strtok(NULL, delim);

    double parteFrac = 0;
    char numerosDecimais [100];
    strcpy(numerosDecimais, split);
    int i = 0;
    int cont = -1;
    for (; i <= strlen(numerosDecimais) - 1; i++)
    {
        int digito = numerosDecimais[i] - '0';
        double potencia = pow (baseValor, cont);
        parteFrac += digito * potencia;
        cont--;
    }

    return parteInteira + parteFrac;
}

char* converter (char *valor, unsigned int baseValor, unsigned int baseConversao, char *result)
{
    if (strchr(valor, ','))
    {
        result = malloc (4);
        double valorNaDez = converterParaDezFrac(valor, baseValor);
        result = converterParaBaseFrac(valorNaDez, baseConversao);
        return result;
    }
    if (strchr(valor, '-') != NULL)
    {
        removaChar(valor, '-');
        result = malloc (4);
        strcpy(result, "-");
        double valorNaDez = converterParaDez(valor, baseValor);
        char *auxResult = malloc (4);
        strcpy(auxResult, "");
        auxResult = converterParaBase(valorNaDez, baseConversao);
        strcat(result, auxResult);
    }
    else
    {
        result = malloc (4);
        strcpy(result, " ");
        double valorNaDez = converterParaDez(valor, baseValor);
        result = converterParaBase(valorNaDez, baseConversao);
    }

    return result;
}

int main ()
{
    int continuar = 1;
    while (continuar != 0)
    {
        system("cls");
        char *res = malloc(1);
        char valor [1000];
        unsigned int baseValor;
        unsigned int baseConversao;
        printf ("Conversor de bases numericas\n");

        printf ("\nDigite o valor a ser convertido:\n");
        fflush(stdout);

        scanf("%s", valor);
        fflush(stdin);

        printf ("\nDigite a base do valor:\n");
        fflush(stdout);

        scanf("%u", &baseValor);
        fflush(stdin);

        printf ("\nDigite a base para a conversao:\n");
        fflush(stdout);

        scanf("%u", &baseConversao);
        fflush(stdin);

        char* result = converter(valor, baseValor, baseConversao, result);

        printf("\nR: Valor da conversao = %s", result);

        printf("\n\nDeseja encerrar o programa? Se sim, digite sim, senao, digite nao: ");
        fflush(stdout);
        scanf ("%s", res);
        fflush (stdin);

        if (strcmp(res, "sim") == 0)
            continuar = 0;

        free(res);
        free(result);
    }

    return 0;
}
