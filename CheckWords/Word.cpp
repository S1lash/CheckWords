//
//  Word.cpp
//  CheckWords
//
//  Created by Илья Кузьмичев on 17.10.15.
//  Copyright © 2015 Ilya Kuzmichev. All rights reserved.
//

#include "Word.hpp"

Word::Word(string basis, string word){
    this->count=1;
    this->basis=basis;
    this->word=word;
}