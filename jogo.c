// Trabalho realizado por Alexsandro, Alvaro e João.
// Bibliotecas Usadas para o projeto
#include <stdio.h> //biblioteca usada para entradas e saídas
#include <stdlib.h> //biblioteca usada na função limpaTela
#include <string.h> //biblioteca usada para copiar vetores
#include <stdbool.h> //biblioteca usada para utilização de booleanos
#include <time.h> //biblioteca usada para criar a semente de tempo da função srand(time(NULL)) para aleatoriedade

//protótipo de funções para evitar erros
void iniciaTabuleiro(char tabuleiro[3][3]);
void exibeTabuleiro(char tabuleiro[3][3]);
void exibeInstrucoes();
int confereTabuleiro(char tabuleiro[3][3]);
void jogo(char nome1[], char nome2[], int pont1, int pont2);
void modoFacilCpu(char nomeDoJogador[], int pontJogador, int pontCPU);
void modoDificilCpu(char nomeDoJogador[], int pontJogador, int pontCPU);
int minimax(char tabuleiro[3][3], int profundidade, bool ehMaximizador);
int avaliarTabuleiro(char tabuleiro[3][3]);
bool tabuleiroCompleto(char tabuleiro[3][3]);
void encontrarMelhorMovimento(char tabuleiro[3][3], int *linha, int *coluna);
void menuInicial();

//funcao que realiza a limpa do terminal em sistemas operacionais Windows
void limpaTelaWindows(){
    system("cls");
}
//funcao que realiza a limpa do terminal em sistemas operacionais Linux
void limpaTelaLinux(){
    system("clear");
}
//funcao que cria o tabuleiro visualmente
void iniciaTabuleiro(char tabuleiro[3][3]){
    //Navega por cada posicaoo do tabuleiro e coloca o simbolo de '-'
    int linha,coluna;
    for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna++){
            tabuleiro[linha][coluna] = '-';
        }
    }
}
//funcao que mostra as instrucoes de possiveis posicoes que possam ser jogadas
void exibeInstrucoes(){
    printf("\nMapa de Posicoes:");
    printf("\n 1 | 2 | 3");
    printf("\n 4 | 5 | 6");
    printf("\n 7 | 8 | 9");
}
void exibeTabuleiro (char tabuleiro[3][3]){
//Exibe o tabuleiro com suas linhas e colunas quebrando a linha ao sair de um for
   int linha,coluna;
   printf("\n");
   for(linha = 0; linha < 3; linha++){
       for(coluna = 0; coluna < 3; coluna++){
           printf("%c   ", tabuleiro[linha][coluna]);
       }
       printf("\n");
   }
}
//funcao que verfica as linhas, colunas e as duas diagonais, em busca de um vencedor, que ira retorna o vencedor.
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

// Verifica se o tabuleiro esta completo (empate)
bool tabuleiroCompleto(char tabuleiro[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(tabuleiro[i][j] == '-')
                return false;
        }
    }
    return true;
}

// Funcao para avaliar o estado atual do tabuleiro
int avaliarTabuleiro(char tabuleiro[3][3]) {
    int resultado = confereTabuleiro(tabuleiro);

    // Se o jogador (X) ganhou, retorna -10
    if(resultado == 1)
        return -10;

    // Se a CPU (O) ganhou, retorna +10
    else if(resultado == 2)
        return 10;

    // Se eh empate, retorna 0
    return 0;
}

