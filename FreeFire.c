#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// STRUCTS
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

//  VARIÁVEIS GLOBAIS
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

No* mochilaLista = NULL; // Ponteiro para a cabeça da lista encadeada

//  FUNÇÕES DE APOIO 
void mostrarItem(Item item) {
    printf("Nome: %s | Tipo: %s | Quantidade: %d\n", item.nome, item.tipo, item.quantidade);
}

//  VERSÃO COM VETOR 
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\n Mochila (vetor) cheia!\n");
        return;
    }
    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItensVetor++] = novo;
    printf("\n Item adicionado ao vetor!\n");
}

void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("\n Mochila (vetor) vazia!\n");
        return;
    }
    char nome[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    int encontrado = -1;
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n Item não encontrado no vetor!\n");
        return;
    }

    for (int i = encontrado; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    totalItensVetor--;
    printf("\n Item removido do vetor!\n");
}

void listarItensVetor() {
    if (totalItensVetor == 0) {
        printf("\n Mochila (vetor) está vazia!\n");
        return;
    }
    printf("\n Itens da mochila (vetor):\n");
    for (int i = 0; i < totalItensVetor; i++) {
        mostrarItem(mochilaVetor[i]);
    }
}

int buscarSequencialVetor(char nome[]) {
    int comparacoes = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\n Encontrado (sequencial, vetor): ");
            mostrarItem(mochilaVetor[i]);
            printf("Comparações realizadas: %d\n", comparacoes);
            return i;
        }
    }
    printf("\n Item não encontrado (sequencial, vetor).\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    return -1;
}

// Ordenação por nome (Bubble Sort)
void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\n Vetor ordenado por nome!\n");
}

// Busca binária (somente após ordenar)
int buscarBinariaVetor(char nome[]) {
    int inicio = 0, fim = totalItensVetor - 1, meio;
    int comparacoes = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) {
            printf("\n Encontrado (binária, vetor): ");
            mostrarItem(mochilaVetor[meio]);
            printf("Comparações realizadas: %d\n", comparacoes);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\n Item não encontrado (binária, vetor).\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    return -1;
}

//  VERSÃO COM LISTA ENCADEADA 
void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("\nErro de alocação de memória!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("\n Item adicionado à lista encadeada!\n");
}

void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("\n Mochila (lista) vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\n Item não encontrado na lista!\n");
        return;
    }

    if (anterior == NULL) {
        mochilaLista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\n Item removido da lista encadeada!\n");
}

void listarItensLista() {
    if (mochilaLista == NULL) {
        printf("\n Mochila (lista) está vazia!\n");
        return;
    }
    printf("\n Itens da mochila (lista encadeada):\n");
    No* atual = mochilaLista;
    while (atual != NULL) {
        mostrarItem(atual->dados);
        atual = atual->proximo;
    }
}

void buscarSequencialLista(char nome[]) {
    int comparacoes = 0;
    No* atual = mochilaLista;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\n Encontrado (sequencial, lista): ");
            mostrarItem(atual->dados);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("\n Item não encontrado (sequencial, lista).\n");
    printf("Comparações realizadas: %d\n", comparacoes);
}

//  PROGRAMA PRINCIPAL 
int main() {
    int opcao, estrutura;
    char nomeBusca[30];

    do {
        printf("\n==============================\n");
        printf(" SISTEMA DE INVENTÁRIO\n");
        printf("==============================\n");
        printf("Escolha a estrutura:\n");
        printf("1 - Vetor\n");
        printf("2 - Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &estrutura);

        if (estrutura == 0) break;

        do {
            printf("\n--- MENU (estrutura %s) ---\n",
                   estrutura == 1 ? "Vetor" : "Lista");
            printf("1 - Inserir item\n");
            printf("2 - Remover item\n");
            printf("3 - Listar itens\n");
            printf("4 - Buscar item (sequencial)\n");
            if (estrutura == 1) {
                printf("5 - Ordenar vetor\n");
                printf("6 - Buscar item (binária, vetor)\n");
            }
            printf("0 - Voltar\n");
            printf("Opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    if (estrutura == 1) inserirItemVetor();
                    else inserirItemLista();
                    break;
                case 2:
                    if (estrutura == 1) removerItemVetor();
                    else removerItemLista();
                    break;
                case 3:
                    if (estrutura == 1) listarItensVetor();
                    else listarItensLista();
                    break;
                case 4:
                    printf("\nDigite o nome do item para buscar: ");
                    scanf(" %[^\n]", nomeBusca);
                    if (estrutura == 1) buscarSequencialVetor(nomeBusca);
                    else buscarSequencialLista(nomeBusca);
                    break;
                case 5:
                    if (estrutura == 1) ordenarVetor();
                    else printf("\n Opção inválida para lista encadeada!\n");
                    break;
                case 6:
                    if (estrutura == 1) {
                        printf("\nDigite o nome do item para buscar (binária): ");
                        scanf(" %[^\n]", nomeBusca);
                        buscarBinariaVetor(nomeBusca);
                    } else {
                        printf("\n Opção inválida para lista encadeada!\n");
                    }
                    break;
                case 0: break;
                default: printf("\n Opção inválida!\n");
            }
        } while (opcao != 0);

    } while (estrutura != 0);

    printf("\n Encerrando o sistema...\n");
    return 0;
}
