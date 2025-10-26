#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10 
#define TAM_NOME 50
#define TAM_TIPO 30 

struct Item {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
};
//criei uma funcao para avisar quando a mochila estiver cheia 
void adicionarItem(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens >= MAX_ITENS) {
        printf("Mochila cheia!!!, não é possivel adicionar mais itens \n")
        return;
}

    printf("\n--- ADICIONAR ITEM ---\n ");
    printf("Nome do item: ");
    scanf("%s", mochila[*quantidadeItens].nome);

    printf("Tipo do item: ");
    scanf("%s", mochila[*quantidadeItens].tipo);

    printf("Quantidade: ");
    scanf("%d", mochila[*quantidadeItens].quantidade);

    (*quantidadeItens)++;
    printf("Item adicionado com sucesso\n");
}
// funcao para remover item

void removerItem(struct Item mochila[], int *quantidadeItens) {
    if(*quantidadeItens == 0) {
        printf("Mochila vazia !!! Não há itens para remover. \n");
        return;
    }
    char nomeRemover[50];
    printf("\n --- REMOVER ITEM ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", nomeRemover);

    int encontrado = 0;
    for (int i = 0; i < *quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0 ){
            encontrado = 1;
            // funcao que move todos os itens uma posicao para frente
            for( int j = i; j < *quantidadeItens - 1; j++) {
                mochila[j] - mochila[j + 1];
            }
            (*quantidadeItens) -- ;
            printf("Item '%s' removido com sucesso !\n", nomeRemover);
            break;
        }
    }
    if (!encontrado) {
        printf(" Item '%s' não encontrado !\n", nomeRemover);
    }
}

//funcao para listar os itens
void listarItens(struct Item mochila[], int quantidadeItens) {
    printf("\n ITENS NA MOCHILA\n");
    printf("| %-20s | %15s | %10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("+----------------------------------------------------+\n");

    if (quantidadeItens == 0) {
        printf("| %-45s |\n", "Mochila vazia!");
    }  else {
        for (int i = 0; i < quantidadeItens; i ++) {
            printf("| %-20s | %-15s | %-10s |\n",
                    mochila[i].nome,
                    mochila[i].tipo,
                    mochila[i].quantidade);
        }
    }
    printf("+-------------------------------------------------+\n");
    printf("Total de itens: %d/%d\n", quantidadeItens, MAX_ITENS);
}

// funcao principal 

int main(){
    struct Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;

    printf("BEM-VINDO AO INVENTARIO DO FREE FIRE!");
    
    do {
        printf("\n === MENU PRINCIPAL === \n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                adicionarItem(mochila, &quantidadeItens);
                break;
            case 2:
                removerItem(mochila, &quantidadeItens);
                break;
            case 3:
                listarItens(mochila, quantidadeItens);
                break;
            case 0:
                print("Saindo do programa... Até logo!\n");
                break;
            default:
                printf("Opcao invalida! tente novamente.\n");
        }
    } 
    while (opcao != 0);
    return 0;
}