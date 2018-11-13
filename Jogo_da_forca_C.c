#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 10

/* Estrutra para armazenar a ficha do jogador*/

struct cadastro{
  short int cod; //Código do jogador
  char nick[25]; //Nick do funcionario 
  short int score; //Pontuação do jogador
}player[MAX];

typedef struct cad_plvr{
  char nivel; //nivel de dificuldade das palavras
  char categoria; 
  char palavra;
}nv_palavra;

int topo, topo_plvr; //variaveis de controle, indicam quantos cadastros ja foram realizados
void menu();
void cadastrar();
void excluir();
void listar();
void pesquisar();
void cad_palavra();
//void listar_palavras();

int main(){
  menu();
  return 0;
}
void menu(){
  int n = 1;
    
  while(n!=0) {
    printf("Bem-vindo ao Jogo da Forca em C!\nO que deseja fazer?\n\n1 - Cadastro\n2 - Excluir cadastro\n3 - Ranking\n5 - Cadastrar palavras\n0 - Sair\n");
    scanf("%d", &n);
    
    switch(n) {
      case 0:
        return;
      case 1:{
        printf("Novo jogador\n\n");
               if(topo < MAX){
                 cadastrar();
               }
               else
               {
                 printf("Desculpe, sitema de cadastro esta no limite.\n\n");
               }
               break;
             }
               
        case 2:
             {
               if(topo == 0)
               {
                 printf("Não há dados para serem excluidos.\n\n");
               }
               else
               {
                 excluir();
                 printf("Cadastro excluido com sucesso.\n\n");
               }
               break;
             }
        case 3:
             {
               if(topo == 0)
               {
                 printf("Não há dados no sistema!\n\n");
               }
               else
               {
                 printf("Listando os jogadores cadastrados\n\n");
                 listar();
               }
               break;
             }
        case 4:
        case 5:
          cad_palavra();
          break;
        default:
               printf("Opcao invalida!\n\n");
                                     
      }
      }

}

//Cadastrar jogadores
void cadastrar(){
  FILE* cadastros;
  struct cadastro update;

  cadastros = fopen("ranking.bin", "ab");
  
  if(cadastros == NULL){
    printf("Não foi possivel acessar o banco para realizar o cadastro.\n\n");
  }

  else{
    player[topo].cod = topo + 1;
    printf("Informe seu nick: ");
    scanf("%s", player[topo].nick);
    player[topo].score = 0;

    printf("\nCadastro efetuado com sucesso!\n\nSeu codigo é: %d\n\n", player[topo].cod);

    topo = topo + 1;

    fwrite(&player[topo], sizeof(player[topo]), 10, cadastros);
  }
  fclose(cadastros);
}

//Excluir jogadores(Só o ultimo :v)
void excluir(){
  topo  = topo - 1;

}

//Listar todos os jogadores

void listar(){
  FILE *rkg;
  int i, resultado;
  rkg = fopen("rankig.bin", "rb");

  if(!rkg){
  printf("Não foi possível acessar o arquivo com o ranking.");
  }

  for(i = 0; i <= topo; i++){
    resultado = fread(&player[MAX], sizeof(topo), 10, rkg);
    printf("Nick: %s\nScore: %d", player[i].nick, player[i].score);
  }
  fclose(rkg);
}

/*pesquisar jogadores pelo codigo
void pesquisar(){
  int i, dado, cont = 0;
  
  printf("Pesquisa por codigo: ");
  scanf("%d",&dado);
  for(i = 0; i < topo; i++){

    if(dado == player[i].cod){
      printf("Cadastro encontrado\n\nCodigo: %d\nNick: %s\nScore: %d\n\n",player[i].cod, player[i].nick, player[i].score);
      cont = cont + 1;
    }
  }

  if(cont == 0){
    printf("Cadastro não encontrado!\n\n");
  }
}*/

//Cadastrar novas palavras
void cad_palavra(){
  int op;
  FILE* palavras;
  nv_palavra inp_plvr[50], cat;
  

  palavras = fopen("palavras.bin", "ab");

  if(palavras == NULL){
    printf("Não foi possivel acessar o banco de palavras.");
  }
  else{
    do{
      printf("Informe a palavra que deseja adicionar ao banco de palavras: ");
      scanf("%s", &inp_plvr[topo_plvr].palavra);

      //******FAZER UMA FUNÇÃO PARA CHECAR E ARMAZENAR AS PALAVRAS POR CATEGORIA/DIFICULDADE***********

      /*if(strlen(&inp_plvr.palavra) <= 6){
        inp_plvr.nivel = '1';
      }
      else if(strlen(&inp_plvr.palavra) > 4 && strlen(&inp_plvr.palavra) <= 8){
        inp_plvr.nivel = '2';
      }
      else{
        inp_plvr.nivel = '3';
      }
      
      inp_plvr.nivel = '1';
      inp_plvr.categoria = '8';*/
      fwrite(&inp_plvr, sizeof(nv_palavra), 1, palavras);

      printf("Deseja adicionar mais palavras?\n\n1 - Sim\n2 - Nao\n");
      scanf("%d", &op);
    
    }while(op == 1);
    fclose(palavras);
  }
  topo_plvr += 1;
  printf("%d° palavra", topo_plvr);
}