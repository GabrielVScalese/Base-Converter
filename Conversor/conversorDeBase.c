#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
    int i = 0, j = 0;

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
    if (valor == 10)
        return 'A';

    if (valor == 11)
        return 'B';

    if (valor == 12)
        return 'C';

    if (valor == 13)
        return 'D';

    if (valor == 14)
        return 'E';

    if (valor == 15)
        return 'F';

    if (valor == 16)
        return 'G';

    if (valor == 17)
        return 'H';

    if (valor == 18)
        return 'I';

    if (valor == 19)
        return 'J';

    if (valor == 20)
        return 'K';

    if (valor == 21)
        return 'L';

    if (valor == 22)
        return 'M';

    if (valor == 23)
        return 'N';

    if (valor == 24)
        return 'O';

    if (valor == 25)
        return 'P';

    if (valor == 26)
        return 'Q';

    if (valor == 27)
        return 'R';

    if (valor == 28)
        return 'S';

    if (valor == 29)
        return 'T';

    if (valor == 30)
        return 'U';

    if (valor == 31)
        return 'V';

    if (valor == 32)
        return 'W';

    if (valor == 33)
        return 'X';

    if (valor == 34)
        return 'Y';

    if (valor == 35)
        return 'Z';
}

int getValor (char *letra)
{
    if (toupper(letra) == 'A')
        return 10;

    if (toupper(letra) == 'B')
        return 11;

    if (toupper(letra) == 'C')
        return 12;

    if (toupper(letra) == 'D')
        return 13;

    if (toupper(letra) == 'E')
        return 14;

    if (toupper(letra) == 'F')
        return 15;

    if (toupper(letra) == 'G')
        return 16;

    if (toupper(letra) == 'H')
        return 17;

    if (toupper(letra) == 'I')
        return 18;

    if (toupper(letra) == 'J')
        return 19;

    if (toupper(letra) == 'K')
        return 20;

    if (toupper(letra) == 'L')
        return 21;

    if (toupper(letra) == 'M')
        return 22;

    if (toupper(letra) == 'N')
        return 23;

    if (toupper(letra) == 'O')
        return 24;

    if (toupper(letra) == 'P')
        return 25;

    if (toupper(letra) == 'Q')
        return 26;

    if (toupper(letra) == 'R')
        return 27;

    if (toupper(letra) == 'S')
        return 28;

    if (toupper(letra) == 'T')
        return 29;

    if (toupper(letra) == 'U')
        return 30;

    if (toupper(letra) == 'V')
        return 31;

    if (toupper(letra) == 'W')
        return 32;

    if (toupper(letra) == 'X')
        return 33;

    if (toupper(letra) == 'Y')
        return 34;

    if (toupper(letra) == 'Z')
        return 35;
}

double converterParaDez (char valor [], unsigned int baseValor)
{
    double result = 0;
    int i = strlen(valor) - 1;
    int cont = 0;

    for (; i >= 0 ; i--)
    {
        if (isalpha(valor[i]))
        {
            int digito = getValor(valor[i]);
            double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
        else
        {
            int digito = valor[i] - '0';
            double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
    }

    return result;
}

int isInteger(double val)
{
    int truncated = (int)val;
    return (val == truncated);
}

char* converterParaBaseFrac (double valor, unsigned int baseConversao)
{
    unsigned int quociente = (unsigned int) valor; // Obtem a parte inteira do valor
    double parteDecimal = valor - quociente;
    unsigned int aux = 0;
    unsigned int numeroCasas = 0;

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

    if (parteDecimal != 0)
        while (numeroCasas < 11)
        {
            double produto;
            produto = parteDecimal * baseConversao;
            aux = parteDecimal * baseConversao;
            parteDecimal = produto;
            inserirNoFim(listaDecimal, aux);

            if (isInteger(parteDecimal))
                break;

            if (aux >= 1)
                parteDecimal = parteDecimal - aux;

            numeroCasas++;
        }
    else
        inserirNoFim(listaDecimal, 0);

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
    char aux [10];
    strcpy(aux, split);
    double parteInteira = converterParaDez(aux, baseValor);

    split = strtok(NULL, delim); // Obtem parte decimal do valor

    double parteFrac = 0;
    char numerosDecimais [100];
    strcpy(numerosDecimais, split);
    int i = 0;
    int cont = -1;

    for (; i <= strlen(numerosDecimais) - 1; i++)
    {
        if (isalpha(numerosDecimais[i]))
        {
            int digito = getValor (numerosDecimais[i]);
            double potencia = pow (baseValor, cont);
            parteFrac += digito * potencia;
            cont--;
        }
        else
        {
            int digito = numerosDecimais[i] - '0';
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
        char *auxResult = converterParaBaseFrac (valorNaDez, baseConversao);
        strcat(result, auxResult);
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
    //unsigned int continuar = 1;
    //while (continuar != 0)
    //{
        system("cls");
        char *res = malloc(1);
        char valor [1000];
        char valorClone [1000];
        unsigned int baseValor, baseConversao;
        printf ("Conversor de bases numericas\n");

        printf ("\nDigite o valor a ser convertido:\n");
        fflush(stdout);

        scanf("%s", valor);
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

        /*resposta: printf("\n\nDeseja encerrar o programa? (sim / nao) ");
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
    }*/

    return 0;
}
