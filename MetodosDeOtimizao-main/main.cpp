#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <climits>
#include <sstream>
#include <string>


#include "estruturas.hpp"

#define MAX(X,Y) ((X > Y) ? X : Y)

using namespace std; 

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::fill_n; using std::istringstream;


int main(){

    vector<string> words;

    lerArquivo();
    LerDados();

    return 0;

}

void lerArquivo(){

    string filename("j12060_7.sm");
    string word;
    vector<string> words;
    vector<string> words2;
    int i=0, temporario=0, temporario2=0, auxiliar=0, x=0,p=0;
    DadosDasTarefas DadosDasTarefas[MAX_TAREFAS];
    

    ifstream input_file("j12060_7.sm");
    
    if(!input_file.is_open()){
        cerr << "Não foi possivel abrir o arquivo- '" << filename << "'" << endl;
        

    }else{  
        input_file >> word;
        string space_delimiter = " ";
    
        while( !input_file.eof()){
            getline(input_file,word);
            size_t pos = 0;
            
            // Pega a quantidade de recursos e armazena
            if(i==8){
               
                while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                    words.push_back(word.substr(0, pos));
                    word.erase(0, pos + space_delimiter.length());
                }
               
                sscanf(words[22].data(), "%d", &QuantidadeDeRecursos); //converte string para inteiro
                
                //cout << QuantidadeDeRecursos <<endl;
                
            }

            //Pega a quantidade de tarefas e armazena
            if(i==14){
               
                pos = 0;
                while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                    words2.push_back(word.substr(0, pos));
                    word.erase(0, pos + space_delimiter.length());
                }
               sscanf(words2[8].data(), "%d", &QuantidadeDeTarefas);
               if(QuantidadeDeTarefas==0){
                   sscanf(words2[9].data(), "%d", &QuantidadeDeTarefas);
               } //converte string para inteiro
               // cout << QuantidadeDeTarefas <<endl;
                
            }
     
            //Pega a quantidade de sucessores e seus ids e armazena
            if(i>=18){
                
                if(i<=(18+(QuantidadeDeTarefas+1))){
                   
                    istringstream ss(word);
                   
                    x=0;
                    while( ss){
                    ss >> entrada[x];
                    x++;

                    }

                    DadosDasTarefas[temporario].Id = entrada[0];
                    DadosDasTarefas[temporario].QuantidadeDeSucessores = entrada[2];
                    p=3;
                    for(int z=0; z<DadosDasTarefas[temporario].QuantidadeDeSucessores; z++){
                        DadosDasTarefas[temporario].IdSucessores[z] = entrada[p];
                        p++;
                    }

                  /*   cout << DadosDasTarefas[temporario].Id << " " << DadosDasTarefas[temporario].QuantidadeDeSucessores << " " 
                   << DadosDasTarefas[temporario].IdSucessores[0] << " " <<  DadosDasTarefas[temporario].IdSucessores[1] << " " << DadosDasTarefas[temporario].IdSucessores[2] <<endl;
                    */
                    temporario++;

                   
                }                                
                    
                
            }

            //Pega a duração e a quantidade de recurso que cada tarefa consome
            if((i>=(18+(QuantidadeDeTarefas+6)))){
                if((i<=((18+(QuantidadeDeTarefas+6)+(QuantidadeDeTarefas+1))))){

                     istringstream ss(word);
                   
                    x=0;
                    while( ss){
                    ss >> entrada[x];
                    x++;

                    }

                    DadosDasTarefas[temporario2].DuracaoDaTarefa = entrada[2];
                    
                    p=3;
                    for(int z=0; z<QuantidadeDeRecursos; z++){
                        DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[z] = entrada[p];
                        p++;
                    }

                  /*  cout << DadosDasTarefas[temporario2].DuracaoDaTarefa<<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0] 
                        <<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]
                        <<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]
                        <<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[3]<< endl;
*/
                    
                
                    temporario2++;
                }   
            }
        
            //Pega Quanto de cada Recurso tem disponivel
            if((i==((18+(QuantidadeDeTarefas+6)+(QuantidadeDeTarefas+1))+4))){
            x=0; 
           // cout<<word<<endl;
            istringstream ss(word);
            while( ss){
                ss >> QuantidadeDeCadaRecursoDisponivel[x];
                x++;

            }
           
/*
                cout<<QuantidadeDeCadaRecursoDisponivel[0]<<endl;
                cout<<QuantidadeDeCadaRecursoDisponivel[1]<<endl;
                cout<<QuantidadeDeCadaRecursoDisponivel[2]<<endl;
                cout<<QuantidadeDeCadaRecursoDisponivel[3]<<endl;
*/

            }
            
            i++; 

        }
            
        input_file.close();

    }

    PreencherMatrizDeSucessores(DadosDasTarefas);
    OrdemDeExecucao(DadosDasTarefas);

       
}

