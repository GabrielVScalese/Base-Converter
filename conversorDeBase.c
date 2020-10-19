#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int converterParaDez (char* valor, int baseValor)
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

int converterParaBase (int valor, int baseConversao)
{
    int quociente = valor;
    int restos [1000];
    int result;

    int cont = 0;
    while (quociente != 0)
    {
        restos [cont++] = quociente % baseConversao;
        quociente = (int) quociente / baseConversao;
    }


    return result;
}

int converter (char *valor, int baseValor, int baseConversao)
{
    int result;
    int auxResult;
    switch (baseConversao)
    {
        case 2: auxResult = converterParaDez(valor, baseValor);
                result = converterParaBase(auxResult, baseConversao);
        break;
    }

    return result;
}

int main ()
{
    char *valor = malloc (1);
    int baseValor;
    int baseConversao;
    printf ("Conversor de bases numericas\n");

    printf ("\nDigite o valor a ser convertido:\n");
    fflush(stdout);

    scanf("%s", valor);

    printf ("\nDigite a base do valor:\n");
    fflush(stdout);

    scanf("%i", &baseValor);

    printf ("\nDigite a base para a conversao:\n");
    fflush(stdout);

    scanf("%i", &baseConversao);

    int result = converter(valor, baseValor, baseConversao);

    printf("\n%s na base %i vale %i", valor, baseConversao, result);

    return 0;
}
