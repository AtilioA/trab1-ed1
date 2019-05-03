#include "../include/PartidaCircular.h"

tJogador *InsereJogador(tJogador *jogador)
{
    tJogador *novo;
    novo = (tJogador *)malloc(sizeof(tJogador));
    CriaMao(&novo->mao);
    FMVazio(&novo->pontos);

    novo->prox = jogador;
    return (novo);
}

void PreparaPartida(tPartida *partida, int nJogadores)
{
    partida->nJogadores = 0;
    partida->inicial = (tJogador *)malloc(sizeof(tJogador));
    CriaMao(&partida->inicial->mao);
    FMVazio(&partida->inicial->pontos);
    partida->nJogadores++;
    tJogador *inicio = partida->inicial;
    while (QuantidadeJogadores(partida) <= nJogadores)
    {
        inicio = InsereJogador(inicio);
        partida->nJogadores++;
    }
    partida->inicial->prox = inicio;
}

void DestroiPartida(tPartida *partida)
{
    tJogador *atual, *lixo;
    lixo = partida->inicial;
    while ((QuantidadeJogadores(partida)) > 0)
    {
        atual = lixo->prox;
        LiberaMao(&lixo->mao);
        DestroiMonte(&lixo->pontos);
        free(lixo);
        lixo = atual;
        partida->nJogadores--;
    }
    DestroiMonte(partida->monte);
}

void MoveCabeca(tPartida *partida, int pos)
{
    tJogador *atual = partida->inicial;
    for (int i = 1; i <= pos; i++)
    {
        atual = atual->prox;
    }
    partida->inicial = atual;
}

void JogaCartaHumano(tPartida *partida, tJogador *humano) // não sei qual jogador é o humano
{
    int p = 0;
    printf("Informe a posicao da carta que quer jogar: ");
    scanf("%i", &p);

    tMao *maoJogador = Mao(humano);
    tCarta cartaSelecionada = PegaCarta(p, *maoJogador);
    MaoParaMonte(cartaSelecionada, Mesa(partida), maoJogador);
}

void ImprimePontuacao(tPartida *partida)
{
    int i = 0;
    tJogador *atual = partida->inicial;

    printf("Pontuação da partida:\n");
    for (i = 1, atual = partida->inicial; i < QuantidadeJogadores(partida); i++, atual = atual->prox)
    { // Falta mostrar no printf qual jogador é o humano
        printf("Jogador %i: %i pontos\n", i, *Pontuacao(atual));
    }
}

int QuantidadeJogadores(tPartida *partida)
{
    return (partida->nJogadores);
}

tJogador *JogadorInicial(tPartida *partida)
{
    return partida->inicial;
}

tMonte *Baralho(tPartida *partida)
{
    return partida->monte;
}

tCarta Corte(tPartida *partida)
{
    return partida->corte;
}

tMonte *Pontuacao(tJogador *jogador)
{
    return &jogador->pontos;
}

tMao *Mao(tJogador *jogador)
{
    return &jogador->mao;
}

tMonte *Mesa(tPartida *partida)
{
    return partida->mesa;
}

int PC(tJogador *jogador)
{
    return jogador->PC;
}

int *ModoDev(tPartida *partida)
{
    return &partida->modoDev;
}

int IndiceJogador(tJogador *jogador)
{
    return jogador->indice;
}

int Vencedor(tPartida *partida)
{
    for (int i = 1; i <= QuantidadeJogadores(partida); i++)
    {
        if (CartasIguais(MaiorMesa(Mesa(partida), Corte(partida)), CartaNoIndice(1, Mesa(partida))))
            MoveCabeca(partida, i - 1);
    }
    return (IndiceJogador(JogadorInicial(partida)));
}
