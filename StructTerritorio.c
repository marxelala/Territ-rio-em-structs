#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    
    struct Territorio territorios[5];

    printf("=== CADASTRO DE TERRITORIOS ===\n\n");

  
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);

        
        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", territorios[i].nome); 

        
        printf("Digite a cor do exercito: ");
        scanf(" %[^\n]", territorios[i].cor);


        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); 
    }


    printf("=== DADOS DOS TERRITORIOS CADASTRADOS ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-------------------------------\n");
    }

    return 0;
}