// Implementacao do algoritmo Minimax
int minimax(char tabuleiro[3][3], int profundidade, bool ehMaximizador) {
    // Avalia o estado atual do tabuleiro e atribui um valor a pontuação
    int pontuacao = avaliarTabuleiro(tabuleiro);

    // Se a CPU ganhou, retorna a pontuacao
    if(pontuacao == 10)
        return pontuacao - profundidade;

    // Se o jogador ganhou, retorna a pontuacao
    if(pontuacao == -10)
        return pontuacao + profundidade;

    // Se nao ha mais movimentos possiveis (empate)
    if(tabuleiroCompleto(tabuleiro))
        return 0;

    // Se eh a vez do maximizador (CPU)
    if(ehMaximizador) {
        int melhorPontuacao = -1000;

        // Percorre todas as celulas e calcula a pontuação das jogadas possíveis
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                // Verifica se a celula esta vazia
                if(tabuleiro[i][j] == '-') {
                    // Faz o movimento
                    tabuleiro[i][j] = 'O';

                    // Chama minimax recursivamente e escolhe o valor maximo
                    melhorPontuacao = (melhorPontuacao > minimax(tabuleiro, profundidade + 1, !ehMaximizador)) ?
                                      melhorPontuacao : minimax(tabuleiro, profundidade + 1, !ehMaximizador);

                    // Desfaz o movimento
                    tabuleiro[i][j] = '-';
                }
            }
        }
        //retorna a melhor pontuação possível
        return melhorPontuacao;
    }
    // Se eh a vez do minimizador (jogador)
    else {
        int melhorPontuacao = 1000;

        // Percorre todas as celulas
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                // Verifica se a celula esta vazia
                if(tabuleiro[i][j] == '-') {
                    // Faz o movimento
                    tabuleiro[i][j] = 'X';

                    // Chama minimax recursivamente e escolhe o valor minimo
                    melhorPontuacao = (melhorPontuacao < minimax(tabuleiro, profundidade + 1, !ehMaximizador)) ?
                                      melhorPontuacao : minimax(tabuleiro, profundidade + 1, !ehMaximizador);

                    // Desfaz o movimento
                    tabuleiro[i][j] = '-';
                }
            }
        }
        return melhorPontuacao;
    }
}

