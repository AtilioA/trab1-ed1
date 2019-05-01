#ifndef CARTAS_H_
#define CARTAS_H_

#include <stdlib.h>
#include <stdio.h>

// Define os valores possíveis para número e naipe das cartas do baralho
#define VALORES "23456QJK7A"
#define NAIPES "COPE"
#define nVALORES 10
#define nNAIPES 4
// Número padrão de cartas em uma mão
#define nMAO 3

// Estrutura de dados que abstrai uma carta, que possui valor e naipe
typedef struct
{
    char valor;
    char naipe;
} tCarta;

/* Funções para acessar estrutura opaca */
// Retorna o valor de uma carta
char Valor(tCarta carta);
// Retorna o naipe de uma carta
char Naipe(tCarta carta);

// Verifica se uma carta é válida
int CartaValida(tCarta carta);

// Cria uma carta e retorna-a
tCarta PreencheCarta(char valor, char naipe);

// Cria uma carta vazia e retorna-a
tCarta CartaVazia();

// Imprime uma carta
void ImprimeCarta(tCarta carta);


#endif
