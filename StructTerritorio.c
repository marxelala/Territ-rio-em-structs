#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inserirItem(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome do item: ");
    scanf("%s", mochila[*contador].nome);
    printf("Tipo do item: ");
    scanf("%s", mochila[*contador].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[*contador].quantidade);
    (*contador)++;
    printf("Item adicionado com sucesso!\n");
}

void listarItens(Item mochila[], int contador) {
    if (contador == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\nItens na mochila:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void removerItem(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);
    int encontrado = 0;
    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *contador - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*contador)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) printf("Item nao encontrado.\n");
}

void buscarItem(Item mochila[], int contador) {
    if (contador == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    char nome[30];
    printf("Nome do item a buscar: ");
    scanf("%s", nome);
    int encontrado = 0;
    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("Item nao encontrado.\n");
}

int main() {
    Item mochila[MAX_ITENS];
    int contador = 0, opcao;
    do {
        printf("\n--- Sistema de Inventario ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: inserirItem(mochila, &contador); break;
            case 2: removerItem(mochila, &contador); break;
            case 3: listarItens(mochila, contador); break;
            case 4: buscarItem(mochila, contador); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
