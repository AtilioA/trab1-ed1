#include "include/IA2Jogadores.h"
#include "include/IA4Jogadores.h"
#include "include/Maos.h"
#include "include/Cartas.h"
#include "include/BaralhoEncadeado.h"
#include "include/PartidaCircular.h"
#include "include/Jogo.h"
#include <time.h>

int main()
{

    tMonte baralho;
    tPartida *partida;
    CriaBaralho (&baralho);
    partida = CriaPartida(4, &baralho);
    Partida (partida, &baralho);
    FinalizaPartida (partida);
    DestroiPartida (partida);
    /* Se precisar do que estava aqui é só pegar no GitHub */

    return 0;
}
