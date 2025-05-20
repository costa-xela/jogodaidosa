#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

void iniciaTabuleiro(char tabuleiro[3][3]);
void exibeTabuleiro(char tabuleiro[3][3]);
void exibeInstrucoes();
int confereTabuleiro(char tabuleiro[3][3]);
void jogo(char nome1[], char nome2[], int pont1, int pont2);
void modoFacilCpu(char nomeDoJogador[], int pontJogador, int pontCPU);
void menuInicial();

void limpaTela() {
    system("cls");
}

void iniciaTabuleiro(char tabuleiro[3][3]) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            tabuleiro[i][j] = '-';
}

void exibeTabuleiro(char tabuleiro[3][3]) {
    printf("\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            printf(" %c ", tabuleiro[i][j]);
        printf("\n");
    }
}

void exibeInstrucoes() {
    printf("\nMapa de posicoes (teclas 1 a 9):\n");
    printf(" 7 | 8 | 9 \n");
    printf(" 4 | 5 | 6 \n");
    printf(" 1 | 2 | 3 \n");
}

int confereTabuleiro(char tabuleiro[3][3]) {
    // Verifica Linhas, Colunas e Diagonais
    for(int i = 0; i < 3; i++) {
        if(tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != '-')
            return (tabuleiro[i][0] == 'X') ? 1 : 2;
        if(tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != '-')
            return (tabuleiro[0][i] == 'X') ? 1 : 2;
    }
    if(tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != '-')
        return (tabuleiro[0][0] == 'X') ? 1 : 2;
    if(tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != '-')
        return (tabuleiro[0][2] == 'X') ? 1 : 2;

    return 0;
}

void modoFacilCpu(char nomeDoJogador[], int pontJogador, int pontCPU) {
    char tabuleiro[3][3];
    int posicoes[9][2] = {{2,0},{2,1},{2,2},{1,0},{1,1},{1,2},{0,0},{0,1},{0,2}};
    int rodada = 0, estadoDeJogo = 1;
    char posicaoJogada;
    int linhaJogada, colunaJogada;
    bool posicionou;
    int opcao;

    iniciaTabuleiro(tabuleiro);
    srand(time(NULL));

    while(rodada < 9 && estadoDeJogo == 1) {
        limpaTela();
        printf("\nRodada: %d\n", rodada);
        printf("Pontuacao: %s %d x %d CPU\n", nomeDoJogador, pontJogador, pontCPU);
        exibeTabuleiro(tabuleiro);
        exibeInstrucoes();

        if(rodada % 2 == 0) {
            // Jogador
            posicionou = false;
            while(!posicionou) {
                printf("\n%s, digite uma posição (1-9): ", nomeDoJogador);
                scanf(" %c", &posicaoJogada);
                int idx = posicaoJogada - '1';
                if(idx >= 0 && idx <= 8) {
                    linhaJogada = posicoes[idx][0];
                    colunaJogada = posicoes[idx][1];
                    if(tabuleiro[linhaJogada][colunaJogada] == '-') {
                        tabuleiro[linhaJogada][colunaJogada] = 'X';
                        posicionou = true;
                    }
                }
            }
        } else {
            // CPU aleatório
            posicionou = false;
            while(!posicionou) {
                int jogadaCPU = rand() % 9; // Recebe um valor aleatorio de 1 a 9
                linhaJogada = posicoes[jogadaCPU][0];
                colunaJogada = posicoes[jogadaCPU][1];
                if(tabuleiro[linhaJogada][colunaJogada] == '-') {
                    printf("\nCPU escolheu a posição %d.\n", jogadaCPU + 1);
                    tabuleiro[linhaJogada][colunaJogada] = 'O';
                    posicionou = true;
                }
            }
        }

        int resultado = confereTabuleiro(tabuleiro);
        if(resultado == 1) {
            printf("\n%s venceu!\n", nomeDoJogador);
            pontJogador++;
            estadoDeJogo = 0;
        } else if(resultado == 2) {
            printf("\nCPU venceu!\n");
            pontCPU++;
            estadoDeJogo = 0;
        }

        rodada++;
    }

    exibeTabuleiro(tabuleiro);
    if(estadoDeJogo == 1) printf("\nEmpate!\n");

    printf("\nO que deseja fazer?");
    printf("\n1 - Jogar novamente");
    printf("\n2 - Menu Inicial");
    printf("\n3 - Sair\n");
    scanf("%d", &opcao);

    if(opcao == 1)
        modoFacilCpu(nomeDoJogador, pontJogador, pontCPU);
    else if(opcao == 2)
        menuInicial();
}

void jogo(char nomeDoJogadorUm[], char nomeDoJogadorDois[], int pontuacaoJogadorUm, int pontuacaoJogadorDois) {

}

void menuInicial() {
    int opcao = 0, opcao2 = 0;
    char nomeDoJogadorUm[30], nomeDoJogadorDois[30];

    while(opcao < 1 || opcao > 4) {
        limpaTela();
        printf("Bem vindo ao Jogo da Velha");
        printf("\n1 - Jogar contra outro jogador");
        printf("\n2 - Jogar contra o CPU");
        printf("\n3 - Sobre");
        printf("\n4 - Sair");
        printf("\nEscolha uma opcao e tecle ENTER: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o nome do jogador 1: ");
                scanf("%s", nomeDoJogadorUm);
                printf("Digite o nome do jogador 2: ");
                scanf("%s", nomeDoJogadorDois);
                jogo(nomeDoJogadorUm, nomeDoJogadorDois, 0, 0);
                break;
            case 2:
                printf("\nModo CPU - Escolha a dificuldade:");
                printf("\n1 - Modo Facil\n2 - (Ainda to fazendo, num escolha esse cabrunco nao)\n");
                while(opcao2 < 1 || opcao2 > 2) {
                    scanf("%d", &opcao2);
                    if(opcao2 == 1) {
                        printf("Digite seu nome: ");
                        scanf("%s", nomeDoJogadorUm);
                        modoFacilCpu(nomeDoJogadorUm, 0, 0);
                    } else {
                        printf("te MANDEI NAO ESCOLHER ESSA OPCAO\n");
                        menuInicial();
                    }
                }
                break;
            case 3:
                printf("\nJogo da Velha em C - por Alexsando, Alvaro, Joao!\n");
                break;
            case 4:
                printf("\nSaindo...\n");
                exit(0);
        }
    }
}

int main() {
    menuInicial();
    return 0;
}
