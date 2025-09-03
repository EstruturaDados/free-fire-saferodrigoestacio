#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor global que simula a mochila
Item mochila[MAX_ITENS];
int totalItens = 0; // Controla quantos itens estão cadastrados

// ------------------------- FUNÇÕES ----------------------------

// Função para inserir item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome); // ler string com espaços
    printf("Digite o tipo do item (arma, municao, cura, ferramenta): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("\n✅ Item adicionado com sucesso!\n");
}

// Função para remover item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️ Mochila vazia! Não há itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n❌ Item não encontrado.\n");
        return;
    }

    // Shift dos itens para remover o escolhido
    for (int i = encontrado; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;

    printf("\n🗑️ Item removido com sucesso!\n");
}

// Função para listar todos os itens da mochila
void listarItens() {
    if (totalItens == 0) {
        printf("\n📦 Mochila está vazia!\n");
        return;
    }

    printf("\n📋 Itens da mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial por nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n📦 Mochila está vazia!\n");
        return;
    }

    char nomeBuscar[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBuscar);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\n🔎 Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item não encontrado na mochila.\n");
}

// ------------------------- PROGRAMA PRINCIPAL ----------------------------
int main() {
    int opcao;

    do {
        printf("\n==============================\n");
        printf("🎒 SISTEMA DE INVENTÁRIO 🎮\n");
        printf("==============================\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("\n👋 Saindo do sistema...\n"); break;
            default: printf("\n⚠️ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
