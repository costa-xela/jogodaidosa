#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void menuInicial();
void jogo ();
void limpaTela(){
    system("clear");
    system("cls");
}
void iniciaTabuleiro(char tabuleiro[3][3]){
 
    //Navega por cada posição do tabuleiro e coloca o símbolo de '-'
    int linha,coluna;
    for(linha = 0; linha < 3; linha++){
        for(coluna = 0; coluna < 3; coluna++){
            tabuleiro[linha][coluna] = '-';
        }
    }
 
}
void exibeInstrucoes(){
 
    printf("\nMapa de Posicoes:");
    printf("\n 7 | 8 | 9");
    printf("\n 4 | 5 | 6");   
    printf("\n 1 | 2 | 3");
 
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
int confereTabuleiro(char tabuleiro[3][3]){
 
    int linha, coluna;

    //Confere linhas
    for(linha = 0; linha < 3; linha++){
        if(tabuleiro[linha][0] == 'X' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]){
            return 1;
        }else if(tabuleiro[linha][0] == 'O' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]){
            return 2;
        }
    }

    //Confere Colunas
    for(coluna = 0; coluna < 3; coluna++){
        if(tabuleiro[0][coluna] == 'X' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]){
            return 1;
        }else if(tabuleiro[0][coluna] == 'O' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]){
            return 2;
        }
    }

    //Diagonal Principal
    if(tabuleiro[0][0] != '-' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]){

        if(tabuleiro[0][0] == 'X'){
           return 1;
        }else{
           return 2;
        }
    }

    //Diagonal Secundária
    if(tabuleiro[0][2] != '-' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]){

        if(tabuleiro[0][2] == 'X'){
            return 1;
        }else{
           return 2;
        }
    }

    return 0;
}

void jogo(char nomeDoJogadorUm [], char nomeDoJogadorDois [], int pontuacaoJogadorUm, int pontuacaoJogadorDois){
 
    ///Variáveis Gerais
    char nomeDoJogadorAtual[30];//Nomes dos jogadores
    char tabuleiro[3][3];                                       //Tabuleiro do Jogo
    //int linha,coluna;                                           //Auxiliares para tabuleiro
    int linhaJogada,colunaJogada,posicaoJogada;                 //Posição em que o jogador posiciona sua marca
    int estadoDeJogo = 1;                                       //0 = Sem jogo,1 = Em Jogo
    int turnoDoJogador = 1;                                     //1 = X, 2 = O
    int rodada = 0;                                             //Quantas vezes os jogadores jogaram no total
    int opcao;                                                  //Opção de reinício
    bool posicionouJogada;                                      //Verifica se o jogador colocou um marcador no tabuleiro
 
    //Coloca os '-' no tabuleiro para indicar o vazio
    iniciaTabuleiro(tabuleiro);
 
    while(rodada < 9 && estadoDeJogo == 1){
 
        limpaTela();
 
        printf("\nRodada: %i \n",rodada);
        printf("Pontuacao: %s : %i  x  %i : %s",nomeDoJogadorUm,pontuacaoJogadorUm,pontuacaoJogadorDois,nomeDoJogadorDois);
 
        //Exibe o tabuleiro na tela
        exibeTabuleiro(tabuleiro);
 
        //Exibe qual numero corresponde a qual posicao
        exibeInstrucoes();
 
 
        //Atualiza o nome do jogador atual
        if(turnoDoJogador == 1){
 
            strcpy(nomeDoJogadorAtual,nomeDoJogadorUm);

            
 
        }else{
 
            strcpy(nomeDoJogadorAtual,nomeDoJogadorDois);
 
        }
 
        posicionouJogada = false;
 
        //Matriz de posicoes possíveis
        int posicoes[9][2] = {{2,0},{2,1},{2,2},{1,0},{1,1},{1,2},{0,0},{0,1},{0,2}};
 
        while(posicionouJogada == false){
 
            //Lê a jogada
            printf("\n%s digite uma posicao conforme o mapa acima:",nomeDoJogadorAtual);
            scanf("%d",&posicaoJogada); 
 
            //Passa a linha e coluna de acordo com a matriz de posições exibida no mapa
            linhaJogada = posicoes[posicaoJogada-1][0];
            colunaJogada = posicoes[posicaoJogada-1][1];
 
            //Verifica se a posição é vazia
            if(tabuleiro[linhaJogada][colunaJogada] == '-'){
 
                //Conseguiu posicionar um marcador
                posicionouJogada = true;
 
                //Verifica de quem é a vez para posicionar o marcador
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
 
    //Opção escolhida pelo jogador
    int opcao = 0, opcao2=0;
 
    //Nome dos jogadores
    char nomeDoJogadorUm[30], nomeDoJogadorDois[30];
 
    //Enquanto o jogador não digita uma opcao válida, mostra o menu novamente
    while(opcao < 1 || opcao > 4){
        limpaTela();
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
                //logica do jogo contra a CPU;
                printf("\nPara jogar contra a CPU, digite a dificudade");
                printf("\n1-Modo fácil \n2-Modo difícil\n");
                
                while (opcao2<1||opcao2>2)
                {
                    scanf("%d", &opcao2);
                    if(opcao2<1||opcao2>2){
                        printf("Opcao invalida");
                    }
                }
                //jogo_aleatorio(nomeDoJogadorUm, nomeDoJogadorDois,0,0);
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
