//
//  Reader.hpp
//  CheckWords
//
//  Created by Илья Кузьмичев on 17.10.15.
//  Copyright © 2015 Ilya Kuzmichev. All rights reserved.
//

#ifndef Reader_hpp
#define Reader_hpp
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

class Reader {
    
    
public:
    Reader (string pathToFile);
    string NextWord();
    void CloseFile();
    void OpenFile();
    bool Eof();
    
private:
    string pathToFile;
    fstream  f;
    
};



#endif /* Reader_hpp */
