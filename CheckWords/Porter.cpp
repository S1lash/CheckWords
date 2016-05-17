/*
 
 ENGLISH
 
("(a|e|i|o|u|y)(\\w*)")
("(a|e|i|o|u|y)")
("(\\w*)(a|e|i|o|u|y)")
("(b|c|d|f|g|h|j|k|l|m|n|p|q|r|s|t|v|w|x|z)");
("(a|e|i|o|u|y)(b|c|d|f|g|h|j|k|l|m|n|p|q|r|s|t|v|w|x|z)(\\w*)");
 
 RUSSIAN
 
("(а|е|и|о|у|ы|э|ю|я)")
("(б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)");
("(а|е|и|о|у|ы|э|ю|я)((а|е|и|о|у|ы|э|ю|я|б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)*)");
("(а|е|и|о|у|ы|э|ю|я|б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)");
("(а|е|и|о|у|ы|э|ю|я)(б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)((а|е|и|о|у|ы|э|ю|я|б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)*)");
(\\w*) = ((а|е|и|о|у|ы|э|ю|я|б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)*)
 */

#include "Porter.hpp"

void Porter::SearchRs(string word){
    boost::regex volwesPlusAll("(а|е|и|о|у|ы|э|ю|я)((а|е|и|о|у|ы|э|ю|я|б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)*)"); //гласная-все*
    boost::regex volwes ("(а|е|и|о|у|ы|э|ю|я)");//гласная
    
    this->prist = "";
    this->rv = "";
    this->r1 = "";
    this->r2 = "";
    
    
    string temp = boost::regex_replace(word, volwesPlusAll, "", boost::format_first_only);
    boost::regex newReg(temp);
    this->prist=temp;
    if (temp == word){
        return;
    } else {
    word = boost::regex_replace(word, newReg, "", boost::format_first_only);
    boost::sregex_iterator iter(word.begin(), word.end(), volwes);
    boost::smatch tempIt = *iter;
    boost::smatch checkIt;
        
    this->prist+=tempIt.str();
    this->rv = boost::regex_replace(word, volwes, "", boost::format_first_only);
        
    this->r1=this->SearchR(word);
    this->r2=this->SearchR(this->r1);
    
    }
}

string Porter::SearchR(string txt){
    boost::regex volwesNonVolvesPlusAll("(а|е|и|о|у|ы|э|ю|я)(б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)((а|е|и|о|у|ы|э|ю|я|б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)*)");//гласная-согласная-все*
    boost::regex volwesNonVolwes("(а|е|и|о|у|ы|э|ю|я)(б|в|г|д|ж|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ч|ш|щ|ь|ъ)");//гласная-согласная
    
    string temp = boost::regex_replace(txt, volwesNonVolvesPlusAll, "", boost::format_first_only);
    boost::regex newReg(temp);
    temp = boost::regex_replace(txt, newReg, "", boost::format_first_only);
    return boost::regex_replace(temp, volwesNonVolwes, "", boost::format_first_only);
    }




bool Porter::CheckNoun(){
    boost::regex reg("(а|ев|ов|ие|ье|е|иями|ями|ами|еи|ии|и|ией|ей|ой|ий|й|иям|ям|ием|ем|ам|ом|о|у|ах|иях|ях|ы|ь|ию|ью|ю|ия|ья|я)$");
    
    if ( boost::regex_search(this->rv, reg) ){
        this->changeRV = boost::regex_replace(this->rv, reg, "");
        return true;
    }
    return false;
}


bool Porter::CheckPerfectiveGerund(){
    boost::regex reg("((а|я|и|ы)(в|вши|вшись))$");
    
    if ( boost::regex_search(this->rv, reg) ){
        this->changeRV = boost::regex_replace(this->rv, reg, "");
        return true;
    }
    return false;
}

