#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//menu do jogo

void limpaTela(){
    system("clear");
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
