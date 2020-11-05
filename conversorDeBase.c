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
    struct no *novoNo = malloc(sizeof(struct no*));
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
    struct no *novoNo = malloc(sizeof(struct no*));
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

    for (; aux != NULL; aux = aux->prox) 
    {
        char *auxChar = aux->valor;
        strcat(charArray, aux->valor);
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

char getLetra (int valor)
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

long double converterParaDez (char valor [], unsigned int baseValor)
{
    long double result = 0;
    int i = strlen(valor) - 1;
    unsigned int cont = 0;

    for (; i >= 0 ; i--)
    {
        if (isalpha(valor[i]))
        {
            unsigned int digito = getValor(valor[i]);
            long double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
        else
        {
            unsigned int digito = valor[i] - '0';
            long double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
    }

    return result;
}

int isInteiro (double valor)
{
    int valorInteiro = (int) valor;
    return (valor == valorInteiro);
}

char* converterParaBaseFrac (double valor, unsigned int baseConversao)
{
    unsigned int quociente = (unsigned int) valor;
    double parteDecimal = valor - quociente;
    unsigned int aux = 0;
    unsigned int numeroCasas = 0;

    struct lista *listaResto = malloc(sizeof(struct lista*));
    inicializarLista(listaResto);
    struct lista *listaDecimal = malloc(sizeof(struct lista*));
    inicializarLista(listaDecimal);

    if (quociente == 0)
        inserirNoInicio(listaResto, "0");

    while (quociente != 0)
    {
        unsigned int resto = quociente % baseConversao;
        char *restoChar = malloc (sizeof(char));
       
        if (resto > 9)
            *restoChar = getLetra (resto);
        else
            sprintf(restoChar, "%u", resto);
        
        inserirNoInicio(listaResto, restoChar);
        quociente = (int) quociente / baseConversao;
    }

    if (parteDecimal != 0)
        while (numeroCasas < 11)
        {
            double produto = parteDecimal * baseConversao;
            aux = produto;
            parteDecimal = produto;
            char *auxChar = malloc (sizeof(char));
            
            if (aux > 9)
                *auxChar = getLetra (aux);
            else
                sprintf(auxChar, "%u", aux);
            
            inserirNoFim(listaDecimal, auxChar);

            if (isInteiro(parteDecimal))
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

long double converterParaDezFrac (char valor[], unsigned int baseValor)
{
    char delim [] = ",";
    char *split = strtok(valor, delim); // Obtem parte inteira do valor
    long double parteInteira = converterParaDez(split, baseValor);

    split = strtok(NULL, delim); // Obtem parte decimal do valor

    long double parteFrac = 0;
    unsigned int i = 0;
    int cont = -1;

    for (; i <= strlen(split) - 1; i++)
    {
        if (isalpha(split[i]))
        {
            unsigned int digito = getValor (split[i]);
            long double potencia = pow (baseValor, cont);
            parteFrac += digito * potencia;
            cont--;
        }
        else
        {
            unsigned int digito = split[i] - '0';
            long double potencia = pow (baseValor, cont);
            parteFrac += digito * potencia;
            cont--;
        }
    }

    return parteInteira + parteFrac;
}

char* converter (char *valor, unsigned int baseValor, unsigned int baseConversao, char *result)
{
    result = malloc (10 * sizeof(char));

    if (strchr(valor, ',') == NULL)
        strcat(valor, ",0");

    if (strchr(valor, '-') != NULL)
    {
        removaChar(valor, '-');
        strcpy(result, "-");
        long double valorNaDez = converterParaDezFrac(valor, baseValor);
        char *valorNaBase = converterParaBaseFrac (valorNaDez, baseConversao);
        strcat(result, valorNaBase);
        free(valorNaBase);
    }
    else
    {
        long double valorNaDez = converterParaDezFrac(valor, baseValor);
        result = converterParaBaseFrac (valorNaDez, baseConversao);
    }

    return result;
}

int existsBase (unsigned int base)
{
    return base >= 2 && base <= 36;
}

int existsNaBase (char valor[], unsigned int baseValor)
{
    unsigned int i = 0;
    char alfabeto [26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (; i <= strlen(valor) - 1; i++)
    {
        if (valor[i] == ',' || valor[i] == '-')
            continue;

        if (strchr(alfabeto, toupper(valor[i])))
        {
            unsigned int valorLetra = getValor(valor[i]);
            if (baseValor < valorLetra + 1)
                return 0;
        }
        else
        {
            int aux = valor[i] - '0';
            if (aux >= baseValor)
                return 0;
        }
    }

    return 1;
}

int main ()
{
    unsigned int continuar = 1;
    while (continuar != 0)
    {
        system("clear");
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

        base_valor: printf ("\nDigite a base do valor a ser convertido:\n");
        fflush(stdout);

        scanf("%u", &baseValor);
        fflush(stdin);

        if (existsBase(baseValor) == 0)
        {
            printf ("\nBase numérica inexistente!\n");
            fflush(stdout);
            goto base_valor;
        }

        if (existsNaBase(valor, baseValor) == 0)
        {
            printf ("\nValor não existente na base fornecida!\n");
            fflush(stdout);
            goto base_valor;
        }

        base_conversao: printf ("\nDigite a base para a conversao:\n");
        fflush(stdout);

        scanf("%u", &baseConversao);
        fflush(stdin);

        if (existsBase(baseConversao) == 0)
        {
            printf ("\nBase numérica inexistente!\n");
            fflush(stdout);
            goto base_conversao;
        }

        char* result = converter(valor, baseValor, baseConversao, result);

        printf("\nR: %s (base %u) = %s (base %u)\n", valorClone, baseValor, result, baseConversao);

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