void PreencherMatrizDeSucessores(DadosDasTarefas infoTarefas[]){
    int i,j,aux;

    //Zera Matriz
    for (i = 0; i <  QuantidadeDeTarefas+2; i++){ //linha
        for (j = 0; j < QuantidadeDeTarefas+2; j++){ //coluna
            Matriz[i][j]=0;
        }
    }
    
    //Preenche Matriz
    for (i = 0; i <QuantidadeDeTarefas+2; i++){ //linha
        for (j = 0; j <QuantidadeDeTarefas+2; j++){ //coluna
           //percorre e encontra ids de sucessores que estejam na linha
           for(aux=0;aux<(infoTarefas[i].QuantidadeDeSucessores);aux++){
            if(infoTarefas[i].IdSucessores[aux]==(j+1)){
                Matriz[i][j]=1;
            }
          } 
        }
    }
    
    //Imprimir Matriz
    /*i=0;
    while(i<QuantidadeDeTarefas+2){
        for(j=0; j<QuantidadeDeTarefas+2;j++){
            cout << Matriz[i][j] << " ";
        }
        cout << infoTarefas[i].Id << " " << endl;
        i++;
    }*/

   
}

void OrdemDeExecucao(DadosDasTarefas infoTarefas[]){
    int flag,aux,aux2=0,f,aux3;

    
    //Zera vetor de ordems
    for(int j=0;j<(QuantidadeDeTarefas+2);j++){

        infoTarefas[j].Ordem = 0; 
        infoTarefas[j].IdDoAntecessor = 0;  
        vetIndObjOrd[j]=0; 
        
    }
    

    for(int i=0; i<(QuantidadeDeTarefas+1); i++){
        for(int j=0; j<(QuantidadeDeTarefas+2); j++){
            if(Matriz[i][j]!=0){
                
                if(i!=0){//função que verifica se existe alguma tarefa a ser realizada antes e qual a sua ordem.
                    for(aux=0;aux<(QuantidadeDeTarefas+1);aux++){
                        if(Matriz[aux][j]!=0){
                            
                           if(infoTarefas[aux].Ordem<infoTarefas[j].Ordem){
                                infoTarefas[j].Ordem;
                           }else{
                            infoTarefas[j].Ordem=infoTarefas[aux].Ordem+1;
                            infoTarefas[j].IdDoAntecessor = aux+1;
                           }
                            
                        }
                    }
                }else{
                    infoTarefas[j].Ordem=i;
                }
            }
        }
    }
   
    //Cria vetor de antecessores(Vetor de indices ordenados) e vetor de ids
    for(int j=0;j<(QuantidadeDeTarefas+2);j++){ 
            vetIndObjOrd[j] = infoTarefas[j].Ordem;
            vetIndObjOrd2[j] = infoTarefas[j].Id;

    }
    

    //Ordena o vetor de ids das tarefas por antecessores
    for(int prev=0; prev<(QuantidadeDeTarefas+2);prev++){
        for(int next = prev+1; next<(QuantidadeDeTarefas+2);next++){
            aux2 =vetIndObjOrd[prev];
            aux3 = vetIndObjOrd2[prev];
            if(vetIndObjOrd[next]<vetIndObjOrd[prev]){
                vetIndObjOrd[prev]=vetIndObjOrd[next];
                vetIndObjOrd2[prev]=vetIndObjOrd2[next];
                vetIndObjOrd[next]=aux2;
                vetIndObjOrd2[next]=aux3;
            }
        }
    }
    
   //imprime Id e ordem da tarefa e duração
   /* for(int j=0;j<(QuantidadeDeTarefas+2);j++){
        int aux4=vetIndObjOrd2[j];
        cout<< vetIndObjOrd2[j] <<" - Ordem: "<< vetIndObjOrd[j] << " ,Duracao: " <<infoTarefas[aux4-1].DuracaoDaTarefa <<endl;  
    }*/

    HeuConstAleGul(infoTarefas, 10);//10% de aleatoriedade
    //TempoDeExecucao(infoTarefas);
    

}

