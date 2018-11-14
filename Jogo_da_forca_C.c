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
  char nivel[15]; //nivel de dificuldade das palavras
  char categoria[20]; 
  char palavra[50];
}nv_palavra;

int topo, topo_plvr; //variaveis de controle, indicam quantos cadastros ja foram realizados
void menu();
void cadastrar();
void listar();
void cad_palavra();
//void listar_palavras();

int main(){
  topo = 0;
  menu();
  return 0;
}

void menu(){
  int n = 1;
    
  while(n!=0) {
    printf("Bem-vindo ao Jogo da Forca em C!\nO que deseja fazer?\n\n1 - Cadastro\n2 - Excluir cadastro\n3 - Ranking\n5 - Cadastrar palavras\n0 - Sair\n");
    scanf("%d", &n);
    
    switch(n){
      case 0:
        return;
        
      case 1:{
        printf("Novo jogador\n\n");

        if(topo < MAX){
          cadastrar();
        }

        else{
          printf("Desculpe, sitema de cadastro esta no limite.\n\n");
        }
        break;
      }
               
      case 2:{
        if(topo == 0){
          printf("Não há dados para serem excluidos.\n\n");
        }
        
        else{
          
          printf("Cadastro excluido com sucesso.\n\n");
        }
        break;
      }
        
      case 3:{
        /*if(topo == 0){
          printf("Não há dados no sistema!\n\n");
          }
          
          else{
            printf("Listando os jogadores cadastrados\n\n");*/
            listar();
          //}
         break;
      }
      
      case 4:

      case 5:{
        cad_palavra();
        break;
      }

      default:
        printf("Opcao invalida!\n\n");                       
    }
  }

}

//Cadastrar jogadores
void cadastrar(){
  FILE* cadastros;
  char nick[25];

  cadastros = fopen("ranking.txt", "a");
  
  if(!cadastros){
    printf("Não foi possivel acessar o banco para realizar o cadastro.\n\n");
    return;
  }

  else{
    player[topo].cod = (topo + 1);

    do{
      printf("Informe seu nick(máximo 25 caracteres): ");
      scanf("%s", nick);
    }while(strlen(nick) > 25);
    
    player[topo].score = 0;
    
    printf("\nCadastro efetuado com sucesso!\n\nSeu codigo é: %d\n\n", player[topo].cod);

    topo = topo + 1;

    fprintf(cadastros, "%d", player[topo].cod);
    fprintf(cadastros, "%c", '-');
    fprintf(cadastros, "%s", nick);
    fprintf(cadastros, "%c", '-');
    fprintf(cadastros, "%d", player[topo].score);
    fprintf(cadastros, "%c", '\n');
  }
  fclose(cadastros);
}

//Listar todos os jogadores

void listar(){
  FILE *rkg;
  int i, resultado;
  char players[10];

  rkg = fopen("ranking.txt", "r");

  if(!rkg){
  printf("Não foi possível acessar o arquivo com o ranking.");
  return;
  }

  while(fgets(players, 10, rkg) != NULL)
  printf("%s", players);
  
  fclose(rkg);

  printf("\n \n");
}


//Cadastrar novas palavras
void cad_palavra(){
  int op;
  FILE* palavras = NULL;
  nv_palavra inp_plvr[50], cat;
  

  palavras = fopen("palavras.txt", "a+");

  if(!palavras){
    printf("Não foi possivel acessar o banco de palavras.");
  }

  else{

    do{
      printf("Informe a palavra que deseja adicionar ao banco de palavras: ");
      scanf("%s", &inp_plvr[topo_plvr].palavra[50]);

      fprintf(palavras, "%s", &inp_plvr[topo_plvr].palavra[50]);
      fprintf(palavras, "%c", '\n');

      printf("Deseja adicionar mais palavras?\n\n1 - Sim\n2 - Nao\n");
      scanf("%d", &op);
    
    } while(op == 1);
    fclose(palavras);
  }
  topo_plvr += 1;
}
