#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "processo.h"
#include <locale.h>

#define MAX 18393

int main() {
    setlocale(LC_ALL, "");
    Processo p[MAX];
    int i = 0;
    int op;

    do {
        printf("\tMENU\n");
        printf("\n1 - Ordenar por ID\n");
        printf("2 - Ordenar por Data de Ajuizamento\n");
        printf("3 - Achar quantos processos estão vinculados a uma determinada classe\n");
        printf("4 - Identificar quantos id_assuntos constam\n");
        printf("5 - Calcular tempo do processo\n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &op);

        while ((getchar()) != '\n');

        if (op == 0) {
            printf("Saindo...\n");
            break;
        }

        i = lerArquivo(p, "processo_043_202409032338.csv");
        if (i == -1) {
            return 1;
        }

        switch (op) {
            case 1:
                ordenarId(p, i);
                criarArquivo(p, i);
                break;
            case 2:
                ordenarDt(p, i);
                criarArquivo(p, i);
                break;
            case 3: {
                char str[10], classeid[10];
                printf("Informe o número de id da classe (somente os números):\n");
                scanf("%s", str);
                sprintf(classeid, "{%s}", str);
                int num = acharclasse(p, i, classeid);
                printf("Estão vinculados %d processos à classe %s\n", num, str);
                break;
            }
            case 4: {
                int numachdos = numassuntos(p, i);
                printf("Constam %d id de assunto na tabela\n", numachdos);
                break;
            }
            case 5:
                calculardias(p, i);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        printf("\nPressione Enter para voltar ao menu...\n");
        while (getchar() != '\n');

    } while (op != 0);

    return 0;
}