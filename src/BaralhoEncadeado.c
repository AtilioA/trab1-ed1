#include "../include/Cartas.h"
#include "../include/Maos.h"
#include "../include/BaralhoEncadeado.h"

void FMVazio(tMonte *monte)
{
    monte->primeiro = (tCelula *)malloc(sizeof(tCelula)); // monte->primeiro será a cabeça do monte
    monte->ultimo = monte->primeiro;
    monte->ultimo->prox = NULL;
    monte->tamanho = 0;
}

void CriaBaralho(tMonte *monte)
{
    FMVazio(monte);
    tCarta atual;

    for (int i = 0; i < nVALORES * nNAIPES; i++)
    {
        atual = PreencheCarta(VALORES[i % 10], NAIPES[i / 10]);
        Insere(atual, monte);
    }
}

int EstaVazio(tMonte *monte)
{
    return (QuantidadeMonte(monte) == 0);
}

tCelula CriaCelulaVazia()
{
    tCelula celulaVazia;

    celulaVazia.carta = CartaVazia();
    celulaVazia.prox = NULL;

    return celulaVazia;
}

tCarta Carta(tCelula *celula)
{
    return celula->carta;
}

int QuantidadeMonte(tMonte *monte)
{
    return (monte->tamanho);
}

int ExisteCarta(tCarta x, tMonte *monte)
{
    if (EstaVazio(monte))
    {
        return 0;
    }
    tCelula *atual = monte->primeiro->prox;

    while (atual != NULL)
    {
        if ((Valor(Carta(atual)) == Valor(x)) && (Naipe(Carta(atual)) == Naipe(x)))
            return 1;
        atual = atual->prox;
    }
    return 0;
}

void Insere(tCarta x, tMonte *monte)
{
    if (!ExisteCarta(x, monte))
    {
        monte->ultimo->prox = (tCelula *)malloc(sizeof(tCelula));
        monte->ultimo = monte->ultimo->prox;
        monte->ultimo->carta = x;
        monte->ultimo->prox = NULL;

        monte->tamanho++;
    }
    else
    {
        printf("A carta ja existe no monte.\n");
    }
}

void Retira(tCarta x, tMonte *monte, tCarta *cartaRetirada)
{
    tCelula *atual, *anterior;

    anterior = monte->primeiro;
    for (atual = monte->primeiro->prox; atual != NULL; atual = atual->prox)
    {
        if ((Valor(Carta(atual)) == Valor(x)) && (Naipe(Carta(atual)) == Naipe(x)))
        {
            *cartaRetirada = Carta(atual);
            anterior->prox = atual->prox;
            free(atual);
            monte->tamanho--;
            return;
        }
        anterior = atual;
    }
    *cartaRetirada = CartaVazia();
}

tCarta Corta(tMonte *monte, int pos)
{
    tCarta corte;

    if ((pos >= 1) && (pos <= QuantidadeMonte(monte)))
    {
        int i = 1;
        tCelula *atual;
        atual = monte->primeiro->prox;

        while (atual != NULL && i < pos)
        {
            i++;
            atual = atual->prox;
        }

        if (atual != NULL)
        {
            monte->ultimo->prox = monte->primeiro->prox;
            monte->primeiro->prox = atual->prox;
            monte->ultimo = atual;
            atual->prox = NULL;
            corte = Carta(monte->ultimo);
        }
        if ((Valor(corte) == 'A') || (Valor(corte) == '7')) {
            pos = ((pos + 1) % QuantidadeMonte(monte)) + 1;
            corte = Corta(monte, pos);
        }
        return (corte);
    }
    printf("ERRO! Nao foi possivel cortar.\n");
    return (CartaVazia());
}

void TrocaCarta(tMonte *monte, tCelula *celula, int pos)
{
    int i = 1;

    if (pos < QuantidadeMonte(monte))
    {
        tCarta primeiraCarta = Carta(celula);
        tCarta segundaCarta = CartaNoIndice(pos, monte);
        celula->carta = segundaCarta;

        // Agora basta substituir a carta da célula no índice pela carta da célula de entrada
        tCelula *atual = monte->primeiro->prox;
        while (atual != NULL && i < pos)
        {
            i++;
            atual = atual->prox;
            // printf("Buscando celula original...\n");
        }
        if (atual == NULL)
        {
            printf("Nao foi possivel chegar na posicao!\n");
        }
        else
        {
            atual->carta = primeiraCarta;
        }
    }
    else
    {
        printf("A posicao fica fora da monte.\n");
    }
}

// Para cada célula da monte, gerar uma posição aleatória dentro da monte e mover a célula pra esta posição
void Embaralha(tMonte *monte)
{
    int posAleatoria = 0, tamMonte = QuantidadeMonte(monte);

    if (tamMonte != 0)
    {
        struct timeval t;
        tCelula *anterior = NULL;
        tCelula *atual = monte->primeiro->prox;

        gettimeofday(&t, NULL);
        srand((unsigned int)t.tv_usec); // Inicializa o gerador de números aleatórios
        while (atual != NULL)
        {
            anterior = atual;
            atual = atual->prox;

            posAleatoria = (rand() % tamMonte);
            if (posAleatoria < 1)
            {
                posAleatoria = 1;
            }

            // printf("%i, %i\n\n", tamMonte, posAleatoria);
            TrocaCarta(monte, anterior, posAleatoria);
        }
    }
}

// Usando imprimeCarta
void ImprimeMonte(tMonte *monte)
{
    if (QuantidadeMonte(monte) != 0)
    {
        tCelula *atual = NULL;

        //printf("Quantidade de itens: %i\n", QuantidadeMonte(monte)); // Ocultar isso depois
        for (atual = monte->primeiro->prox; atual != NULL; atual = atual->prox)
            ImprimeCarta(Carta(atual));
    }
}

void DestroiMonte(tMonte *monte)
{
    tCelula *anterior, *atual;

    atual = monte->primeiro;
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        free(anterior);
    }

    monte->tamanho = 0;
}

tCarta CartaNoIndice(int pos, tMonte *monte)
{
    if (pos >= 1) // 1 como sendo o primeiro elemento
    {
        int i = 1;
        tCelula *atual = monte->primeiro->prox; // cabeça da lista

        while (atual != NULL && i < pos)
        {
            i++;
            atual = atual->prox;
        }

        if (atual != NULL)
        {
            return Carta(atual);
        }
    }

    return CartaVazia();
}

void MaoParaMonte(tCarta carta, tMonte *monte, tMao *mao)
{
    RetiraDaMao(carta, mao);
    Insere(carta, monte);
}

void MonteParaMao(tCarta *carta, tMonte *monte, tMao *mao)
{
    tCarta retirada;

    Retira(*carta, monte, &retirada);
    ColocaNaMao(retirada, mao);
}

int PontuacaoCarta(tCarta x)
{
    switch (Valor(x))
    {
    case 'A':
        return 11;
    case '7':
        return 10;
    case 'K':
        return 4;
    case 'Q':
        return 3;
    case 'J':
        return 2;
    default:
        return 0;
    }
}

int ContaPontos(tMonte *monte)
{
    tCelula *atual = monte->primeiro->prox;
    int pontos = 0;

    while (atual != NULL)
    {
        pontos += PontuacaoCarta(Carta(atual));
        atual = atual->prox;
    }

    return pontos;
}
