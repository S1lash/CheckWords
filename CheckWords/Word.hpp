//
//  Word.hpp
//  CheckWords
//
//  Created by Илья Кузьмичев on 17.10.15.
//  Copyright © 2015 Ilya Kuzmichev. All rights reserved.
//

#ifndef Word_hpp
#define Word_hpp
#include <iostream>
#include <stdio.h>
using namespace std;


class Word {
    
    
public:
    Word(string basis, string word);
    string basis, word;
    long count;
};
#endif /* Word_hpp */
