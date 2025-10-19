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

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));
    int qtd, opcao;
    Territorio *mapa;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro na alocacao de memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

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
            }
        }
        else if (opcao == 0) {
            printf("\nEncerrando o jogo...\n");
        } 
        else {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
