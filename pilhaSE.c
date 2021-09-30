#include "interface.h"

void iniciaPilha(pilha *pilha) {
    pilha->topo = NULL;
    pilha->tamanhoPilha = 0;
}

int vazia(pilha *pilha) {
    if(pilha->topo == NULL) {
        return 1;
    }

    return 0;
}

void exibePilha(pilha *pilha) {
    if(vazia(pilha)){
        printf("A pilha está vazia!\n\n");

        return;
    }

    nodo *auxiliar;
    
    auxiliar = pilha->topo;

    printf("Pilha:");
    
    while (auxiliar != NULL) {
        printf("\n%s\n", auxiliar->tag);
        
        auxiliar = auxiliar->abaixo;
    }

    printf("%i", pilha->tamanhoPilha);
}

void destroiPilha(pilha *pilha) {
    if (!vazia(pilha)) {
        nodo *pilhaAcima, *pilhaAtual;

        pilhaAtual = pilha->topo;
        
        while (pilhaAtual != NULL) {
            pilhaAcima = pilhaAtual->abaixo;
            
            free(pilhaAtual);
            
            pilhaAtual = pilhaAcima;
        }
    }
}

void empilharTag(pilha *pilhaMae, char tag[50]) {
    nodo *novo = (nodo *) malloc(sizeof(nodo));

    memset(novo->tag, 0, 50);

    strncpy(novo->tag, tag, strlen(tag));

    novo->abaixo = NULL;

    if (vazia(pilhaMae)) {
        pilhaMae->topo = novo;
    } else {
        novo->abaixo = pilhaMae->topo;

        pilhaMae->topo = novo;
    }

    (pilhaMae->tamanhoPilha)++;
}

void desempilharTag(pilha *pilhaMae) {
    if (vazia(pilhaMae) == 0) {
        nodo *auxiliar = (nodo *) malloc(sizeof(nodo));

        auxiliar = pilhaMae->topo;

        pilhaMae->topo = auxiliar->abaixo;
        pilhaMae->tamanhoPilha--;
    }
}

bool validaTagComFechamento(char tag[50]) {
    if (strcmp(tag, "!DOCTYPE") == 0) {
        return false;
    }

    if (strcmp(tag, "input") == 0) {
        return false;
    }

    if (strcmp(tag, "iframe") == 0) {
        return false;
    }

    if (strcmp(tag, "img") == 0) {
        return false;
    }

    if (strcmp(tag, "br") == 0) {
        return false;
    }

    if (strcmp(tag, "hr") == 0) {
        return false;
    }

    if (strcmp(tag, "meta") == 0) {
        return false;
    }

    return true;
}

bool verificarTagAberturaNaPilha(pilha *pilhaMae, char tag[50]) {
    if(vazia(pilhaMae) == 1) {
        printf("Erro! Tag de fechamento sem tag de abertura.\n\nTag '</%s>'.", tag);

        free(pilhaMae);
        
        exit(0);
    }

    if (strcmp(pilhaMae->topo->tag, tag) == 0) {
        desempilharTag(pilhaMae);
        
        return false;
    }

    return true;
}