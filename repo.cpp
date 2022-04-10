//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#include "repo.h"
#include "vector_man.h"
#include "vector_man.cpp"

void Repo::add_medicine(const Medicine &a) {
    this->elems.push_back(a);
}

void Repo::modify_medicine(const Medicine &a, int poz) {
    this->elems[poz]=a;
}

Vector_Man<Medicine>& Repo::get_elems(){
    return elems;
}

Repo::Repo() {

}

void Repo::delete_medicine(int poz) {
    this->elems.erase(poz);
}

ostream &operator<<(ostream &out, const RepoException &ex) {
    for(const auto& mesg : ex.msg){
        out<<mesg<<"\n";
    }
    return out;
}
