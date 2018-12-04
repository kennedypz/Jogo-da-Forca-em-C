//Jogo da forca proposto como atividade avaliativa do terceiro estágio da cadeira de Introdução à linguagem de programação, do curso de Ciência da Computação, segundo período, Unipê.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> //função tolower

/* Estrutra para armazenar a ficha do jogador*/
typedef struct cadastro{
  char nick[25]; //Nick do funcionario 
  short int score; //Pontuação do jogador
  struct cadastro * prox;
}player;

typedef struct cad_plvr{ //nivel de dificuldade das palavras
  char palavra[75];
  struct cad_plvr * prox;
}nv_palavra;

int aux;
char nick1[25], nick2[25], random_word[30], palavragm2[75];

void menu();
void menu2(char nick[25]);
void escolhepalavra();
void jogar(char *palavra);
void cadastrar();
player *lista();
void cad_palavra(char* palavra, int x);
void boneco(int x, int y);
void creditos();
void login(player * lista, char * nicklog);
void verificanick(player * lista, char * nicklog);
int verificaplayer2(player * lista, char * nicklog);
void verificapalavra(char *palavra);
void trofeu(char *winner);
void aumentascore(player * lista, char * nick, int score);
void salvaRanking(player * lista);
void ranking(player *lista);
player * liberaMemoriaUltimoElementoLista(player* lista);
void liberaMemoria(player * lista);

int main(){
  menu();
  return 0;
}

