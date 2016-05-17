//
//  Reader.cpp
//  CheckWords
//
//  Created by Илья Кузьмичев on 17.10.15.
//  Copyright © 2015 Ilya Kuzmichev. All rights reserved.
//

#include "Reader.hpp"

Reader::Reader(string pathToFile){
    this->pathToFile=pathToFile;
}

string Reader::NextWord(){
    string temp="";
    char tempChar;
    
    while (!Eof()) {
        cout<<"while___>"<<temp<<"<"<<endl;
        tempChar=f.get();
        if (!ispunct(tempChar) and !iscntrl(tempChar) and !isspace(tempChar) and !Eof() ){
            temp+=tempChar;
        } else break;
        
    }
    
    if ((temp == "") and (!Eof())) {
        return this->NextWord();
    }
    
    
    return temp;
}

void Reader::CloseFile(){
    f.close();
}

void Reader::OpenFile(){
    f.open(pathToFile);
}

bool Reader::Eof(){
    return f.eof();
}

