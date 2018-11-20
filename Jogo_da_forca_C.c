//Jogo da forca proposto como atividade avaliativa do terceiro estágio da cadeira de Introdução à linguagem de programação, do curso de Ciência da Computação, segundo período, Unipê.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
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
char random_word[30];
void menu();
void menu2();
void escolhepalavra();
void jogar(char *palavra);
void cadastrar();
void listar();
void cad_palavra();
void boneco(int x);

int main(){
  topo = 0;
  escolhepalavra();
  menu();
  return 0;
}

void menu(){
  int n = 1;
  char *teste = "homem-aranha 3";
    
  while(n!=0) {
    printf("Bem-vindo ao Jogo da Forca em C!\nO que deseja fazer?\n\n1 - Cadastro\n3 - Ranking\n4 - Jogar\n5 - Cadastrar palavras\n0 - Sair\n");
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
        jogar(random_word);
        break;
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
      scanf(" %[^\t\n]s", &inp_plvr[topo_plvr].palavra[50]);

      fprintf(palavras, "%s", &inp_plvr[topo_plvr].palavra[50]);
      fprintf(palavras, "%c", '\n');

      printf("Deseja adicionar mais palavras?\n\n1 - Sim\n2 - Nao\n");
      scanf("%d", &op);
    
    } while(op == 1);
    fclose(palavras);
  }
  topo_plvr += 1;
}

void boneco(int x){
  printf("\n");
  switch(x){
    case 0:{
      printf("       ____      \n ");
      printf("     / ô ô\\ \n");     
      printf("     (   u  )\n");     
      printf("      \\____/  \n");               
      printf("    /\\  ._. /\\  \n");   
      printf("   / /  | | \\ \\   \n") ;
      printf("  / /   |_|  \\ \\  \n");
      printf(" / /    |-|   \\ \\  \n");
      printf("/ /     | |    \\ \\ \n");
      printf("\\/      |_|     \\/ \n");
      printf("    /\\      /\\   \n");
      printf("   / /      \\ \\   \n");
      printf("  / /        \\ \\  \n");
      printf(" / /          \\ \\ \n");
      printf("/ /            \\ \\ \n");
      printf("\\/              \\/ \n\n");
      break;
    }
    case 1:{
      printf("       ____      \n ");
      printf("     / ô ô\\ \n");     
      printf("     (   u  )\n");     
      printf("      \\____/  \n");               
      printf("    /\\  ._. /\\  \n");   
      printf("   / /  | | \\ \\   \n") ;
      printf("  / /   |_|  \\ \\  \n");
      printf(" / /    |-|   \\ \\  \n");
      printf("/ /     | |    \\ \\ \n");
      printf("\\/      |_|     \\/ \n");
      printf("    /\\        \n");
      printf("   / /         \n");
      printf("  / /          \n");
      printf(" / /           \n");
      printf("/ /             \n");
      printf("\\/               \n\n");
      break;
    }
    case 2:{
      printf("       ____      \n ");
      printf("     / ô ô\\ \n");     
      printf("     (   u  )\n");     
      printf("      \\____/  \n");               
      printf("    /\\  ._. /\\  \n");   
      printf("   / /  | | \\ \\   \n") ;
      printf("  / /   |_|  \\ \\  \n");
      printf(" / /    |-|   \\ \\  \n");
      printf("/ /     | |    \\ \\ \n");
      printf("\\/      |_|     \\/ \n\n");
      break;
    }
    case 3:{
      printf("       ____      \n ");
      printf("     / ô ô\\ \n");     
      printf("     (   u  )\n");     
      printf("      \\____/  \n");               
      printf("    /\\  ._.   \n");   
      printf("   / /  | |    \n") ;
      printf("  / /   |_|    \n");
      printf(" / /    |-|     \n");
      printf("/ /     | |     \n");
      printf("\\/      |_|      \n\n");
      break;
    }
    case 4:{
      printf("       ____      \n ");
      printf("     / ô ô\\ \n");     
      printf("     (   u  )\n");     
      printf("      \\____/  \n");               
      printf("      ._.   \n");   
      printf("     | |    \n") ;
      printf("     |_|    \n");
      printf("     |-|     \n");
      printf("     | |     \n");
      printf("      |_|      \n\n");
      break;
    }
    case 5:{
      printf("       ____      \n ");
      printf("     / x x\\ \n");     
      printf("     (   n  )\n");     
      printf("      \\____/  \n\n");
      break;    
    }
  }
}

