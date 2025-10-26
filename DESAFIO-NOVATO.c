#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define MAX_UNIDADES 10

struct Item {
    char nome[50];
    char tipo[30];
    int quantidade;
};

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para calcular o total de unidades
int calcularTotalUnidades(struct Item mochila[], int quantidadeItens) {
    int total = 0;
    for (int i = 0; i < quantidadeItens; i++) {
        total += mochila[i].quantidade;
    }
    return total;
}

void adicionarItem(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens >= MAX_ITENS) {
        printf(" Mochila cheia! Não é possível adicionar mais TIPOS de itens.\n");
        return;
    }
    
    // Verificar se não ultrapassa o limite de UNIDADES
    int totalAtual = calcularTotalUnidades(mochila, *quantidadeItens);
    if (totalAtual >= MAX_UNIDADES) {
        printf(" Mochila cheia! Limite de %d unidades atingido.\n", MAX_UNIDADES);
        return;
    }
    
    printf("\n ADICIONAR ITEM\n");
    
    printf("Nome do item: ");
    scanf("%49s", mochila[*quantidadeItens].nome);
    limparBuffer();
    
    printf("Tipo do item: ");
    scanf("%29s", mochila[*quantidadeItens].tipo);
    limparBuffer();
    
    printf("Quantidade de unidades (max %d disponivel): ", MAX_UNIDADES - totalAtual);
    
    int resultadoScanf;
    do {
        resultadoScanf = scanf("%d", &mochila[*quantidadeItens].quantidade);
        limparBuffer();
        
        if (resultadoScanf != 1 || mochila[*quantidadeItens].quantidade <= 0) {
            printf("❌ Quantidade inválida! Digite um número positivo: ");
        } else if (totalAtual + mochila[*quantidadeItens].quantidade > MAX_UNIDADES) {
            printf("❌ Quantidade excede o limite! Máx %d disponível: ", MAX_UNIDADES - totalAtual);
            resultadoScanf = 0; // Força repetir
        }
    } while (resultadoScanf != 1 || mochila[*quantidadeItens].quantidade <= 0);
    
    (*quantidadeItens)++;
    printf(" Item adicionado com sucesso!\n");
}

void listarItens(struct Item mochila[], int quantidadeItens) {
    int totalUnidades = calcularTotalUnidades(mochila, quantidadeItens);
    
    printf("\n ITENS NA MOCHILA\n");
    printf("+-------------------------------------------------+\n");
    printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("+-------------------------------------------------+\n");
    
    if (quantidadeItens == 0) {
        printf("| %-45s |\n", "Mochila vazia!");
    } else {
        for (int i = 0; i < quantidadeItens; i++) {
            printf("| %-20s | %-15s | %-10d |\n", 
                   mochila[i].nome, 
                   mochila[i].tipo, 
                   mochila[i].quantidade);
        }
    }
    printf("+-------------------------------------------------+\n");
    printf("Tipos de itens: %d/%d\n", quantidadeItens, MAX_ITENS);
    printf("Total de unidades: %d/%d\n", totalUnidades, MAX_UNIDADES);
}

void removerItem(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens == 0) {
        printf("❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    char nomeRemover[50];
    printf("\n REMOVER ITEM\n");
    printf("Digite o nome do item a ser removido: ");
    scanf("%49s", nomeRemover);
    limparBuffer();
    
    int encontrado = 0;
    for (int i = 0; i < *quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            printf(" Removendo %d unidades de '%s'\n", mochila[i].quantidade, nomeRemover);
            
            for (int j = i; j < *quantidadeItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*quantidadeItens)--;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item '%s' não encontrado na mochila.\n", nomeRemover);
    }
}

int main() {
    struct Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;
    
    printf(" BEM-VINDO AO INVENTARIO  \n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf(" Entrada invalida! Digite um número.\n");
            continue;
        }
        limparBuffer();
        
        switch(opcao) {
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
                printf(" Saindo do programa...\n");
                break;
            default:
                printf(" Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
    
    return 0;
}
