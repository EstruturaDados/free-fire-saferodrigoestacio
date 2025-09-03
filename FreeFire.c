#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

//  STRUCT 
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

//  FUNÇÕES AUXILIARES 
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- Lista de Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

//  ORDENAÇÃO 

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

//  BUSCA BINÁRIA 
int buscaBinariaPorNome(Componente v[], int n, char chave[], int *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

//  MEDIÇÃO DE TEMPO 
void medirTempo(void (*algoritmo)(Componente[], int, int*),
                Componente v[], int n, int *comparacoes) {
    clock_t inicio, fim;
    inicio = clock();
    algoritmo(v, n, comparacoes);
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Comparações: %d | Tempo: %.6f segundos\n", *comparacoes, tempo);
}

//  PROGRAMA PRINCIPAL 
int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0, opcao, comparacoes;
    char chave[30];

    do {
        printf("\n==============================\n");
        printf("SISTEMA DE MONTAGEM DA TORRE\n");
        printf("==============================\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por nome (Bubble Sort)\n");
        printf("4 - Ordenar por tipo (Insertion Sort)\n");
        printf("5 - Ordenar por prioridade (Selection Sort)\n");
        printf("6 - Buscar componente por nome (binária, após ordenar por nome)\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                if (n >= MAX_COMPONENTES) {
                    printf("Mochila cheia. Não é possível cadastrar mais.\n");
                } else {
                    printf("Nome do componente: ");
                    fgets(componentes[n].nome, 30, stdin);
                    componentes[n].nome[strcspn(componentes[n].nome, "\n")] = 0;

                    printf("Tipo do componente: ");
                    fgets(componentes[n].tipo, 20, stdin);
                    componentes[n].tipo[strcspn(componentes[n].tipo, "\n")] = 0;

                    printf("Prioridade (1 a 10): ");
                    scanf("%d", &componentes[n].prioridade);
                    getchar();
                    n++;
                    printf("Componente cadastrado com sucesso.\n");
                }
                break;
            case 2:
                if (n == 0) {
                    printf("Nenhum componente cadastrado.\n");
                } else {
                    mostrarComponentes(componentes, n);
                }
                break;
            case 3:
                medirTempo(bubbleSortNome, componentes, n, &comparacoes);
                mostrarComponentes(componentes, n);
                break;
            case 4:
                medirTempo(insertionSortTipo, componentes, n, &comparacoes);
                mostrarComponentes(componentes, n);
                break;
            case 5:
                medirTempo(selectionSortPrioridade, componentes, n, &comparacoes);
                mostrarComponentes(componentes, n);
                break;
            case 6:
                printf("Digite o nome a buscar: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                {
                    int pos = buscaBinariaPorNome(componentes, n, chave, &comparacoes);
                    if (pos != -1) {
                        printf("Componente encontrado:\n");
                        mostrarComponentes(&componentes[pos], 1);
                    } else {
                        printf("Componente não encontrado.\n");
                    }
                    printf("Comparações: %d\n", comparacoes);
                }
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