bool Porter::CheckReflexive(){
    boost::regex reg("(ся|сь)$");
    
    if ( boost::regex_search(this->rv, reg) ){
        this->changeRV = boost::regex_replace(this->rv, reg, "");
        return true;
    }
    return false;
}

bool Porter::CheckVerb(){
    boost::regex reg1("((а|я)(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно))$");
    boost::regex reg2("(ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)$");
    
    if ( boost::regex_search(this->rv, reg1) ){
        this->changeRV = boost::regex_replace(this->rv, reg1, "");
        return true;
    } else {
        if (boost::regex_search(this->rv, reg2)) {
            this->changeRV = boost::regex_replace(this->rv, reg2, "");
            return true;
        } else return false;
    }
}

bool Porter::CheckAjectival(){
    boost::regex participle_ajactive_1("(((а|я)(ем|нн|вш|ющ|щ))(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею))$");
    boost::regex participle_ajactive_2("((ивш|ывш|ующ)(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею))$");
    boost::regex ajactive("(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею)$");
    
    if ( boost::regex_search(this->rv, participle_ajactive_1) ){
        this->changeRV = boost::regex_replace(this->rv, participle_ajactive_1, "");
        return true;
    } else {
        if (boost::regex_search(this->rv, participle_ajactive_2)) {
            this->changeRV = boost::regex_replace(this->rv, participle_ajactive_2, "");
            return true;
        } else {
            if (boost::regex_search(this->rv, ajactive)) {
                this->changeRV = boost::regex_replace(this->rv, ajactive, "");
                return true;
            } else return false;
        }
    }
}

string Porter::GetWord(string word){
    boost::regex reg2("[А-Я]");
    if (boost::regex_search(word, reg2)) {
        word = this->InvertBigToSmall(word);
    }
    
    boost::regex reg3("ё");
    if (boost::regex_search(word, reg3)) {
        word = boost::regex_replace(word, reg3, "е");
    }
    
    boost::regex reg1("—| |«|…|»|“|„");
    if (boost::regex_search(word, reg1)) {
        word = boost::regex_replace(word, reg1, "");
    }
    return word;
}

string Porter::GetBase(string word){
    boost::regex reg1("[a-z]|[A-Z]");
    if (boost::regex_search(word, reg1)) {
        return word;
    }
    
    this->SearchRs(word);
    
    if (this->rv == "") {
        return word;
    }
    
    if (!this->Step_One()) {
        this->changeRV = this->rv;
        this->newWord = this->prist + this->changeRV;
    } else this->newWord = this->prist + this->changeRV;

    if (this->Step_Two()) {
        this->newWord = this->prist + this->changeRV;
    }
    
    if (this->Step_Three()) {
        this->newWord = this->prist + this->changeRV;
    }
    
    if (this->Step_Four()) {
        this->newWord = this->prist + this->changeRV;
    }
    
    return this->newWord;
}


bool Porter::Step_One(){
    
    if (this->CheckPerfectiveGerund()) {
        return true;
    }
    if (this->CheckReflexive()) {
        return true;
    }
    if (this->CheckAjectival()) {
        return true;
    }
    if (this->CheckVerb()) {
        return true;
    }
    if (this->CheckNoun()) {
        return true;
    }
    
    return false;
}

bool Porter::Step_Two(){
    boost::regex reg("о$");
    
    if (boost::regex_search(this->changeRV, reg)) {
        this->changeRV = boost::regex_replace(this->changeRV, reg, "");
        return true;
    } else return false;
    
}

bool Porter::Step_Three(){
    boost::regex derivational("ост|ость");
    boost::regex derivationalLast("(ост|ость)$");
    
    if (boost::regex_search(this->r2, derivational)) {
        if (boost::regex_search(this->changeRV, derivationalLast)) {
            this->changeRV = boost::regex_replace(this->changeRV, derivationalLast, "");
            return true;
        } else return false;
    } else return false;
}

