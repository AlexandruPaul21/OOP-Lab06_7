//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//
#include <iostream>
#include "domain.h"

Medicine::Medicine(const string name, const string prod, const string subst, const int price) {
    this->name=name;
    this->prod=prod;
    this->subst=subst;
    this->price=price;
}

Medicine::Medicine(const Medicine& m) : name{m.name},prod{m.prod},subst{m.subst},price{m.price}{
    //std::cout<<"M-am creat din altu deja creat :)\n";
}

bool Medicine::operator==(const Medicine &ot) {
    if(price==ot.price && prod==ot.prod && subst==ot.subst && price==ot.price){
        return true;
    }
    return false;
}

Medicine::Medicine() {
    name="";
    price=-1;
    prod="";
    subst="";
}

Medicine Medicine::operator=(const Medicine &ot) {
    name=ot.name;
    prod=ot.prod;
    subst=ot.subst;
    price=ot.price;
    return (*this);
}

bool has_letters(const string S){
    for(int i=0; i<S.size(); ++i){
        if('A'<=S[i] && S[i]<='Z' || 'a'<=S[i] && S[i]<='z'){
            return true;
        }
    }
    return false;
}

ostream &operator<<(ostream &out, const ValidationException &ex) {
    for(const auto& mess : ex.msg){
        out<<mess<<"\n";
    }
    return out;
}

void Validator::validate(
        const string cname,
        const string cprod,
        const string csubst,
        const int cprice
        ) const {
    //string errors="";

    vector<string> errors;

    bool vname= has_letters(cname);
    if(cname.size()==0){
        errors.push_back("Numele nu poat fi vid");
    } else if(!vname){
        errors.push_back("Numele trebuie sa contina minim o litera");
    }

    bool vprod= has_letters(cprod);
    if(cprod.size()==0){
        errors.push_back("Producatorul nu poate fi vid");
    } else if(!vprod){
        errors.push_back("Producatorul trebuie sa contina litere");
    }

    bool vsubst= has_letters(csubst);
    if(csubst.size()==0){
        errors.push_back("Substanta activa nu poate fi vida");
    } else if(!vsubst){
        errors.push_back("Substanta activa trebuie sa contina litere");
    }

    if(cprice<=0){
        errors.push_back("Pretul trebuie sa fie un numar natural nenul");
    }
    if(!errors.empty()){
        throw ValidationException(errors);
    }
}

