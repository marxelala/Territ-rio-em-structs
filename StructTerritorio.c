#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n--- Territorios Cadastrados ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nNao e possivel atacar um territorio da mesma cor!\n");
        return;
    }
    if (atacante->tropas < 2) {
        printf("\nO atacante precisa ter pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nAtaque iniciado!\n");
    printf("%s (atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("\nO defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}

void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

int verificarMissao(char *missao, Territorio *mapa, int tamanho, char *corJogador) {
    int conquistas = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) conquistas++;
    }

    if (strstr(missao, "3 territorios") && conquistas >= 3) return 1;
    if (strstr(missao, "5 territorios") && conquistas >= 5) return 1;
    if (strstr(missao, "vermelha")) {
        int existe = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) existe = 1;
        }
        if (!existe) return 1;
    }
    return 0;
}

void liberarMemoria(Territorio *mapa, char *missao1, char *missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}

int main() {
    srand(time(NULL));
    int qtd, opcao;
    Territorio *mapa;
    char *missaoJogador1, *missaoJogador2;

    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Conquistar 5 territorios",
        "Eliminar todas as tropas da cor vermelha",
        "Manter pelo menos 2 territorios com mais de 10 tropas",
        "Dominar metade do mapa"
    };
    int totalMissoes = 5;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro na alocacao de memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    missaoJogador1 = (char *)malloc(100 * sizeof(char));
    missaoJogador2 = (char *)malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\nMissao do Jogador 1: %s\n", missaoJogador1);
    printf("Missao do Jogador 2: %s\n", missaoJogador2);

    do {
        printf("\n--- Menu WAR ---\n");
        printf("1. Exibir territorios\n");
        printf("2. Atacar\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirTerritorios(mapa, qtd);
        } 
        else if (opcao == 2) {
            exibirTerritorios(mapa, qtd);
            int a, d;
            printf("\nEscolha o numero do territorio atacante: ");
            scanf("%d", &a);
            printf("Escolha o numero do territorio defensor: ");
            scanf("%d", &d);
            if (a < 1 || a > qtd || d < 1 || d > qtd || a == d) {
                printf("Escolha invalida!\n");
            } else {
                atacar(&mapa[a - 1], &mapa[d - 1]);
                exibirTerritorios(mapa, qtd);

                if (verificarMissao(missaoJogador1, mapa, qtd, mapa[a - 1].cor)) {
                    printf("\nJogador 1 cumpriu sua missao e venceu o jogo!\n");
                    break;
                }
                if (verificarMissao(missaoJogador2, mapa, qtd, mapa[d - 1].cor)) {
                    printf("\nJogador 2 cumpriu sua missao e venceu o jogo!\n");
                    break;
                }
            }
        }
        else if (opcao == 0) {
            printf("\nEncerrando o jogo...\n");
        } 
        else {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    return 0;
}
