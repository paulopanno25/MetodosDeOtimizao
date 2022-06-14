#ifndef ESTRUTURAS_HPP_INCLUDED
#define ESTRUTURAS_HPP_INCLUDED


#include <string>

// Dados de entrada

typedef struct dadosDasTarefas{
    int Id;
    int QuantidadeDeSucessores;
    int IdSucessores[2];
    int DuracaoDaTarefa;
    int QuantidadeDeRecursosConsumidos[3];

}DadosDasTarefas;

int QuantidadeDeRecursos;
int QuantidadeDeTarefas;
int QuantidadeDeCadaRecursoDisponivel[3];




void lerArquivo(std::string arq);


#endif // ESTRUTURAS_HPP_INCLUDED