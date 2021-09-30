#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include "pilhaSE.c"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");
    
    pilha *pilhaMae = (pilha *) malloc(sizeof(pilha));

    if (!pilhaMae) {
        printf("\nErro! Não há memória disponível.\n");
        exit(1);
    } else {
        iniciaPilha(pilhaMae);
        
        bool concatenarTag = false;
        bool abrirTag = false;
        bool fecharTag = false;
        int countChar = 0;
        char caractere;

        char tag[50] = {0};

        FILE *arquivo = fopen(argv[1], "r");
        
        if (arquivo != NULL) {
            while((caractere = fgetc(arquivo)) != EOF) {
                if (caractere == '/' && countChar == 0 && concatenarTag == true) {
                    fecharTag = true;
                }

                if (caractere == '>') {
                    abrirTag = false;
                }

                if ((isspace(caractere) || caractere == '>') && caractere != '\n') {
                    int i = strlen(tag);

                    if (i > 0 && validaTagComFechamento(tag)) {
                        if (fecharTag == false) {
                            empilharTag(pilhaMae, tag);
                        } else {
                            if (verificarTagAberturaNaPilha(pilhaMae, tag) == true) {
                                printf("\nErro! Tag de fechamento sem tag de inicialização.\n\nTag esperada: '</%s>'. Tag recebida: '</%s>'.\n", pilhaMae->topo->tag, tag);

                                return 0;
                            } else {
                                fecharTag = false;
                            }
                        }
                    }



                    memset(tag, 0, sizeof(tag));
                    
                    countChar = 0;

                    concatenarTag = false;
                }

                if (concatenarTag && caractere != ' ' && strcmp(&caractere, "") != 0 && caractere != '/') {
                    tag[countChar] = caractere;
                    countChar++;
                }

                if (caractere == '<') {
                    if (abrirTag == true) {
                        printf("Erro! Símbolos de abertura de tag '<' repetidos no arquivo.");
                        
                        return 0;
                    }

                    abrirTag = true;
                    concatenarTag = true;
                } 
            }

            if (pilhaMae->tamanhoPilha > 0) {
                printf("Erro! Tag de inicialização sem tag de fechamento.\n\nTag '<%s>'.", pilhaMae->topo->tag);
            } else {
                printf("Sucesso! O arquivo HTML está correto.");
            }

            fclose(arquivo);    

            return 0;
        } else {
            printf("\nErro! Não foi possível abrir o arquivo.\n");
            
            return 0;
        }

        return 0;
    }
}