void HeuConstAleGul(DadosDasTarefas infoTarefas[], const int percentual){
    int tam, pos, aux;
    int vetAux[MAX_TAREFAS];
   
   
    memcpy(&vetAux, &vetIndObjOrd2, sizeof(vetIndObjOrd2));
   
    tam = MAX(1, (percentual / 100.0) * (QuantidadeDeTarefas+2));
   
    for(int j = 0; j < tam; j++)
    {
        pos = j + rand()%((QuantidadeDeTarefas+2) - j);
        aux = vetAux[pos];
        vetAux[pos] = vetAux[j];
        vetAux[j] = aux;
    }
    memset(vetDeExecucao, 0, sizeof(vetDeExecucao));
    memset(Contador, 0, sizeof(Contador));
    
    vetIndObjOrd[0] = -1;
    vetDeExecucao[0]= -1;
    int cont=0;
    

    for(int prev=0; prev<(QuantidadeDeTarefas+2);prev++){
        for(int next = prev+1; next<(QuantidadeDeTarefas+2);next++){
            int aux2[QuantidadeDeRecursos];
            if((vetIndObjOrd[prev]) == 0 && vetIndObjOrd[vetAux[next]-1] == 0 && (vetIndObjOrd2[prev] != vetIndObjOrd2[vetAux[next]-1])){
               /* cout<< (vetIndObjOrd[prev]) << " ";
                cout<< vetIndObjOrd2[prev] << " ";
                cout<< vetIndObjOrd[vetAux[next]-1] << " ";
                cout<< vetIndObjOrd2[vetAux[next]-1] << " ";
                cout<<endl;*/
                cont=0;
                for(int i = 0; i < QuantidadeDeRecursos; i++){ 
                    if(infoTarefas[vetIndObjOrd2[prev]-1].QuantidadeDeRecursosConsumidos[i] + 
                       infoTarefas[vetIndObjOrd2[vetAux[next]-1]].QuantidadeDeRecursosConsumidos[i] <= QuantidadeDeCadaRecursoDisponivel[i]
                       && vetDeExecucao[vetIndObjOrd2[prev]-1] != 1){
                            
                            cont+=1;
                       }
                }
                if(cont == QuantidadeDeRecursos){
                    vetDeExecucao[vetIndObjOrd2[prev]-1] = 1;
                    vetDeExecucao[vetIndObjOrd2[vetAux[next]-1]-1] = 1;
                    infoTarefas[vetIndObjOrd2[prev]-1].TempoDeInicio = 0;
                    infoTarefas[vetIndObjOrd2[vetAux[next]-1]-1].TempoDeInicio = 0;
                }
            
            }
            if(vetDeExecucao[infoTarefas[vetIndObjOrd2[prev]-1].IdDoAntecessor] == 1 || vetDeExecucao[infoTarefas[vetIndObjOrd2[prev]-1].IdDoAntecessor] == -1){
                cont=0;
                if(vetDeExecucao[infoTarefas[vetIndObjOrd2[vetAux[next]-1]].IdDoAntecessor] == 1){
                    for(int i = 0; i < QuantidadeDeRecursos; i++){ 
                        if(infoTarefas[vetIndObjOrd2[prev]-1].QuantidadeDeRecursosConsumidos[i] + 
                       infoTarefas[vetIndObjOrd2[vetAux[next]-1]].QuantidadeDeRecursosConsumidos[i] <= QuantidadeDeCadaRecursoDisponivel[i]
                       && vetDeExecucao[vetIndObjOrd2[prev]-1] != 1){
                            
                            cont+=1;
                       }
                    }
                    if(cont == QuantidadeDeRecursos){
                        vetDeExecucao[vetIndObjOrd2[prev]-1] = 1;
                        vetDeExecucao[vetIndObjOrd2[vetAux[next]-1]-1] = 1;

                        int antecPosicao = (infoTarefas[vetIndObjOrd2[prev]-1].IdDoAntecessor);
                        int antecPosicaoNEXT = (infoTarefas[vetIndObjOrd2[vetAux[next]-1]].IdDoAntecessor);

                        infoTarefas[vetIndObjOrd2[prev]-1].TempoDeInicio = 
                        infoTarefas[antecPosicao].TempoDeInicio + infoTarefas[antecPosicao].DuracaoDaTarefa;
                        
                        infoTarefas[vetIndObjOrd2[vetAux[next]-1]-1].TempoDeInicio = 
                        infoTarefas[antecPosicaoNEXT].TempoDeInicio + infoTarefas[antecPosicaoNEXT].DuracaoDaTarefa;
                    }
                }else{
                    vetDeExecucao[vetIndObjOrd2[prev]-1] = 1;
                    int antecPosicao = (infoTarefas[vetIndObjOrd2[prev]-1].IdDoAntecessor);
                    infoTarefas[vetIndObjOrd2[prev]-1].TempoDeInicio = infoTarefas[antecPosicao].TempoDeInicio + infoTarefas[antecPosicao].DuracaoDaTarefa;
                    Contador[prev] =  infoTarefas[vetIndObjOrd2[prev]-1].TempoDeInicio + infoTarefas[vetIndObjOrd2[prev]-1].DuracaoDaTarefa;
                }
               
            }
        }
    }


    
    /* for(int j = 0; j < (QuantidadeDeTarefas+2); j++){
        cout << vetDeExecucao[j] << " ";
    }
    cout<<endl;
   for(int j = 0; j < (QuantidadeDeTarefas+2); j++){
        cout << vetIndObjOrd2[j]<< " ";
    }
    cout<<endl;
   for(int j = 0; j < (QuantidadeDeTarefas+2); j++){
        cout << infoTarefas[vetIndObjOrd2[j]-1].TempoDeInicio<< " ";
    }*/

    memcpy(&vetorGeraldeInformacoes, &infoTarefas, sizeof(vetorGeraldeInformacoes));
    CalculoFo(infoTarefas);


    
}

