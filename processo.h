#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct {
    char id[10];
    char num[100];
    char dt_ajuizamento[100];
    char id_classe[10]; 
    char id_assunto[10];
    char ano_eleicao[10];
} Processo;

int comparar(char *a, char *b);
void criarArquivo(Processo p[], int i);
void ordenarId(Processo p[], int n);
char primeiroCaractere(const char *str);
void ordenarDt(Processo p[], int n);
int numassuntos(Processo p[],int i);
int acharclasse(Processo p[],int i, const char *id);
void calculardias(Processo p[], int i);
int lerArquivo(Processo p[], const char *nome_arquivo);


#endif
