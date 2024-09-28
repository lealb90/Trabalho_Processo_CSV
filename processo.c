#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "processo.h"

#define MAX 18393

int lerArquivo(Processo p[], const char *nome_arquivo) {
    char linha[256];
    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        printf("ERRO na abertura do arquivo\n");
        return -1;  
    }

    // Ignorar o cabeçalho
    fgets(linha, sizeof(linha), arq);

    int i = 0;
    
    while (fgets(linha, sizeof(linha), arq) != NULL && i < MAX) {
        linha[strcspn(linha, "\n")] = 0; // Remove o '\n'
        
        char *token = strtok(linha, ",");
        if (token) strcpy(p[i].id, token);

        token = strtok(NULL, ",");
        if (token) strcpy(p[i].num, token);

        token = strtok(NULL, ",");
        if (token) strcpy(p[i].dt_ajuizamento, token);
        
        token = strtok(NULL, ",");
        if (token)strcpy(p[i].id_classe, token);
       
        token = strtok(NULL, ",");
        if (token)strcpy(p[i].id_assunto, token);
      
        token = strtok(NULL, ",");
        if (token) strcpy(p[i].ano_eleicao, token);

        i++;
    }
    fclose(arq);
    return i;
}

int comparar(char *a, char *b) {
    return atoi(a) - atoi(b);
}

void ordenarId(Processo p[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (comparar(p[j].id, p[minIndex].id) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Processo temp = p[i];
            p[i] = p[minIndex];
            p[minIndex] = temp;
        }
    }
}

int compararData(char *data1, char *data2) {
    return strcmp(data1, data2);  
}

void ordenarDt(Processo p[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (compararData(p[j].dt_ajuizamento, p[minIndex].dt_ajuizamento) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Processo temp = p[i];
            p[i] = p[minIndex];
            p[minIndex] = temp;
        }
    }
}

void criarArquivo(Processo p[], int i) {
	int j;
    FILE *fp = fopen("dados_ordenado.csv", "w");
    if (fp == NULL) {
        printf("ERRO na abertura do arquivo\n");
        exit(1);
    }

    fprintf(fp, "id,numero;data_ajuizamento,id_classe,id_assunto,ano_eleicao\n");

    for (j = 0; j < i; j++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n", 
            p[j].id,
            p[j].num,
            p[j].dt_ajuizamento,
            p[j].id_classe,
            p[j].id_assunto,
            p[j].ano_eleicao);
    }

    fclose(fp);  
    printf("Abrindo arquivo...\n");
     system("dados_ordenado.csv");
     return;
}
int acharclasse(Processo p[],int i, const char *id){
	int j;
    int num = 0;
    for (j = 0; j < i; j++) {
        if (strcmp(id, p[j].id_classe) == 0) {
            num++;
        }
    }
    return num;
}
Processo acharprocesso(Processo p[],int i, const char *id){
	int j;
	for(j = 0; j < i; j++){
	if (strcmp(id, p[j].id) == 0){
		return p[j];
	}
		
	}
	printf("processo nao encontrado");
		exit (1);
	
}
void calculardias(Processo p[], int i){
    char id[10], ano_str[5], mes_str[3], dia_str[3];
    printf("Informe o id do processo: \n");
    fflush(stdin);
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = 0;

    Processo newp = acharprocesso(p, i, id);

    char *token = strtok(newp.dt_ajuizamento, "-");
    if (token) strcpy(ano_str, token);

    token = strtok(NULL, "-");
    if (token) strcpy(mes_str, token);

    token = strtok(NULL, " ");
    if (token) strcpy(dia_str, token);

    int ano = atoi(ano_str);
    int mes = atoi(mes_str);
    int dia = atoi(dia_str);

    time_t t = time(NULL);
    struct tm *dataatual = localtime(&t);

    int anoatual = dataatual->tm_year + 1900;
    int mesatual = dataatual->tm_mon + 1;
    int diaatual = dataatual->tm_mday;

    int resulano = anoatual - ano;
    int resulmes = mesatual - mes;
    int resuldia = diaatual - dia;
    if (resuldia < 0) {
        resuldia += 31;
        resulmes--;
    }
    if (resulmes < 0) {
        resulmes += 12;
        resulano--;
    }
    printf("O processo esta em tramitação na justiça a %d dias, %d meses, %d anos",resuldia,resulmes,resulano);
    
    
}
int numassuntos(Processo p[], int i) {
    int j, k;
    int numachados = 0;
    char achados[MAX][20];

    for (j = 0; j < i; j++) {
        int existe = 0;
        for (k = 0; k < numachados; k++) {  
            if (strcmp(p[j].id_assunto, achados[k]) == 0) {
                existe = 1;
                break;
            }
        }if (!existe) {
            strcpy(achados[numachados], p[j].id_assunto);
			 
            numachados++;
            
        }
        
        
    }
    return numachados;
}
