#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//menu do jogo

void limpaTela(){
    system("clear");
}
void jogo(char nomeDoJogadorUm [], char nomeDoJogadorDois [], int pontuacaoJogadorUm, int pontuacaoJogadorDois){
 
    ///Variáveis Gerais
    char nomeDoJogadorAtual [30];//Nomes dos jogadores
    char tabuleiro[3][3];                                       //Tabuleiro do Jogo
    int linha,coluna;                                           //Auxiliares para tabuleiro
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
        printf("Pontuacao: %s %i  x  %i %s",nomeDoJogadorUm,pontuacaoJogadorUm,pontuacaoJogadorDois,nomeDoJogadorDois);
 
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
            printf("\nDigite uma posicao conforme o mapa acima:",nomeDoJogadorAtual);
            scanf("%c",&posicaoJogada); 
 
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
            printf("O jogador X venceu");
            pontuacaoJogadorUm++;
            estadoDeJogo = 0;
        }else if(confereTabuleiro(tabuleiro) == 2){
            printf("O jogador O venceu");
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
    printf("\n3-Sair");
    scanf("%i",&opcao);
    if(opcao == 1){
        jogo(nomeDoJogadorUm, nomeDoJogadorDois,pontuacaoJogadorUm,pontuacaoJogadorDois);
    }else if(opcao == 2){
        menuInicial();
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
                //jogo(nomeDoJogadorUm, nomeDoJogadorDois,0,0);
                
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
