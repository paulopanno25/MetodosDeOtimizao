#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <vector>
#include <algorithm>

#include "estruturas.hpp"
using namespace std; 

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::fill_n;


int main(){

    lerArquivo();

    return 0;

}

void lerArquivo(){

    string filename("j3048_10.sm");
    string word;
    vector<string> words;
    vector<string> words2;
    vector<string> words3;
    int i=0, temporario=0, temporario2=0, auxiliar=0, aux_id=32;
    DadosDasTarefas DadosDasTarefas[MAX_TAREFAS];
    

    ifstream input_file("j3048_10.sm");
    
    if(!input_file.is_open()){
        cerr << "Não foi possivel abrir o arquivo- '" << filename << "'" << endl;
        

    }else{  
        input_file >> word;
        string space_delimiter = " ";
    
        while( !input_file.eof()){
            getline(input_file,word);
            size_t pos = 0;
            
            
            if(i==8){
               // Pega a quantidade de recursos e armazena
                while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                    words.push_back(word.substr(0, pos));
                    word.erase(0, pos + space_delimiter.length());
                }
               sscanf(words[22].data(), "%d", &QuantidadeDeRecursos); //converte string para inteiro
                
                cout << QuantidadeDeRecursos <<endl;
                
            }

            if(i==14){
               //Pega a quantidade de tarefas e armazena
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
                    
                    DadosDasTarefas[temporario].IdSucessores[0]=0;
                    DadosDasTarefas[temporario].IdSucessores[1]=0;
                    DadosDasTarefas[temporario].IdSucessores[2]=0;

                    pos = 0;
                    while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                       words3.push_back(word.substr(0, pos));
                        word.erase(0, pos + space_delimiter.length());
                    }
                   
                   if(i<=26){
                        sscanf(words3[3].data(), "%d", &(DadosDasTarefas[temporario].Id)); //converte string para inteiro
                        sscanf(words3[21].data(), "%d", &(DadosDasTarefas[temporario].QuantidadeDeSucessores));
                        
                       

                        sscanf(words3[32].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[0]));//Armazena o id dos sucessores
                           
                        if((DadosDasTarefas[temporario].QuantidadeDeSucessores!=0) && (DadosDasTarefas[temporario].IdSucessores[0]==0)){
                            sscanf(words3[31].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[0]));
                        }

                        sscanf(words3[35].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[1]));//Armazena o id dos sucessores
                           
                        if((DadosDasTarefas[temporario].QuantidadeDeSucessores!=0) && (DadosDasTarefas[temporario].IdSucessores[1]==0)){
                            sscanf(words3[34].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[1]));
                            if((DadosDasTarefas[temporario].QuantidadeDeSucessores!=0) && (DadosDasTarefas[temporario].IdSucessores[1]==0)){
                                sscanf(words3[33].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[1]));
                            }
                        } 
                   
                                             
                        
                        
                   }else if(i<=116){
                       sscanf(words3[2].data(), "%d", &(DadosDasTarefas[temporario].Id)); //converte string para inteiro
                       sscanf(words3[20].data(), "%d", &(DadosDasTarefas[temporario].QuantidadeDeSucessores));
 

                       sscanf(words3[30].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[0]));//Armazena o id dos sucessores
                           
                        if((DadosDasTarefas[temporario].QuantidadeDeSucessores!=0) && (DadosDasTarefas[temporario].IdSucessores[0]==0)){
                            sscanf(words3[31].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[auxiliar]));
                        }

                      sscanf(words3[33].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[1]));//Armazena o id dos sucessores
                           
                        if((DadosDasTarefas[temporario].QuantidadeDeSucessores!=0) && (DadosDasTarefas[temporario].IdSucessores[1]==0)){
                            sscanf(words3[32].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[1]));
                            
                        } 
                      

                        
                   }else{
                       sscanf(words3[1].data(), "%d", &(DadosDasTarefas[temporario].Id)); //converte string para inteiro
                       sscanf(words3[19].data(), "%d", &(DadosDasTarefas[temporario].QuantidadeDeSucessores));

                        sscanf(words3[28].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[0]));//Armazena o id dos sucessores
                           
                        if((DadosDasTarefas[temporario].QuantidadeDeSucessores!=0) && (DadosDasTarefas[temporario].IdSucessores[0]==0)){
                            sscanf(words3[39].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[auxiliar]));
                        }

                      sscanf(words3[31].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[1]));//Armazena o id dos sucessores
                           
                        if((DadosDasTarefas[temporario].QuantidadeDeSucessores!=0) && (DadosDasTarefas[temporario].IdSucessores[1]==0)){
                            sscanf(words3[30].data(), "%d", &(DadosDasTarefas[temporario].IdSucessores[1]));
                            
                        } 
                       


                   }
                    int aux3=0;

                        sscanf(word.data(), "%d", &(aux3));
                        
                        DadosDasTarefas[temporario].IdSucessores[2]=aux3;//Armazena o ultimo id dos sucessores

                    if(DadosDasTarefas[temporario].IdSucessores[0]==0 && DadosDasTarefas[temporario].IdSucessores[1]!=0 ){   
                        DadosDasTarefas[temporario].IdSucessores[0]=aux3;
                        DadosDasTarefas[temporario].IdSucessores[1]=0;  
                        DadosDasTarefas[temporario].IdSucessores[2]=0;        
                    }else if(DadosDasTarefas[temporario].IdSucessores[1]==0 && DadosDasTarefas[temporario].IdSucessores[2]!=0){
                        DadosDasTarefas[temporario].IdSucessores[1]=aux3;
                        DadosDasTarefas[temporario].IdSucessores[2]=0;      
                    }


                     
                   //cout << DadosDasTarefas[temporario].Id << " " << DadosDasTarefas[temporario].QuantidadeDeSucessores << " " 
                   //<< DadosDasTarefas[temporario].IdSucessores[0] << " " <<  DadosDasTarefas[temporario].IdSucessores[1] << " " << DadosDasTarefas[temporario].IdSucessores[2] <<endl;
                    
                    temporario++;
                }                                
                    
                
            }
            
            words3.clear();

            if((i>=(18+(QuantidadeDeTarefas+6)))){
                if((i<=((18+(QuantidadeDeTarefas+6)+(QuantidadeDeTarefas+1))))){
                    
                    DadosDasTarefas[temporario].QuantidadeDeRecursosConsumidos[0]=0;
                    DadosDasTarefas[temporario].QuantidadeDeRecursosConsumidos[1]=0;
                    DadosDasTarefas[temporario].QuantidadeDeRecursosConsumidos[2]=0;
                    DadosDasTarefas[temporario].QuantidadeDeRecursosConsumidos[3]=0;
                    //cout << word << endl;
                    pos = 0;
                    while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                       words3.push_back(word.substr(0, pos));
                        word.erase(0, pos + space_delimiter.length());
                    }
                   
                   if(i<=((18+(QuantidadeDeTarefas+6))+8)){
                       sscanf(words3[13].data(), "%d", &(DadosDasTarefas[temporario2].DuracaoDaTarefa));
                       if(DadosDasTarefas[temporario2].DuracaoDaTarefa==0){
                           sscanf(words3[12].data(), "%d", &(DadosDasTarefas[temporario2].DuracaoDaTarefa));
                       }
                        //converte string para inteiro
                       

                        sscanf(words3[20].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0]));//Armazena o id dos sucessores
                           
                        if(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0] == 0 ){
                            sscanf(words3[19].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0]));
                        }
                        

                        sscanf(words3[24].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]));//Armazena o id dos sucessores
                        
                        if((DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]) == 0){
                            sscanf(words3[23].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]));
                        }

                        sscanf(words3[28].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]));//Armazena o id dos sucessores
                        
                        if((DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]) == 0){
                            sscanf(words3[27].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]));
                        }
                   
                                             
                        
                        
                   }else if(i<=(((18+(QuantidadeDeTarefas+6))+8)+90)){
                       sscanf(words3[12].data(), "%d", &(DadosDasTarefas[temporario2].DuracaoDaTarefa));
                       if(DadosDasTarefas[temporario2].DuracaoDaTarefa==0){
                           sscanf(words3[11].data(), "%d", &(DadosDasTarefas[temporario2].DuracaoDaTarefa));
                       }

                        sscanf(words3[19].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0]));//Armazena o id dos sucessores
                           
                        if(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0] == 0 ){
                            sscanf(words3[18].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0]));
                        }
                        

                        sscanf(words3[23].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]));//Armazena o id dos sucessores
                        
                        if((DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]) == 0){
                            sscanf(words3[22].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]));
                        }

                        sscanf(words3[27].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]));//Armazena o id dos sucessores
                        
                        if((DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]) == 0){
                            sscanf(words3[26].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]));
                        }


                        
                   }else{
                      sscanf(words3[11].data(), "%d", &(DadosDasTarefas[temporario2].DuracaoDaTarefa));
                       if(DadosDasTarefas[temporario2].DuracaoDaTarefa==0){
                           sscanf(words3[10].data(), "%d", &(DadosDasTarefas[temporario2].DuracaoDaTarefa));
                       }
                       //Le e armazena o consumo de recursos
                       sscanf(words3[18].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0]));//Armazena o id dos sucessores
                           
                        if(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0] == 0 ){
                            sscanf(words3[17].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0]));
                        }
                        

                        sscanf(words3[22].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]));//Armazena o id dos sucessores
                        
                        if((DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]) == 0){
                            sscanf(words3[21].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]));
                        }

                        sscanf(words3[26].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]));//Armazena o id dos sucessores
                        
                        if((DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]) == 0){
                            sscanf(words3[25].data(), "%d", &(DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]));
                        }

                   }
                    int auxpp=0;

                        sscanf(word.data(), "%d", &(auxpp));
                        
                        DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[3]=auxpp;//Armazena o ultimo id dos sucessores

                   
                  /*  cout << DadosDasTarefas[temporario2].DuracaoDaTarefa<<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[0] 
                        <<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[1]
                        <<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[2]
                        <<" "<<DadosDasTarefas[temporario2].QuantidadeDeRecursosConsumidos[3]<< endl;
                     */
                 
                    temporario2++;
                }   
                
                //cout<< word << endl;
            }
            
            if((i==((18+(QuantidadeDeTarefas+6)+(QuantidadeDeTarefas+1))+4))){
                //cout<<word<<endl;
                 pos = 0;
                while ((pos = word.find(space_delimiter)) != string::npos) { //Separa a string por ' '
                    words3.push_back(word.substr(0, pos));
                    word.erase(0, pos + space_delimiter.length());
                }

                sscanf(words3[3].data(), "%d", &(QuantidadeDeCadaRecursoDisponivel[0]));

                sscanf(words3[9].data(), "%d", &(QuantidadeDeCadaRecursoDisponivel[1]));

                sscanf(words3[14].data(), "%d", &(QuantidadeDeCadaRecursoDisponivel[2]));


                int auxppp=0;

                sscanf(word.data(), "%d", &(auxppp));
                        
                QuantidadeDeCadaRecursoDisponivel[3]=auxppp;//Armazena o ultimo 
            }
            i++; 

        }
            
        input_file.close();

    }

    void PreencherMatriz();

    int Matriz[QuantidadeDeTarefas][QuantidadeDeTarefas], j;
    int QuantidadeDeTarefasColuna = QuantidadeDeTarefas;
    int QuantidadeDeTarefasLinhas = QuantidadeDeTarefas;
    int IdSucessores = IdSucessores;
    i = 0;

    for (QuantidadeDeTarefasLinhas = 0; i <  QuantidadeDeTarefasLinhas; i++){ //linha
        for (QuantidadeDeTarefasColuna = 0; j < QuantidadeDeTarefasColuna; j++){ //coluna
            if (QuantidadeDeTarefasColuna == IdSucessores){ 
                cout << '1';
            } else {
                cout << '0';
            }
        }
    }

    //Imprimir para vê se está saindo correto
    for (QuantidadeDeTarefasLinhas = 0; i <  QuantidadeDeTarefasLinhas; i++){ //linha
        for (QuantidadeDeTarefasColuna = 0; j < QuantidadeDeTarefasColuna; j++){ //coluna
        cout << Matriz[QuantidadeDeTarefas][QuantidadeDeTarefas] << " ";
        }
    }    
}