void escolhepalavra() {
	FILE* f;
  int qtddepalavras, randomico;

	f = fopen("palavras.txt", "r");

	if(!f) {
		printf("Não foi possivel acessar o banco de palavras.\n\n");
    return;
	}

	while(fgets(random_word, 10, f) != NULL){
    qtddepalavras++;
  }
  qtddepalavras -= 4;

	srand(time(NULL));
  rand();
	randomico = rand() % qtddepalavras;

  fseek(f, 0, SEEK_SET);
	for(int i = 0; i <= randomico; i++) {
		fscanf(f, "%s", random_word);
	}
  
  printf("(linha 305) Quantidade de palavras: %d\npalavra escolhida %s\n\n", qtddepalavras, random_word);

	fclose(f);
}

void jogar(char *palavra){
  int t, i, erros = 0, char_especial = 0, acertou = 0, tentativas = 0;
  char letras_tentadas[20]; 
  char *teste = "homem-aranha 3";

  //Esse for mede a quantidade de caracteres presentes na palavra a ser adivinhada
  for(t = 0; palavra[t] != '\0'; t++){
    if(palavra[t] == '-' || palavra[t] == ' '){
      char_especial++; //esse contador vai ser usado para subtrair os caracteres especiais para que fiquem visiveis para o usuario
    }
  }

  printf("A palavra possui %d letras\n\n", (t - char_especial));

  char* copia_randwrd = ((char*) malloc(t * sizeof(char)));//alocação dinamica para o que vai ser mostrado ao usuario
  if(!copia_randwrd){
    return;
  }

  //printa a palavras com as letras substituidas por underlines e mostra espaços e hífens
  for(i = 0; palavra[i] != '\0'; i++){
    if(palavra[i] == '-'){
      printf("- ");
    }
    else if(palavra[i] == ' '){
      printf(" ");
    }
    else{
      printf("_ ");
    }
  } 

  //preenchi o vetor com espaços vazios para facilitar a validação de um único caractere
  for(i = 0; i < 20; i++){
    letras_tentadas[i] = '1';
  }

  for(i = 0; i < t; i++){
    copia_randwrd[i] = '_';
  }
  
  do{
    //Letras tentadas
    voltar:
    if(tentativas > 0){
      printf("\n\nletras tentadas: ");
      for(i = 0; i < tentativas; i++){
        printf("%c", letras_tentadas[i]);
      }
    }

    
    printf("\n\nDigite uma letra: ");
    scanf(" %c", &letras_tentadas[tentativas]);

    //***PROBLEMA******
    //impede que o jogador tente a mesma letra duas vezes.
    /*if(tentativas > 0){
      for(i = 0; i <= tentativas; i++){
        if(letras_tentadas[i] == letras_tentadas[tentativas]){
          printf("Você já tentou a letra %c. Por favor, tente uma letra diferente.\n", letras_tentadas[tentativas]);
          goto voltar;
        }
      }
    }*/
    //Confere se foi inserido apenas um caractere
    if(letras_tentadas[tentativas + 1] != '1'){
      printf("Por favor, digite uma letra de cada vez.\n\n");
      goto voltar;
    }
    
    letras_tentadas[tentativas] = tolower(letras_tentadas[tentativas]);//transforma o input do usuario em lower case.

    for(i = 0; i < t && i < 20; i++){

      if(palavra[i] == letras_tentadas[tentativas]){
        copia_randwrd[i] = letras_tentadas[tentativas];
        for(i = 0; i < t; i++){
          printf("%c ", copia_randwrd[i]);
        }
      }
      //***PROBLEMA***
      else{
        erros++;
        //printf("A letra '%c' não faz parte da palavra secreta.\n", letras_tentadas[tentativas]);
        //printf("_ ");
      }
    }

    tentativas++;
    if(strcmp(copia_randwrd, palavra) == 0){
      acertou++;
    }

  }while(acertou != 1 || erros < 5); //***PROBLEMA***

  if(erros >= 5){
    printf("GAME OVER.\n\nA palavra era: ");
    for(i = 0; i < t; i++){
      printf("%c", palavra[i]);
    }
  }
  else if(acertou == 1){
    printf("Parabens, voce venceu!");
  }
}
