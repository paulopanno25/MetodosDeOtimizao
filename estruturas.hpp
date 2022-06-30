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
    int IdDoAntecessor;
    int TempoDeInicio;

}DadosDasTarefas;

int entrada[MAX_TAREFAS];// vetor que armazena todos os dados inteiros de uma linha d arquivo

int QuantidadeDeRecursos;
int QuantidadeDeTarefas;
int Matriz[MAX_TAREFAS][MAX_TAREFAS];
int QuantidadeDeCadaRecursoDisponivel[MAX_OBJ];
int vetIndObjOrd[MAX_TAREFAS];
int vetIndObjOrd2[MAX_TAREFAS];
int vetDeExecucao[MAX_TAREFAS];
int Contador[MAX_OBJ];
int FO;
DadosDasTarefas vetorGeraldeInformacoes[MAX_TAREFAS];
int ptemp[MAX_OBJ],ptemp2[MAX_OBJ];


//leitura do arquivo sol
int fo;
int Mkspan;



void lerArquivo();
void PreencherMatrizDeSucessores(DadosDasTarefas DadosDasTarefas[]);
void OrdemDeExecucao(DadosDasTarefas infoTarefas[]);
void HeuConstAleGul(DadosDasTarefas infoTarefas[], const int percentual);
void CalculoFo(DadosDasTarefas infoTarefas[]);
void TempoDeExecucao(DadosDasTarefas infoTarefas[]);
void EscreverSolucao(DadosDasTarefas infoTarefas[], int makespan);
void LerDados();


#endif // ESTRUTURAS_HPP_INCLUDED