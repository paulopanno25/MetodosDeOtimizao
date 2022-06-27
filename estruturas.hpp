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
    int Ordem;

}DadosDasTarefas;

int entrada[MAX_TAREFAS];// vetor que armazena todos os dados inteiros de uma linha d arquivo

int QuantidadeDeRecursos;
int QuantidadeDeTarefas;
int Matriz[MAX_TAREFAS][MAX_TAREFAS];
int MatrizIndObjOrd[MAX_TAREFAS][MAX_TAREFAS];
int QuantidadeDeCadaRecursoDisponivel[MAX_OBJ];
int ptemp[MAX_OBJ],ptemp2[MAX_OBJ];


void lerArquivo();
void PreencherMatrizDeSucessores(DadosDasTarefas DadosDasTarefas[]);
void OrdemDeExecucao(DadosDasTarefas infoTarefas[]);
void HeuConstAleGul(DadosDasTarefas infoTarefas[], const int percentual);
void CalculoFo(DadosDasTarefas infoTarefas[]);
void TempoDeExecucao();
void EscreverSolucao(DadosDasTarefas infoTarefas[], const bool flag);


#endif // ESTRUTURAS_HPP_INCLUDED