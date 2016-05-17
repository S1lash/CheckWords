//
//  main.cpp
//  CheckWords
//
//  Created by Илья Кузьмичев on 17.10.15.
//  Copyright © 2015 Ilya Kuzmichev. All rights reserved.
//
#include "Reader.hpp"
#include <iostream>
using namespace std;
#include "Word.hpp"
#include <map>
#include <vector>
#include "Porter.hpp"
#include <clocale>

int main(int argc, const char * argv[]) {
    
    setlocale(LC_ALL,"rus_rus.866");
    string path = "/Users/Ilya/Desktop/input";
    string word;
    Porter porter;
    map <string, Word> lib;
    Reader reader(path);
    reader.OpenFile();
    
    int j=1;
    
    while (!reader.Eof()) {
        
        word = reader.NextWord();
        if (word == "") {
            break;
        }
        
        word = porter.GetWord(word);
        if (word == "") {
            continue;
        }
        
        Word temp(porter.GetBase(word), word);
        
        if (lib.count(temp.basis) == 1) {
            (*lib.find(temp.basis)).second.count++;
        } else {
            lib.insert(pair<string,Word>(temp.basis,temp));
        }
        
        cout<<"WORD # "<<j<<endl;
        j++;
    }
    
    reader.CloseFile();
    
    
    vector<pair<long, Word>> sortLib;
    
    for (auto it = lib.begin(); it != lib.end(); ++it) {    //запись из map в вектор с параллельной
        if (sortLib.size() == 0) {                          //сортировкой по убыванию счетчика
        sortLib.push_back(pair<long,Word>((*it).second.count,(*it).second));
        } else {
            
            for (int i=0; i<sortLib.size(); i++) {
                
                if ((*it).second.count > sortLib[i].second.count ) {
                    
                    vector<pair<long, Word>> tempVector(sortLib);
                    sortLib[i] = pair<long, Word>((*it).second.count,(*it).second);
                    
                    for (int j = i; j<tempVector.size()-1; j++) {
                        sortLib[j+1] = tempVector[j];
                    }
                    sortLib.push_back(tempVector[tempVector.size()-1]);
                    
                    break;
                    
                } else {
                    if (i == sortLib.size()-1) {
                        sortLib.push_back(pair<long,Word>((*it).second.count,(*it).second));
                        break;
                    }
                }
            
            }
        }
    }
    
    for (int i=0; i<sortLib.size(); i++) {
        string bas = sortLib[i].second.basis;
        string word = sortLib[i].second.word;
        long count = sortLib[i].second.count;
        cout<<"word = "<<word<<"\t bas = "<<bas<<"\t count = "<<count<<endl;
    }
    
    
    
    return 0;
}
