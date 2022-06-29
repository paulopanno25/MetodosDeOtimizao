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
using namespace std; 

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::fill_n; using std::istringstream;


int main(){

    lerArquivo();
    

    return 0;

}

void lerArquivo(){

    string filename("j10.sm");
    string word;
    vector<string> words;
    vector<string> words2;
    int i=0, temporario=0, temporario2=0, auxiliar=0, x=0,p=0;
    DadosDasTarefas DadosDasTarefas[MAX_TAREFAS];
    

    ifstream input_file("j10.sm");
    
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
                
                cout << QuantidadeDeRecursos <<endl;
                
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
                cout << QuantidadeDeTarefas <<endl;
                
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
    for(int j=0;j<(QuantidadeDeTarefas+2);j++){
        int aux4=vetIndObjOrd2[j];
        cout<< vetIndObjOrd2[j] <<" - Ordem: "<< vetIndObjOrd[j] << " ,Duracao: " <<infoTarefas[aux4-1].DuracaoDaTarefa <<endl;  
    }

    HeuConstAleGul(infoTarefas, 10);//10% de aleatoriedade
    

}

void HeuConstAleGul(DadosDasTarefas infoTarefas[], const int percentual){
    int tam, pos, aux;
    int vetAux[MAX_OBJ];
    memcpy(&vetAux, &vetIndObjOrd2, sizeof(vetIndObjOrd2));
    /*tam = MAX(1, (percentual / 100.0) * (QuantidadeDeTarefas+1));
    for(int j = 0; j < tam; j++)
    {
        pos = j + rand()%((QuantidadeDeTarefas+1) - j);
        aux = vetAux[pos];
        vetAux[pos] = vetAux[j];
        vetAux[j] = aux;
    }
    memset(&s.vetPesMoc, 0, sizeof(s.vetPesMoc));
    memset(&s.vetIdMocObj, -1, sizeof(s.vetIdMocObj));
    for(int j = 0; j < numObj; j++)
        for(int i = 0; i < numMoc; i++)
            if(s.vetPesMoc[i] + vetPesObj[vetAux[j]] <= vetCapMoc[i])
            {
                s.vetIdMocObj[vetAux[j]] = i;
                s.vetPesMoc[i] += vetPesObj[vetAux[j]];
                break;
            }

    */
}

void CalculoFo(DadosDasTarefas infoTarefas[]){

}

void TempoDeExecucao(){

}

void EscreverSolucao(DadosDasTarefas infoTarefas[], const bool flag){

}

void LerDados(){

}