bool Porter::Step_Four(){
    boost::regex superlative("(ейш|ейше)$");
    
    if (HasNN()){
        return true;
    }
    if (boost::regex_search(this->changeRV, superlative)){
        this->changeRV = boost::regex_replace(this->changeRV, superlative, "");
        HasNN();
        return true;
    }
    if (HasSoftSign()){
        return true;
    }
    
    return false;
}

bool Porter::HasNN(){
    boost::regex regNN("нн$");
    boost::regex regN("н$");
    
    if (boost::regex_search(this->changeRV, regNN)) {
        this->changeRV = boost::regex_replace(this->changeRV, regN, "");
        return true;
    } return false;
}

bool Porter::HasSoftSign(){
    boost::regex reg("ь$");
    
    if (boost::regex_search(this->changeRV, reg)) {
        this->changeRV = boost::regex_replace(this->changeRV, reg, "");
        return true;
    } return false;
}

string Porter::InvertBigToSmall(string word){
    boost::regex reg1("А");
    word = boost::regex_replace(word, reg1, "а");
    boost::regex reg2("Б");
    word = boost::regex_replace(word, reg2, "б");
    boost::regex reg3("В");
    word = boost::regex_replace(word, reg3, "в");
    boost::regex reg4("Г");
    word = boost::regex_replace(word, reg4, "г");
    boost::regex reg5("Д");
    word = boost::regex_replace(word, reg5, "д");
    boost::regex reg6("Е");
    word = boost::regex_replace(word, reg6, "е");
    boost::regex reg7("Ё");
    word = boost::regex_replace(word, reg7, "е");
    boost::regex reg8("Ж");
    word = boost::regex_replace(word, reg8, "ж");
    boost::regex reg9("З");
    word = boost::regex_replace(word, reg9, "з");
    boost::regex reg10("И");
    word = boost::regex_replace(word, reg10, "и");
    boost::regex reg11("Й");
    word = boost::regex_replace(word, reg11, "й");
    boost::regex reg12("К");
    word = boost::regex_replace(word, reg12, "к");
    boost::regex reg13("Л");
    word = boost::regex_replace(word, reg13, "л");
    boost::regex reg14("М");
    word = boost::regex_replace(word, reg14, "м");
    boost::regex reg15("Н");
    word = boost::regex_replace(word, reg15, "н");
    boost::regex reg16("О");
    word = boost::regex_replace(word, reg16, "о");
    boost::regex reg17("П");
    word = boost::regex_replace(word, reg17, "п");
    boost::regex reg18("Р");
    word = boost::regex_replace(word, reg18, "р");
    boost::regex reg19("С");
    word = boost::regex_replace(word, reg19, "с");
    boost::regex reg20("Т");
    word = boost::regex_replace(word, reg20, "т");
    boost::regex reg21("У");
    word = boost::regex_replace(word, reg21, "у");
    boost::regex reg22("Ф");
    word = boost::regex_replace(word, reg22, "ф");
    boost::regex reg23("Х");
    word = boost::regex_replace(word, reg23, "х");
    boost::regex reg24("Ц");
    word = boost::regex_replace(word, reg24, "ц");
    boost::regex reg25("Ч");
    word = boost::regex_replace(word, reg25, "ч");
    boost::regex reg26("Щ");
    word = boost::regex_replace(word, reg26, "щ");
    boost::regex reg27("Ш");
    word = boost::regex_replace(word, reg27, "ш");
    boost::regex reg28("Ъ");
    word = boost::regex_replace(word, reg28, "ъ");
    boost::regex reg29("Ы");
    word = boost::regex_replace(word, reg29, "ы");
    boost::regex reg30("Ь");
    word = boost::regex_replace(word, reg30, "ь");
    boost::regex reg31("Э");
    word = boost::regex_replace(word, reg31, "э");
    boost::regex reg32("Ю");
    word = boost::regex_replace(word, reg32, "ю");
    boost::regex reg33("Я");
    word = boost::regex_replace(word, reg33, "я");
    
    return word;
}