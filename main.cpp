#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <vector>

#include "estruturas.hpp"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;

int main(){

    string filename("j10.txt");
    vector<string> words;
    string word;
    
    ifstream input_file("j10.txt");
    
    if(!input_file.is_open()){
        cerr << "Arquivo Invalido!- '"
             << filename << "'" << endl;
        
        return 0;

    }else{  
        while (input_file >> word) {
            words.push_back(word);
        }
        
        for (auto& i : words){
            cout << i << endl;
        }
        
        input_file.close();

        
    }






    return 0;

}


