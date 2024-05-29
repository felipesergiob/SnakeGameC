#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SAIR 27
#define ENTRAR 10
#define CIMA 119
#define BAIXO 115
#define ESQUERDA 97
#define DIREITA 100

typedef struct {
    char nome[20];
    int pontos;
} Jogador;

typedef struct ParteCobra {
    int posX, posY;
    struct ParteCobra *prox;
} ParteCobra;

typedef struct Placar {
    Jogador jogador;
    struct Placar *prox;
} Placar;

void vocePerdeu();
void attPlacar(int pontos);
void aumentarTamanho(ParteCobra **cabeca, int x, int y);
void desenharCobra(ParteCobra *cabeca);
void limparCobra(ParteCobra *cabeca);
void movimentoCobra(ParteCobra **cabeca, int x, int y);
int checarColisao(ParteCobra *cabeca, int x, int y);
void desenharFruta(int x, int y);
void novaFruta(int *x, int *y);
void adicionarPlacar(Placar **cabeca, Jogador jogador);
void salvarPlacar(Placar *cabeca, FILE *arquivo);
void freeCobra(ParteCobra **cabeca);
void liberarPlacar(Placar **cabeca);
void exibirRanking(Placar *cabeca);

#endif 