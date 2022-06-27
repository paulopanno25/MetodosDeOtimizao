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
    int flag,aux,aux2;
    for(int j=0;j<QuantidadeDeTarefas+2; j++){
        for(int i=0; i<(QuantidadeDeTarefas+2); i++){
        MatrizIndObjOrd[j][i]=0;
        //cout<<MatrizIndObjOrd[j][i]<< " ";
        }//cout<<endl;  
    }
    for(int j=0;j<(QuantidadeDeTarefas+2);j++){
        infoTarefas[j].Ordem = 0;  
    }
    

    for(int i=0; i<(QuantidadeDeTarefas+1); i++){
        for(int j=0; j<(QuantidadeDeTarefas+2); j++){
            if(Matriz[i][j]!=0){
                
                if(i!=0){
                    for(aux=0;aux<(QuantidadeDeTarefas+1);aux++){
                        if(Matriz[aux][j]!=0){
                            
                           if(infoTarefas[aux].Ordem<infoTarefas[j].Ordem){
                                infoTarefas[j].Ordem;
                           }else{
                            infoTarefas[j].Ordem=infoTarefas[aux].Ordem+1;
                           }
                            
                        }
                    }
                }else{
                    infoTarefas[j].Ordem=i;
                }
            }
        }
    }

    for(int j=0;j<(QuantidadeDeTarefas+2);j++){
        cout<< infoTarefas[j].Id << " " << infoTarefas[j].Ordem << endl;  
    }

    //flag = 1;
    //while(flag){
    //    flag=0;
    //   for(int j=0; j<(QuantidadeDeTarefas+1); j++){


    //   }
   // }

}

void HeuConstAleGul(DadosDasTarefas infoTarefas[], const int percentual){

}

void CalculoFo(DadosDasTarefas infoTarefas[]){

}

void TempoDeExecucao(){

}

void EscreverSolucao(DadosDasTarefas infoTarefas[], const bool flag){

}