// Encontra o melhor movimento possivel para a CPU
void encontrarMelhorMovimento(char tabuleiro[3][3], int *linha, int *coluna) {
    int melhorPontuacao = -1000;
    *linha = -1;
    *coluna = -1;

    // Percorre todas as celulas
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            // Verifica se a celula esta vazia
            if(tabuleiro[i][j] == '-') {
                // Faz o movimento
                tabuleiro[i][j] = 'O';

                // Calcula a pontuacao para este movimento
                int pontuacaoMovimento = minimax(tabuleiro, 0, false);

                // Desfaz o movimento
                tabuleiro[i][j] = '-';

                // Se a pontuacao deste movimento eh maior que a melhor pontuacao,
                // atualiza a melhor pontuacao e o movimento
                if(pontuacaoMovimento > melhorPontuacao) {
                    *linha = i;
                    *coluna = j;
                    melhorPontuacao = pontuacaoMovimento;
                }
            }
        }
    }
}
// Funcao do modo facil da cpu
void modoFacilCpu(char nomeDoJogador[], int pontJogador, int pontCPU) {
    char tabuleiro[3][3];
    int posicoes[9][2] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
    int rodada = 0, estadoDeJogo = 1;
    char posicaoJogada;
    int linhaJogada, colunaJogada;
    bool posicionou;
    int opcao;
    iniciaTabuleiro(tabuleiro);
    //srand é necessario para que a funcao rand funcione normalmente, deixamos como "null" para que ele retorne o tempo atual em segundos, sem ela a funcao rand n funciona
    srand(time(NULL));
    while(rodada < 9 && estadoDeJogo == 1) {
        limpaTelaLinux();
        limpaTelaWindows();
        printf("\nRodada: %d\n", rodada);
        printf("Pontuacao: %s %d x %d CPU\n", nomeDoJogador, pontJogador, pontCPU);
        exibeTabuleiro(tabuleiro);
        exibeInstrucoes();
        if(rodada % 2 == 0) {
            // Jogador
            posicionou = false;
            while(!posicionou) {
                printf("\n%s, digite uma posicao (1-9): ", nomeDoJogador);
                scanf(" %c", &posicaoJogada);
                int idx = posicaoJogada - '1'; //converte o tipo char para inteiro e diminui um
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
            // CPU aleatorio
            posicionou = false;
            while(!posicionou) {
                int jogadaCPU = rand() % 9; // Recebe um valor aleatorio de 1 a 9
                linhaJogada = posicoes[jogadaCPU][0];
                colunaJogada = posicoes[jogadaCPU][1];
                if(tabuleiro[linhaJogada][colunaJogada] == '-') {
                    printf("\nCPU escolheu a posicao %d.\n", jogadaCPU + 1);
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
    if(estadoDeJogo == 1){
        printf("\nEmpate!\n");
    }
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
// Funcao do modo dificil da CPU, utilizando recursos como o minimax.
void modoDificilCpu(char nomeDoJogador[], int pontJogador, int pontCPU) {
    char tabuleiro[3][3];
    int posicoes[9][2] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
    int rodada = 0, estadoDeJogo = 1;
    char posicaoJogada;
    int linhaJogada, colunaJogada;
    bool posicionou;
    int opcao;
    iniciaTabuleiro(tabuleiro);
    while(rodada < 9 && estadoDeJogo == 1) {
        limpaTelaLinux();
        limpaTelaWindows();
        printf("\nRodada: %d\n", rodada);
        printf("Pontuacao: %s %d x %d CPU (Modo Dificil)\n", nomeDoJogador, pontJogador, pontCPU);
        exibeTabuleiro(tabuleiro);
        exibeInstrucoes();
        if(rodada % 2 == 0) {
            // Jogador
            posicionou = false;
            while(!posicionou) {
                printf("\n%s, digite uma posicao (1-9): ", nomeDoJogador);
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
            // CPU com algoritmo minimax
            printf("\nCPU esta pensando...\n");
            // Encontra o melhor movimento usando o algoritmo minimax
            encontrarMelhorMovimento(tabuleiro, &linhaJogada, &colunaJogada);
            // Converte a posisao da matriz para o numero correspondente no mapa
            int posicaoNumerica = -1;
            for(int i = 0; i < 9; i++) {
                if(posicoes[i][0] == linhaJogada && posicoes[i][1] == colunaJogada) {
                    posicaoNumerica = i + 1;
                    break;
                }
            }
            printf("\nCPU escolheu a posicao %d.\n", posicaoNumerica);
            tabuleiro[linhaJogada][colunaJogada] = 'O';
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
        modoDificilCpu(nomeDoJogador, pontJogador, pontCPU);
    else if(opcao == 2)
        menuInicial();
}
void jogo(char nomeDoJogadorUm [], char nomeDoJogadorDois [], int pontuacaoJogadorUm, int pontuacaoJogadorDois){
    ///Variaveis Gerais
    char nomeDoJogadorAtual[30];                                //Nomes dos jogadores
    char tabuleiro[3][3];                                       //Tabuleiro do Jogo
    //int linha,coluna;                                         //Auxiliares para tabuleiro
    int linhaJogada,colunaJogada,posicaoJogada;                 //Posicao em que o jogador posiciona sua marca
    int estadoDeJogo = 1;                                       //0 = Sem jogo,1 = Em Jogo
    int turnoDoJogador = 1;                                     //1 = X, 2 = O
    int rodada = 0;                                             //Quantas vezes os jogadores jogaram no total
    int opcao;                                                  //Opcao de reinicio
    bool posicionouJogada;                                      //Verifica se o jogador colocou um marcador no tabuleiro
    //Coloca os '-' no tabuleiro para indicar o vazio
    iniciaTabuleiro(tabuleiro);
    while(rodada < 9 && estadoDeJogo == 1){
        limpaTelaLinux();
        limpaTelaWindows();
        exibeTabuleiro(tabuleiro);
        printf("\n");
        exibeInstrucoes();
        printf("\n");
        printf("\nRodada: %i \n",rodada);
        printf("Pontuacao: %s : %i  x  %i : %s",nomeDoJogadorUm,pontuacaoJogadorUm,pontuacaoJogadorDois,nomeDoJogadorDois);
        //Atualiza o nome do jogador atual
        if(turnoDoJogador == 1){
            strcpy(nomeDoJogadorAtual,nomeDoJogadorUm);
        }else{
            strcpy(nomeDoJogadorAtual,nomeDoJogadorDois);
        }
        posicionouJogada = false;
        //Matriz de posicoes possiveis
        int posicoes[9][2] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
        while(posicionouJogada == false){
            //Ele ira le a jogada
            printf("\n%s digite uma posicao conforme o mapa acima:",nomeDoJogadorAtual);
            scanf("%d",&posicaoJogada);
            //Passa a linha e coluna de acordo com a matriz de posicoes exibida no mapa
            linhaJogada = posicoes[posicaoJogada-1][0];
            colunaJogada = posicoes[posicaoJogada-1][1];
            //Verifica se a posicao eh vazia
            if(tabuleiro[linhaJogada][colunaJogada] == '-'){
                //Conseguiu posicionar um marcador
                posicionouJogada = true;
                //Verifica de quem eh a vez para posicionar o marcador
                if(turnoDoJogador == 1){
                    tabuleiro[linhaJogada][colunaJogada] = 'X';
                    turnoDoJogador = 2;
                }else{
                    tabuleiro[linhaJogada][colunaJogada] = 'O';
                    turnoDoJogador = 1;
                }
            }
        }
        //Confere se o jogo acabou
        if(confereTabuleiro(tabuleiro) == 1){
            printf("O jogador %s venceu", nomeDoJogadorUm);
            pontuacaoJogadorUm++;
            estadoDeJogo = 0;
        }else if(confereTabuleiro(tabuleiro) == 2){
            printf("O jogador %s venceu", nomeDoJogadorDois);
            pontuacaoJogadorDois++;
            estadoDeJogo = 0;
        }
        //Aumenta uma rodada
        rodada++;
    }
    exibeTabuleiro(tabuleiro);
    printf("Fim de jogo");
    printf("\nO que deseja fazer?");
    printf("\n1-Continuar Jogando");
    printf("\n2-Menu Inicial");
    printf("\nDigite outro numero para sair: ");
    scanf("%d",&opcao);
    if(opcao == 1){
        jogo(nomeDoJogadorUm, nomeDoJogadorDois,pontuacaoJogadorUm,pontuacaoJogadorDois);
    }else if(opcao == 2){
        menuInicial();
    }else{
    }
}

void menuInicial(){
    //Opcao escolhida pelo jogador
    int opcao = 0, opcao2=0;
    //Nome dos jogadores
    char nomeDoJogadorUm[30], nomeDoJogadorDois[30];
    //Enquanto o jogador nao digita uma opcao valida, mostra o menu novamente
    while(opcao < 1 || opcao > 4){
        limpaTelaLinux();
        limpaTelaWindows();
        printf("Bem vindo ao Jogo da Velha");
        printf("\n1 - Jogar contra outro jogador");
        printf("\n2 - Jogar contra o CPU");
        printf("\n3 - Sobre");
        printf("\n4 - Sair");
        printf("\nEscolha uma opcao e tecle ENTER: ");
        //Faz a leitura da opcao
        scanf("%d", &opcao);
        //Faz algo de acordo com a opcao escolhida
        switch(opcao){
            case 1:
                //Inicia o jogo
                //printf("Jogo iniciado)";
                printf("Digite o nome do jogador 1: ");
                scanf("%s", nomeDoJogadorUm);
                printf("Digite o nome do jogador 2: ");
                scanf("%s", nomeDoJogadorDois);
                jogo(nomeDoJogadorUm, nomeDoJogadorDois,0,0);
                break;
            case 2:
                printf("\nModo CPU - Escolha a dificuldade:");
                printf("\n1 - Modo Facil\n2 - Modo Dificil\n");
                opcao2 = 0;
                while(opcao2 < 1 || opcao2 > 2) {
                    scanf("%d", &opcao2);
                    if(opcao2 == 1) {
                        printf("Digite seu nome: ");
                        scanf("%s", nomeDoJogadorUm);
                        modoFacilCpu(nomeDoJogadorUm, 0, 0);
                    } else if(opcao2 == 2) {
                        printf("Digite seu nome: ");
                        scanf("%s", nomeDoJogadorUm);
                        modoDificilCpu(nomeDoJogadorUm, 0, 0);
                    }
                }
                break;
            case 3:
                //Mostra informacoes do Jogo
                printf("Informacoes do jogo\n");
                break;
            case 4:
                printf("Ate mais!\n");
                break;
        }
    }
}
int main(){
    menuInicial();
    return 0;
}
