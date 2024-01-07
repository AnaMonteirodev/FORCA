#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "forca.h"
#include <ctype.h>

#define FACIL 1
#define MEDIO 2
#define DIFICIL 3
int nivel_dificuldade = 0;

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int qte_maxima_chutes;

int letraexiste(char letra) {

  for(int j = 0; j < strlen(palavrasecreta); j++) {
    if(letra == palavrasecreta[j]) {
      return 1;
    }
  }

  return 0;
}

int chuteserrados() {
  int erros = 0;

  for(int i = 0; i < chutesdados; i++) {

    if(!letraexiste(chutes[i])) {
      erros++;
    }
  }

  return erros;
}

int enforcou() {
  return chuteserrados() >= 5;
}

int ganhou() {
  for(int i = 0; i < strlen(palavrasecreta); i++) {
    if(!jachutou(palavrasecreta[i])) {
      return 0;
    }
  }

  return 1;
}


void abertura() {
  printf("/****************/\n");
  printf("/ Jogo de Forca */\n");
  printf("/****************/\n\n");
}

void chuta() {
  char chute;
  printf("Qual letra? ");
  scanf(" %c", &chute);

  if (!isupper(chute)) {
    printf("Por favor, digite uma letra maiúscula.\n");
    return;
  }

  if(letraexiste(chute)) {
    printf("Você acertou: a palavra tem a letra %c\n\n", chute);
  } else {
    printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
  }

  chutes[chutesdados] = chute;
  chutesdados++;
}

int jachutou(char letra) {
  int achou = 0;
  for(int j = 0; j < chutesdados; j++) {
    if(chutes[j] == letra) {
      achou = 1;
      break;
    }
  }

  return achou;
}

void desenhaforca() {

  int erros = chuteserrados();

  printf("  _______       \n");
  printf(" |/      |      \n");
  printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
  printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
  printf(" |       %c     \n", (erros>=2?'|':' '));
  printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
  printf(" |              \n");
  printf("_|___           \n");
  printf("\n\n");

  for(int i = 0; i < strlen(palavrasecreta); i++) {

    if(jachutou(palavrasecreta[i])) {
      printf("%c ", palavrasecreta[i]);
    } else {
      printf("_ ");
    }

  }
  printf("\n");

}

void escolhepalavra(){
  FILE* f;

  f = fopen("palavras.txt", "r");
  if(f == 0) {
    printf("Banco de dados de palavras não disponível\n\n");
    exit(1);
  }

  int qtddepalavras;
  fscanf(f, "%d", &qtddepalavras);

  srand(time(0));
  int randomico = rand() % qtddepalavras;

  for(int i = 0; i <= randomico; i++) {
    fscanf(f, "%s", palavrasecreta);
  }

  switch (nivel_dificuldade) {
      case FACIL:
        qte_maxima_chutes = 15; 
        break;
      case MEDIO:
        qte_maxima_chutes=10;
        break;
      case DIFICIL:
        qte_maxima_chutes=5;
        break;
      default:
        printf("Nível de dificuldade inválido.\n");
        exit(1);
    }

    fclose(f);
}
void adicionapalavra() {
  char quer;

  printf("Você deseja adicionar uma nova palavra no jogo (S/N)? ");
  scanf(" %c", &quer);

  if (quer == 'S') {
    char novapalavra[TAMANHO_PALAVRA];

    printf("Digite a nova palavra, em letras maiúsculas: ");
    scanf("%s", novapalavra);

    FILE* f;
    f = fopen("palavras.txt", "r+");
    if (f == 0) {
      printf("Banco de dados de palavras não disponível\n\n");
      exit(1);
    }

    int qtd;
    fscanf(f, "%d", &qtd);

    for (int i = 0; i < qtd; i++) {
      fscanf(f, "%s", palavrasecreta);
      if (strcmp(novapalavra, palavrasecreta) == 0) {
        printf("Esta palavra já existe no banco de dados.\n");
        fclose(f);
        return;
      }
    }

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd + 1);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }
}

int main() {
  int escolha_nivel;
  abertura();
  printf("Escolha o nível de dificuldade:\n");
  printf("1 - Fácil\n");
  printf("2 - Médio\n");
  printf("3 - Difícil\n");
  scanf("%d", &escolha_nivel);

  if (escolha_nivel < FACIL || escolha_nivel > DIFICIL) {
    printf("Escolha inválida. O jogo será encerrado.\n");
    return 1;
  }

  nivel_dificuldade = escolha_nivel;
  escolhepalavra();

  do {

    desenhaforca();
    chuta();

  } while (!ganhou() && !enforcou());

  if(ganhou()) {
    printf("\nParabéns, você ganhou!\n\n");

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

    adicionapalavra();
  } else {
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }
  char nome_usuario[50];
  printf("Digite seu nome: ");
  scanf("%s", nome_usuario);

  int pontuacao = (ganhou() ? qte_maxima_chutes - chutesdados : 0);
  
  FILE *arquivo_ranking = fopen("ranking.txt", "a");
  if (arquivo_ranking == NULL) {
      printf("Erro ao abrir o arquivo de ranking.\n");
  } else {
      fprintf(arquivo_ranking, "Nome: %s | Pontuação: %d\n", nome_usuario, (ganhou() ? 1 : 0));
      fclose(arquivo_ranking);
  }
}