void menu(){
  int n = 1, i;
  char nick[25];
  player * lista1 = lista();
    
  while(n!=0) {
    printf ("        _                         _          __                      \n");
	printf ("       | |                       | |        / _|                     \n");              
	printf ("       | | ___   __ _  ___     __| | __ _  | |_ ___  _ __ ___ __ _   \n");
	printf ("   _   | |/ _ \\ / _` |/ _ \\   / _` |/ _` | |  _/ _ \\| '__/ __/ _` |  \n"); 
	printf ("  | |__| | (_) | (_| | (_) | | (_| | (_| | | || (_) | | | (_| (_| |  \n");
	printf ("   \\____/ \\___/ \\__, |\\___/   \\__,_|\\__,_| |_| \\___/|_|  \\___\\__,_|  \n");
	printf ("                 __/ |                                               \n"); 
	printf ("                |___/                                                \n");
    printf("\n\t\t\t\t\t\t\t1 - Cadastro\n\t\t\t\t\t\t\t2 - Entrar\n\t\t\t\t\t\t\t3 - Ranking\n\t\t\t\t\t\t\t4 - Creditos\n\t\t\t\t\t\t\t0 - Sair\n");
    scanf("%d", &n);
    
    switch(n){
      case 0:
        return;
        
      case 1:{
        printf("______________________________________________________\n");
        printf("|	               _           _                      |\n"); 
        printf("|                 | |         | |                     |\n"); 
        printf("|	  ___ __ _  __| | __ _ ___| |_ _ __ ___           |\n");
        printf("|	 / __/ _` |/ _` |/ _` / __| __| '__/ _ \\          |\n");
        printf("|	| (_| (_| | (_| | (_| \\__ | |_| | | (_) |         |\n");
        printf("|	 \\___\\__,_|\\__,_|\\__,_|___/\\__|_|  \\___/          |\n");                                     
        printf("|_____________________________________________________|\n\n");    
        cadastrar();
        break;
      }
               
      case 2:{
          printf("____________________________________\n");
          printf("|	 _             _               |\n");
        printf("|	| |           (_)              |\n");
        printf("|	| | ___   __ _ _ _ __          |\n");
        printf("|	| |/x x\\ / _` | | '_ \\         |\n");
        printf("|	| |  n  | (_| | | | | |        |\n");
        printf("|	|_|\\___/ \\__, |_|_| |_|        |\n");
              printf("|	          __/ |      	       |\n");    
            printf("|	         |___/      	       |\n");
        printf("____________________________________\n\n");
        do{
          printf("Nick: ");
          scanf("%s", nick);
          for(i = 0; i < strlen(nick); i++){
            nick1[i] = nick[i];
          }
          if(strlen(nick) > 25){
            printf("\n\nQuantidade maxima de caracteres excedida, tente novamente.\n\n");
          }
        }while(strlen(nick) > 25);
        login(lista1, nick);
        liberaMemoria(lista1);
        break;
      }
        
      case 3:{
        ranking(lista1);
        liberaMemoria(lista1);
        break;
      }
      
      case 4:{
        printf ("____________________________________________________\n");
        printf ("|        _____       __     _   _                  |\n");  
        printf ("|       / ____|     /_/    | (_) |                 |\n");   
        printf ("|      | |     _ __ ___  __| |_| |_ ___  ___       |\n"); 
        printf ("|      | |    | '__/ _ \\/ _` | | __/ _ \\/ __|      |\n");
        printf ("|      | |____| | |  __/ (_| | | || (_) \\__ \\      |\n");
        printf ("|       \\_____|_|  \\___|\\__,_|_|\\__\\___/|___/      |  \n");
        printf ("|__________________________________________________|\n\n");
        creditos();
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
  player score;
  char nick[25];
  int i;
  player * lista2 = lista();

  cadastros = fopen("ranking.txt", "a");
  
  if(!cadastros){
    printf("Não foi possivel acessar o banco para realizar o cadastro.\n\n");
    return;
  }

  else{
    do{
      printf("Informe seu nick(máximo 25 caracteres): ");
      scanf("%s", nick);

      if(strlen(nick) > 25){
        printf("\n\nQuantidade maxima de caracteres excedida, tente novamente.\n\n");
      }
      verificanick(lista2, nick);
    }while(strlen(nick) > 25);
    
    score.score = 0;
    
    printf("\nCadastro efetuado com sucesso!\n\n");

    fprintf(cadastros, "%s", nick);
    fprintf(cadastros, "%c", ',');
    fprintf(cadastros, "%d", score.score);
    fprintf(cadastros, "%c", '\n');
  }
  fclose(cadastros);
  for(i = 0; i < strlen(nick); i++){
    nick1[i] = nick[i];
  }
  liberaMemoria(lista2);
  menu2(nick);
}

//Listar todos os jogadores
player *lista(){
  FILE *rkg;
  int i;
  char linha[40];

  rkg = fopen("ranking.txt", "r");

  if(!rkg){
    printf("Não foi possível acessar o arquivo com o ranking.8\n\n");
    return 0;
  }

  player * lista = (player*) malloc (sizeof(player));

  if(!lista){
    return 0;
  }

  fgets(linha, 40, rkg);
  
  if(feof(rkg)){
    printf("Ainda não há dados no sistema.");
    return 0;
  }

  char *nome;
  nome = strtok(linha, ",");
  strcpy(lista->nick, nome);
    
  char * s_score = strtok(NULL,",");
    
  lista->score = atoi(s_score);

  lista->prox = 0;

  fgets(linha, 60, rkg);
  
  player * anterior = lista;
  
  while(!feof(rkg)) {
    player * novo = (player*) malloc (sizeof(player));
              
    if(!novo){
      return 0;
    }
    
    strcpy(novo->nick,strtok(linha,","));
    novo->score = atoi(strtok(NULL,","));
    novo->prox = 0;
    anterior->prox = novo;
    anterior = novo;
    fgets(linha, 60, rkg);
  }
  fclose(rkg);
  return lista;
}


//Cadastrar novas palavras
void cad_palavra(char *palavra, int x){
  int op;
  FILE* palavras = NULL;
  nv_palavra inp_plvr[75];
  
  palavras = fopen("palavras.txt", "a+");

  if(!palavras){
    printf("Não foi possível acessar o banco de palavras.5");
  }

  else{
    do{
      if(x == 1){
        printf("Informe a palavra que deseja adicionar ao banco de palavras: ");
        scanf(" %[^\t\n]s", palavra);
        fprintf(palavras, "%s", palavra);
        fprintf(palavras, "%c", '\n');
    
        printf("Deseja adicionar mais palavras?\n\n1 - Sim\n2 - Nao\n");
        scanf("%d", &op);
      }
      else{
        fprintf(palavras, "%s", palavra);
        fprintf(palavras, "%c", '\n');
      }
    } while(op == 1);
    fclose(palavras);
  }
}

void boneco(int x, int y){
  int i;
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
      printf("     (   -  )\n");     
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
      printf("     (   n  )\n");     
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
      printf("     (   n  )\n");     
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

      printf("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n");
      printf("██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n");
      printf("██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n");
      printf("██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n");
      printf("███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n");
      printf("██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n");
      printf("██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n");
      printf("██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n");
      printf("███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n");
      printf("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n\n");
      printf("A palavra secreta era: ");
      if(y == 1){
        for(i = 0; i < strlen(random_word); i++){
          printf("%c", random_word[i]);
        }
      }
      else{
        for(i = 0; i < strlen(palavragm2); i++){
          printf("%c", palavragm2[i]);
        }
      }
      printf("\n\nPressione qualquer tecla para voltar ao menu\n\n");
      menu();
      break;    
    }
  }
}

void escolhepalavra() {
	FILE* f;
  int qtddepalavras, randomico, i;

	f = fopen("palavras.txt", "r");

	if(!f) {
		printf("Não foi possivel acessar o banco de palavras.2\n\n");
    return;
	}

	while(fgets(random_word, 75, f) != NULL){
    qtddepalavras++;
  }

	srand(time(NULL));
  rand();
	randomico = rand() % qtddepalavras;

  fseek(f, 0, SEEK_SET);
	for(i = 0; i <= randomico; i++) {
		fscanf(f, "%s", random_word);
	}
  
  printf("(escolhepalavra) Quantidade de palavras: %d\npalavra 1: %s\n\n", qtddepalavras, random_word);

	fclose(f);
}

void jogar(char *palavra1){
  int t, i, erros = 0, erros2 = 0, char_especial1 = 0, acertou = 0, tentativas = 0, cht = 0, turno = 1;
  char letras_tentadas1[20], chute[30], gamemode;
  player * lista3 = lista();

  printf("Informe o nick do segundo jogador: ");
  scanf(" %s", nick2);
  verificaplayer2(lista3, nick2);

  printf("Como vocês desejam jogar?\n\n1 - Ambos tentando adivinhar a mesma palavra\n2 - Um escolhe a palavra e o outro tenta adivinhar\n");
  scanf(" %c", &gamemode);

  if(gamemode == '1'){
  
  escolhepalavra();
  //Esse for mede a quantidade de caracteres presentes na palavra a ser adivinhada
  for(t = 0; palavra1[t] != '\0'; t++){
    if(palavra1[t] == '-' || palavra1[t] == ' '){
      char_especial1++; //esse contador vai ser usado para subtrair os caracteres especiais para que fiquem visiveis para o usuario
    }
  }

  char* copia_randwrd = ((char*) malloc(strlen(palavra1 - 1) * sizeof(char)));//alocação dinamica para o que vai ser mostrado ao usuario
  if(!copia_randwrd){
    return;
  }

  //printa a palavras com as letras substituidas por underlines e mostra espaços e hífens
  for(i = 0; palavra1[i] != '\0'; i++){
    if(palavra1[i] == '-'){
      copia_randwrd[i] = '-';
    }
    else if(palavra1[i] == ' '){
      copia_randwrd[i] = ' ';
    }
    else{
      copia_randwrd[i] = '_';
    }
  } 

  //preenchi o vetor com espaços vazios para facilitar a validação de um único caractere
  for(i = 0; i < 20; i++){
    letras_tentadas1[i] = '1';
  }
    
  do{

    if((turno % 2) != 0){
      printf("\nTurno do jogador: %s\n", nick1);
    }
    else{
      printf("\nTurno do jogador: %s\n", nick2);
    }
    voltar:
    printf("A palavra possui %d letras\n\n", (t - char_especial1));

    for(i = 0; i < t; i++){
      printf("%c ", copia_randwrd[i]);
    }
    
    if(tentativas > 0){
      printf("\n\nletras tentadas: ");
      for(i = 0; i < tentativas; i++){
        printf("%c ", letras_tentadas1[i]);
      }
      printf("\nDigite 1 para adivinhar a palavra toda.(Se voce errar, perdera o jogo)");
    }
      
    printf("\n\nDigite uma letra: ");
    scanf(" %c", &letras_tentadas1[tentativas]);
    letras_tentadas1[tentativas] = tolower(letras_tentadas1[tentativas]);//transforma o input do usuario em lower case.

    if(letras_tentadas1[tentativas] == '1'){
      printf("Digite a palavra completa: ");
      scanf("%s", chute);

      if(strcmp(chute, palavra1) == 0){
        if((turno % 2) == 0){
          //trofeu(nick2);
          int score = 1;
          aumentascore(lista3, nick2, score);
          salvaRanking(lista3);
          acertou = 1;
          break;
        }
        else{
          //trofeu(nick1);
          int score = 1;
          aumentascore(lista3, nick1, score);
          salvaRanking(lista3);
          acertou = 1;
          break;
        }
      }
      else{
        erros = 5;
        boneco(erros,1);
      }
    }

    //impede que o jogador tente a mesma letra duas vezes.
    if(tentativas > 0){
      for(i = 0; i <= tentativas; i++){
        if(letras_tentadas1[i - 1] == letras_tentadas1[tentativas]){
          printf("Você já tentou a letra %c. Por favor, tente uma letra diferente.\n", letras_tentadas1[tentativas]);
          goto voltar;
        }
      }
    }
    //Confere se foi inserido apenas um caractere
    if(letras_tentadas1[tentativas + 1] != '1'){
      printf("Por favor, digite uma letra de cada vez.\n\n");
      goto voltar;
    }

    int controle = 0;
    
    for(i = 0; i < t; i++){
      if(letras_tentadas1[tentativas] != '1'){
        if(letras_tentadas1[tentativas] == palavra1[i]){
          copia_randwrd[i] = letras_tentadas1[tentativas];
          for(i = 0; i < t; i++){
            printf("%c ", copia_randwrd[i]);
          }
          controle = 1;
        }
      }
    }

    if(controle == 0){
      if((turno % 2) == 0){
        erros++;
      }
      else{
        erros2++;
      }

      printf("A letra '%c' não faz parte da palavra secreta.\n", letras_tentadas1[tentativas]);

      for(i = 0; i < t; i++){
        printf("%c ", copia_randwrd[i]);
      }
    }

    if((turno % 2) == 0){
      boneco(erros,1);
    }
    else{
      boneco(erros2,1);
    }
    
    //printf("copia: %s\nrandom_word: %s\nerros: %d \nturno: %d\npalavra1: %s\n\n", copia_randwrd, random_word, erros, turno, palavra1);

    tentativas++;

    if(strcmp(copia_randwrd, palavra1) == 0){
      acertou++;
        if((turno % 2) == 0){
        //trofeu(nick2);
        int score = 1;
        aumentascore(lista3, nick2, score);
        salvaRanking(lista3);
      }
      else{
        //trofeu(nick1);
        int score = 1;
        aumentascore(lista3, nick1, score);
        salvaRanking(lista3);
      }
    }

    if(acertou != 1){
      turno++;
    }
  }while(acertou == 0); 
  
  if(acertou == 1){
    if((turno % 2) == 0){
      trofeu(nick2);
      int score = 1;
      aumentascore(lista3, nick2, score);
      salvaRanking(lista3);
      menu2(nick1);
    }
    else{
      trofeu(nick1);
      int score = 1;
      aumentascore(lista3, nick1, score);
      salvaRanking(lista3);
      menu2(nick1);
    }
  }
  liberaMemoria(lista3);
  }
  else if(gamemode == '2'){
    printf("O jogador %s irá escolher uma palavra para o jogador %s tentar adivinhar.\n\nInforme a palavra: ", nick1, nick2);
    scanf("%s", palavragm2);
    verificapalavra(palavragm2);

    for(t = 0; palavragm2[t] != '\0'; t++){
      if(palavragm2[t] == '-' || palavragm2[t] == ' '){
        char_especial1++; //esse contador vai ser usado para subtrair os caracteres especiais para que fiquem visiveis para o usuario
      }
    }

    char* copia_randwrd = ((char*) malloc(strlen(palavragm2) * sizeof(char)));//alocação dinamica para o que vai ser mostrado ao usuario
    if(!copia_randwrd){
      return;
    }
    
    //printa a palavras com as letras substituidas por underlines e mostra espaços e hífens
    for(i = 0; palavragm2[i] != '\0'; i++){
      if(palavragm2[i] == '-'){
        copia_randwrd[i] = '-';
      }
      else if(palavragm2[i] == ' '){
        copia_randwrd[i] = ' ';
      }
      else{
        copia_randwrd[i] = '_';
      }
    } 

    //preenchi o vetor com espaços vazios para facilitar a validação de um único caractere
    for(i = 0; i < 20; i++){
      letras_tentadas1[i] = '1';
    }
      
    do{
      voltar1:
      printf("A palavra possui %d letras\n\n", (t - char_especial1));

      for(i = 0; i < t; i++){
        printf("%c ", copia_randwrd[i]);
      }
      
      if(tentativas > 0){
        printf("\n\nletras tentadas: ");
        for(i = 0; i < tentativas; i++){
          printf("%c ", letras_tentadas1[i]);
        }
        printf("\nDigite 1 para adivinhar a palavra toda.(Se voce errar, perdera o jogo)");
      }
        
      printf("\n\nDigite uma letra: ");
      scanf(" %c", &letras_tentadas1[tentativas]);
      letras_tentadas1[tentativas] = tolower(letras_tentadas1[tentativas]);//transforma o input do usuario em lower case.

      if(letras_tentadas1[tentativas] == '1'){
        printf("Digite a palavra completa: ");
        scanf("%s", chute);
        if(strcmp(chute, palavragm2) == 0){
          acertou = 1;
          break;
        }
        else{
          erros = 5;
          boneco(erros,0);
        }
        break;
      }

      //impede que o jogador tente a mesma letra duas vezes.
      if(tentativas > 0){
        for(i = 0; i <= tentativas; i++){
          if(letras_tentadas1[i - 1] == letras_tentadas1[tentativas]){
            printf("Você já tentou a letra %c. Por favor, tente uma letra diferente.\n", letras_tentadas1[tentativas]);
            goto voltar1;
          }
        }
      }
      //Confere se foi inserido apenas um caractere
      if(letras_tentadas1[tentativas + 1] != '1'){
        printf("Por favor, digite uma letra de cada vez.\n\n");
        goto voltar1;
      }

      int controle = 0;
      
      for(i = 0; i < t; i++){
        if(letras_tentadas1[tentativas] == palavragm2[i]){
          copia_randwrd[i] = letras_tentadas1[tentativas];
          for(i = 0; i < t; i++){
            printf("%c ", copia_randwrd[i]);
          }
          controle = 1;
        }
      }

      if(controle == 0){
        erros++;
        if(letras_tentadas1[tentativas] != '1'){
          printf("A letra '%c' não faz parte da palavra secreta.\n", letras_tentadas1[tentativas]);
          
        }
        for(i = 0; i < t; i++){
          printf("%c ", copia_randwrd[i]);
        }
      }
      
      boneco(erros,0);
      
      //printf("copia: %s\nrandom_word: %s\nerros: %d \nturno: %d\npalavragm2: %s\n\n", copia_randwrd, random_word, erros, turno, palavragm2);

      tentativas++;

      if(strcmp(copia_randwrd, palavragm2) == 0){
        acertou++;
      }
      
    }while(acertou == 0); 
    
    if(acertou == 1){
      trofeu(nick2);
      int score = 1;
      aumentascore(lista3, nick2, score);
      salvaRanking(lista3);
    }
    liberaMemoria(lista3);
  }
}

void creditos(){
  printf("\n\n***Jogo da forca em C***\n\nDesenvolvido por:\nLucas\nNina\nPaulo\nTarcisio\n\n");
}

void menu2(char nick[25]){
  int n = 1;
  char palavrainpt[75];
  player *listax = lista();
    
  while(n!=0) {
    printf("Bem-vindo, %s!\n\n1 - Jogar\n2 - Cadastrar palavras\n3 - Ranking\n4 - Creditos\n0 - Sair\n", nick);
    scanf("%d", &n);
    
    switch(n){
      case 0:
        return;
        
      case 1:{
        jogar(random_word);
        break;
      }
               
      case 2:{
        printf("____________________________________________________________\n");
        printf("|       _____          _           _                       |\n");
        printf("|      / ____|        | |         | |                      |\n");
        printf("|     | |     __ _  __| | __ _ ___| |_ _ __ __ _ _ __      |\n");
        printf("|     | |    / _` |/ _` |/ _` / __| __| '__/ _` | '__|     |\n");
        printf("|     | |___| (_| | (_| | (_| \\__ \\ |_| | | (_| | |        |\n");
        printf("|      \\_____\\__,_|\\__,_|\\__,_|___/\\__|_|  \\__,_|_|        |\n");
        printf("|                      _                                   |\n");   
        printf("|                     | |                                  |\n");    
        printf("|          ____   ___ | | __ ___   ___ __ __ _ ___         |\n");    
        printf("|         | '_ \\ / _` | |/ _` \\ \\ / / '__/ _` / __|        |\n");   
        printf("|         | |_) | (_| | | (_| |\\ V /| | | (_| \\__ \\        |\n");    
        printf("|         | .__/ \\__,_|_|\\__,_| \\_/ |_|  \\__,_|___/        |\n");   
        printf("|         | |                                              |\n");   
        printf("|         |_|                                              |\n");
        printf("|__________________________________________________________|\n\n");
        cad_palavra(palavrainpt, 1);
        break;
      }
        
      case 3:{
        ranking(listax);
        liberaMemoria(listax);
        break;
      }
      
      case 4:{
        printf ("____________________________________________________\n");
        printf ("|        _____       __     _   _                  |\n");  
        printf ("|       / ____|     /_/    | (_) |                 |\n");   
        printf ("|      | |     _ __ ___  __| |_| |_ ___  ___       |\n"); 
        printf ("|      | |    | '__/ _ \\/ _` | | __/ _ \\/ __|      |\n");
        printf ("|      | |____| | |  __/ (_| | | || (_) \\__ \\      |\n");
        printf ("|       \\_____|_|  \\___|\\__,_|_|\\__\\___/|___/      |  \n");
        printf ("|__________________________________________________|\n\n");
        creditos();
        break;
      }

      default:
        printf("Opcao invalida!\n\n");                       
    }
  }
}

//Faz o login do usuário
void login(player * lista, char * nicklog){
  int i, cont = 0;
  FILE *rkg;
  player *aux = lista;
  
  rkg = fopen("ranking.txt", "r");

  if(!rkg){
    printf("Não foi possível acessar o arquivo com o ranking.3");
    return;
  }

  while(aux){
    if(strcmp(aux->nick, nicklog) == 0) {
      menu2(nicklog);
      break;
    }
    else{
      cont++;
    }
    aux = aux-> prox;
  }
  if(cont != 0){
    printf("Jogador não encontrado.\n\n");
  }

  fclose(rkg);
}
//Verifica se o nick já foi cadastrado
void verificanick(player * lista, char * nicklog){
  int i;
  FILE *rkg;
  player *aux = lista;
  
  rkg = fopen("ranking.txt", "r");

  if(!rkg){
    printf("Não foi possível acessar o arquivo com o ranking.2");
    return;
  }

  while(aux){
    if(strcmp(aux->nick, nicklog) == 0) {
      printf("Nick já cadastrado, tente um nick diferente.\n\n");
      cadastrar();
    }
    aux = aux-> prox;
  }
  fclose(rkg);
}

int verificaplayer2(player * lista, char * nicklog){
  int i, cont = 0, qtddeplayers = 0;
  FILE *rkg;
  player *aux = lista;
  char nomes[75];
  
  rkg = fopen("ranking.txt", "r");

  if(!rkg){
    printf("Não foi possível acessar o arquivo com o ranking.1");
    return 0;
  }

  while(aux){
    if(strcmp(nick1, nicklog) == 0){
      printf("Voce nao pode jogar contra voce mesmo. Por favor, informe outro nick.\n\n");
      jogar(random_word);
    }
    if(strcmp(aux->nick, nicklog) == 0){
      printf("\nO segundo jogador é: %s\n", nicklog);
    }
    else{
      cont++;
    }
    aux = aux-> prox;
  }
  
  while(fgets(nomes, 75, rkg) != NULL){
    qtddeplayers++;
  }

  if(cont >= qtddeplayers){
    printf("\nSegundo jogador não cadastrado. Tente um jogador diferente ou cadastre o nick tentado.\n");
  }
  fclose(rkg);
  return 1;
}

void verificapalavra(char *palavra){
  FILE *plv;
  int i, cont = 0, qtddlinhas;
  char plvrs[75];

  plv = fopen("palavras.txt", "r");

  if(!plv){
  printf("Não foi possível acessar o arquivo com as palavras.1");
  return;
  }

  while(fgets(plvrs, 75, plv) != NULL){
    qtddlinhas++;
    if(strcmp(plvrs, palavra) != 0){
      cont++;
    }
  }
  if(cont >= qtddlinhas){
    cad_palavra(palavra, 0);
  }
  fclose(plv);
}

void trofeu(char * winner){
  printf("%s venceu!\n\n", winner);
  printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");
}

void aumentascore(player * lista, char * nick, int score){
  player * aux = lista;

  while (aux) {
    if(strcmp(aux->nick, nick) == 0) {
      aux -> score = score;
      return; 
    }
    aux = aux->prox;
  }
}

void salvaRanking(player * lista){
  FILE * rkg = fopen("ranking.txt", "w");
  player * aux = lista;

  while(aux){
    fprintf(rkg, "%s,%d\n", aux->nick, aux->score);
    aux = aux->prox;
  }

  fclose(rkg);
}

void ranking(player *lista){
  int i, j;
  player * aux = lista;

  printf("\nPos|    nick  -   score\n");
  for(i = 0; aux; i++, aux = aux -> prox){
    printf(" %d | %s - %d\n", (i + 1), aux->nick, aux->score);
  }
}

player * liberaMemoriaUltimoElementoLista(player* lista){
  player * anterior = lista;

  while (anterior->prox->prox){ 
    anterior = anterior->prox; 
    //aux = aux->prox; //itera
  }

  free(anterior->prox);
  anterior->prox = 0;
  return lista;
}

void liberaMemoria(player * lista){
  player * ultimo = lista;
  while(ultimo->prox)
  ultimo = liberaMemoriaUltimoElementoLista(lista);
  free(lista);
}
