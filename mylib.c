#include "mylib.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define SAIR 27
#define ENTRAR 10
#define CIMA 119
#define BAIXO 115
#define ESQUERDA 97
#define DIREITA 100

void vocePerdeu() {
    screenGotoxy(30, 10);
    printf("Game Over!");
}

void attPlacar(int pontos) {
    screenGotoxy(35, 22);
    printf("Pontos: %d", pontos);
}

void aumentarTamanho(ParteCobra **cabeca, int x, int y) {
    ParteCobra *novaParte = malloc(sizeof(ParteCobra));
    novaParte->posX = x;
    novaParte->posY = y;
    novaParte->prox = NULL;
    if (*cabeca == NULL) {
        *cabeca = novaParte;
    } else {
        ParteCobra *temp = *cabeca;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = novaParte;
    }
}

void desenharCobra(ParteCobra *cabeca) {
    while (cabeca != NULL) {
        screenSetColor(BLUE, WHITE);
        screenGotoxy(cabeca->posX, cabeca->posY);
        printf("#");
        cabeca = cabeca->prox;
    }
}

void limparCobra(ParteCobra *cabeca) {
    while (cabeca != NULL) {
        screenGotoxy(cabeca->posX, cabeca->posY);
        printf(" ");
        cabeca = cabeca->prox;
    }
}

void movimentoCobra(ParteCobra **cabeca, int x, int y) {
    ParteCobra *novaParte = malloc(sizeof(ParteCobra));
    novaParte->posX = x;
    novaParte->posY = y;
    novaParte->prox = *cabeca;
    *cabeca = novaParte;

    ParteCobra *temp = *cabeca;
    while (temp->prox->prox != NULL) temp = temp->prox;
    free(temp->prox);
    temp->prox = NULL;
}

int checarColisao(ParteCobra *cabeca, int x, int y) {
    while (cabeca != NULL) {
        if (cabeca->posX == x && cabeca->posY == y) return 1;
        cabeca = cabeca->prox;
    }
    return 0;
}

void desenharFruta(int x, int y) {
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(x, y);
    printf("@");
}

void novaFruta(int *x, int *y) {
    *x = rand() % 68 + 8;
    *y = rand() % 16 + 4;
}

void adicionarPlacar(Placar **cabeca, Jogador jogador) {
    Placar *novo = malloc(sizeof(Placar));
    novo->jogador = jogador;
    novo->prox = NULL;

    if (*cabeca == NULL || (*cabeca)->jogador.pontos < jogador.pontos) {
        novo->prox = *cabeca;
        *cabeca = novo;
    } else {
        Placar *temp = *cabeca;
        while (temp->prox != NULL && temp->prox->jogador.pontos >= jogador.pontos) {
            temp = temp->prox;
        }
        novo->prox = temp->prox;
        temp->prox = novo;
    }
}

void salvarPlacar(Placar *cabeca, FILE *arquivo) {
    while (cabeca != NULL) {
        fwrite(&cabeca->jogador, sizeof(Jogador), 1, arquivo);
        cabeca = cabeca->prox;
    }
}

void freeCobra(ParteCobra **cabeca) {
    while (*cabeca != NULL) {
        ParteCobra *temp = *cabeca;
        *cabeca = (*cabeca)->prox;
        free(temp);
    }
}

void liberarPlacar(Placar **cabeca) {
    while (*cabeca != NULL) {
        Placar *temp = *cabeca;
        *cabeca = (*cabeca)->prox;
        free(temp);
    }
}

void exibirRanking(Placar *cabeca) {
    int posicao = 1;
    while (cabeca != NULL && posicao <= 3) {
        printf("%dº Lugar:\nNome: %s\nPontuação: %d\n", posicao, cabeca->jogador.nome, cabeca->jogador.pontos);
        cabeca = cabeca->prox;
        posicao++;
    }
}