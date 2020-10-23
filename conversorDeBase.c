#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct no {
    char *valor;
    struct no *prox;
};

struct lista {
    struct no *primeiro;
    struct no *fim;
    unsigned int tamanho;
};

void inicializarLista (struct lista *lista)
{
    lista->tamanho = 0;
    lista->primeiro = NULL;
    lista->fim = NULL;
}

void inserirNoInicio (struct lista *lista, char* valor)
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

void inserirNoFim (struct lista *lista, char* valor)
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
    unsigned int cont = 0;
    strcpy(charArray, "");

    while (aux != NULL)
    {
        char *auxChar = aux->valor;
        strcat(charArray, aux->valor);
        aux = aux->prox;
        cont++;
    }

    free(lista);
    return charArray;
}

void removaChar (char *string, char carac)
{
    unsigned int i = 0, j = 0;

    while (string[i])
    {
        if (string[i] != carac)
            string[j++] = string[i];

        i++;
    }

    string[j] = '\0';
}

char* getLetra (int valor)
{
    char alfabeto [26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    return alfabeto[valor - 10];
}

unsigned int getValor (char letra)
{
   char alfabeto [26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   
   unsigned int i = 0;
   for (; i < 26; i++)
        if (alfabeto[i] == toupper(letra))
            return i + 10;
}

double converterParaDez (char valor [], unsigned int baseValor)
{
    double result = 0;
    int i = strlen(valor) - 1;
    unsigned int cont = 0;

    for (; i >= 0 ; i--)
    {
        if (isalpha(valor[i]))
        {
            unsigned int digito = getValor(valor[i]);
            double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
        else
        {
            unsigned int digito = valor[i] - '0';
            double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
    }

    return result;
}

int isInteger (double valor)
{
    int valorInteiro = (int) valor;
    return (valor == valorInteiro);
}

char* converterParaBaseFrac (double valor, unsigned int baseConversao)
{
    unsigned int quociente = (unsigned int) valor; // Obtem a parte inteira do valor
    double parteDecimal = valor - quociente;
    unsigned int aux = 0;
    unsigned int numeroCasas = 0;

    struct lista *listaResto = malloc(4);
    inicializarLista(listaResto);
    struct lista *listaDecimal = malloc(4);
    inicializarLista(listaDecimal);

    if (quociente == 0)
        inserirNoInicio(listaResto, "0");

    while (quociente != 0)
    {
        unsigned int resto = quociente % baseConversao;
        char *restoChar = malloc (4);
       
        if (resto > 9)
            *restoChar = getLetra (resto);
        else
            sprintf(restoChar, "%i", resto);
        
        inserirNoInicio(listaResto, restoChar);
        quociente = (int) quociente / baseConversao;
    }

    if (parteDecimal != 0)
        while (numeroCasas < 11)
        {
            double produto = parteDecimal * baseConversao;
            aux = produto;
            parteDecimal = produto;
            char *auxChar = malloc (4);
            
            if (aux > 9)
                *auxChar = getLetra (aux);
            else
                sprintf(auxChar, "%i", aux);
            
            inserirNoFim(listaDecimal, auxChar);

            if (isInteger(parteDecimal))
                break;

            if (aux >= 1)
                parteDecimal = parteDecimal - aux;

            numeroCasas++;
        }
    else
        inserirNoFim(listaDecimal, "0");

    char *parteInteiraChar = getCharArray(listaResto);
    char *parteDecimalChar = getCharArray(listaDecimal);

    strcat(parteInteiraChar, ",");
    strcat(parteInteiraChar, parteDecimalChar);

    return parteInteiraChar;
}

double converterParaDezFrac (char valor[], unsigned int baseValor)
{
    char delim [] = ",";
    char *split = strtok(valor, delim); // Obtem parte inteira do valor
    double parteInteira = converterParaDez(split, baseValor);

    split = strtok(NULL, delim); // Obtem parte decimal do valor

    double parteFrac = 0;
    unsigned int i = 0;
    int cont = -1;

    for (; i <= strlen(split) - 1; i++)
    {
        if (isalpha(split[i]))
        {
            unsigned int digito = getValor (split[i]);
            double potencia = pow (baseValor, cont);
            parteFrac += digito * potencia;
            cont--;
        }
        else
        {
            unsigned int digito = split[i] - '0';
            double potencia = pow (baseValor, cont);
            parteFrac += digito * potencia;
            cont--;
        }
    }

    return parteInteira + parteFrac;
}

char* converter (char *valor, unsigned int baseValor, unsigned int baseConversao, char *result)
{
    result = malloc (4);

    if (strchr(valor, ',') == NULL)
        strcat(valor, ",0");

    if (strchr(valor, '-') != NULL)
    {
        removaChar(valor, '-');
        strcpy(result, "-");
        double valorNaDez = converterParaDezFrac(valor, baseValor);
        char *valorNaBase = converterParaBaseFrac (valorNaDez, baseConversao);
        strcat(result, valorNaBase);
    }
    else
    {
        double valorNaDez = converterParaDezFrac(valor, baseValor);
        result = converterParaBaseFrac (valorNaDez, baseConversao);
    }

    return result;
}

int main ()
{
    unsigned int continuar = 1;
    while (continuar != 0)
    {
        system("cls");
        char *res = malloc (4);
        char valor [100];
        char valorClone [100];
        unsigned int baseValor, baseConversao;
        printf ("Conversor de bases numericas\n");

        printf ("\nDigite o valor a ser convertido:\n");
        fflush(stdout);

        scanf("%s", &valor);
        fflush(stdin);
        strcpy(valorClone, valor);

        printf ("\nDigite a base do valor a ser convertido:\n");
        fflush(stdout);

        scanf("%u", &baseValor);
        fflush(stdin);

        printf ("\nDigite a base para a conversao:\n");
        fflush(stdout);

        scanf("%u", &baseConversao);
        fflush(stdin);

        char* result = converter(valor, baseValor, baseConversao, result);

        printf("\nR: %s (base %i) ~= %s (base %i)\n", valorClone, baseValor, result, baseConversao);

        resposta: printf("\n\nDeseja encerrar o programa? (sim / nao) ");
        fflush(stdout);
        scanf ("%s", res);
        fflush (stdin);

        if (strcmp(res, "sim") == 0)
            continuar = 0;
        else
            if (strcmp(res, "nao") != 0)
            {
                printf("\nVoce deve digitar sim ou nao!");
                fflush(stdout);
                goto resposta;
            }

        free(res);
        free(result);
    }

    return 0;
}