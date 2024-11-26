//Estrutura programa Tabela Hash - Professor Lucas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int maxsize = 10;

typedef struct data{
    char nome[51];
    char numero[11];
} contato;
    
struct hashmap{
    contato **map;
    int len;
} hashTable;

void inicializarTabela() {
    hashTable.map = (contato **) calloc(sizeof(contato), maxsize);
    for (int i = 0; i < maxsize; i++) {
        hashTable.map[i] = NULL;
    }
    hashTable.len = 0;
}

unsigned int hash(char *nome){
    int len = (int) strlen(nome);
    double somatorio = 0;
    for (int i=0; i < len; i++){
        somatorio += pow(nome[i], (len-i));
    }
    int pos = ((int) sqrt(somatorio)) % maxsize;
    return pos;
}

void adicionarContato(char *nome, char *numero) {
    int index = hash(nome);
    contato *novoContato = (contato *) malloc(sizeof(contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->numero, numero);

    if (hashTable.map[index] == NULL) {
        hashTable.map[index] = novoContato;
        hashTable.len++;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("Colisao! Implemente tratamento de colisao.\n");
    }
    return;
}

void buscarContato(char *nome) {
    
    clock_t start, end;
    start = clock();
    
    int index = hash(nome);
    if (hashTable.map[index] != NULL) {
        end = clock();
        double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        printf("Contato encontrado: %s - %s ", hashTable.map[index]->nome, hashTable.map[index]->numero);
        printf("(Tempo de busca: %.4f ms)\n", cpu_time_used);
    } else {
        printf("Contato nao encontrado.\n");
    }
    return;
}

void removerContato() {
    printf("Funcao para remover contato.\n");
}

void exibirContatos() {
    printf("Contatos: %d/%d\n", hashTable.len, maxsize);
    for (int i = 0; i < maxsize; i++) {
        if (hashTable.map[i] != NULL) {
            printf("Posicao %d: %s - %s\n", i, hashTable.map[i]->nome, hashTable.map[i]->numero);
        }
    }
}

int main() {
    int opcao;
    
    char nome[51];
    char numero[11];

    inicializarTabela();

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome do contato (sem espacos): ");
                scanf("%s", nome);
                printf("Numero do contato: ");
                scanf("%s", numero);
                adicionarContato(nome, numero);
                break;
            case 2:
                printf("Nome do contato: ");
                scanf("%s", nome);
                buscarContato(nome);
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