void CalculoFo(DadosDasTarefas infoTarefas[]){
    int Max=0, aux=0;
    for(int i=0; i<(QuantidadeDeTarefas+2); i++){
        aux = infoTarefas[i].TempoDeInicio + infoTarefas[i].DuracaoDaTarefa;
        if(aux>Max){
            Max = aux;
        }
    }

    FO = Max;
    for(int j=0; j<(QuantidadeDeTarefas+2); j++){
        FO += Contador[j];
    }

   EscreverSolucao(infoTarefas, Max);
    
}

void TempoDeExecucao(DadosDasTarefas infoTarefas[]){
    clock_t h;
    double tempo;
    const int repeticoes = 1000;
   // printf("\n\n>>> TESTE - HEURISTICAS CONSTRUTIVAS - PMM3 - %d REPETICOES\n", repeticoes);

    //---
    h = clock();
    for(int r = 0; r < repeticoes; r++)
        HeuConstAleGul(infoTarefas, 10); // 10% de aleatoriedade
    h = clock() - h;
    tempo = (double)h/CLOCKS_PER_SEC;

   printf("Construtiva Aleatoria Gulosa...: %.5f seg.\n", tempo);
}

void EscreverSolucao(DadosDasTarefas infoTarefas[], int makespan){
    int i=0;
    printf("\nFO: %d\n", FO);
    printf("Makespan: %d\n", makespan);
    printf("------------------------------------\n");
    cout << "Job" << " " << "Start" << endl;
    
    while(i<QuantidadeDeTarefas+2){
        cout<< infoTarefas[i].Id << "    " << infoTarefas[i].TempoDeInicio << endl;
        i++;
    }

   

}

void LerDados(vector<string> &words){
    string filename("j301_1.sol");
    string word;
    int i=0, temporario=0,x=0;
    DadosDasTarefas solucao[MAX_TAREFAS];
    

    ifstream input_file("j301_1.sol");
    
    if(!input_file.is_open()){
        cerr << "Não foi possivel abrir o arquivo- '" << filename << "'" << endl;
        

    }else{  
        input_file >> word;
        string space_delimiter = " ";
    
        while( !input_file.eof()){
            getline(input_file,word);
            size_t pos = 0;
            // Pega a FO
            if(i==0){
                while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                    words.push_back(word.substr(0, pos));
                    word.erase(0, pos + space_delimiter.length());
                }
               
                sscanf(word.data(), "%d", &fo); //converte string para inteiro
               // cout << fo <<endl;
                
            }
            
            // Pega a Makespan
            if(i==1){
                while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                    words.push_back(word.substr(0, pos));
                    word.erase(0, pos + space_delimiter.length());
                }
               
                sscanf(word.data(), "%d", &Mkspan); //converte string para inteiro
               // cout << Mkspan <<endl;
                
            }
     
            //Pega o id e o tempo de inicio
            if(i>=4){
                
                if(i<=(4+(QuantidadeDeTarefas+1))){
                   
                    istringstream ss(word);
                   
                    x=0;
                    while( ss){
                    ss >> entrada[x];
                    x++;

                    }

                    solucao[temporario].Id = entrada[0];
                    solucao[temporario].TempoDeInicio = entrada[1];
                    

                   // cout << solucao[temporario].Id  << " " << solucao[temporario].TempoDeInicio  <<endl;
                    
                    temporario++;

                   
                }                                
                    
                
            }
            
            i++; 

        }
            
        input_file.close();

    }

}