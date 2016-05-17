//
//  Porter.hpp
//  CheckWords
//
//  Created by Илья Кузьмичев on 20.10.15.
//  Copyright © 2015 Ilya Kuzmichev. All rights reserved.
//

#ifndef Porter_hpp
#define Porter_hpp

#include <stdio.h>
#include <boost/regex.hpp>
#include <iostream>
using namespace std;

class Porter {
    
public:
    
    string GetBase(string word);
    string GetWord(string word);
    
private:
    
    void SearchRs(string word);
    string SearchR(string txt);
    bool CheckPerfectiveGerund();
    bool CheckReflexive();
    bool CheckVerb();
    bool CheckNoun();
    bool CheckAjectival();
    bool Step_One();
    bool Step_Two();
    bool Step_Three();
    bool Step_Four();
    bool HasNN();
    bool HasSoftSign();
    string InvertBigToSmall(string word);
    
    string prist, changeRV, newWord;
    string rv, r1, r2;
};

#endif /* Porter_hpp */
