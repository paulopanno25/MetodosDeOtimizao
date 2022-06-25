#ifndef ESTRUTURAS_HPP_INCLUDED
#define ESTRUTURAS_HPP_INCLUDED

#define MAX_OBJ 50
#define MAX_TAREFAS 1000

#include <string>

// Dados de entrada

typedef struct dadosDasTarefas{
    int Id;
    int QuantidadeDeSucessores;
    int IdSucessores[MAX_OBJ];
    int DuracaoDaTarefa;
    int QuantidadeDeRecursosConsumidos[MAX_OBJ];

}DadosDasTarefas;

int entrada[MAX_TAREFAS];// vetor que armazena todos os dados inteiros de uma linha d arquivo

int QuantidadeDeRecursos;
int QuantidadeDeTarefas;
int QuantidadeDeCadaRecursoDisponivel[MAX_OBJ];
int ptemp[MAX_OBJ],ptemp2[MAX_OBJ];


void lerArquivo();


#endif // ESTRUTURAS_HPP_INCLUDED