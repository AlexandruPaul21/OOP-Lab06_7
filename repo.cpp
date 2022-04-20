//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#include <fstream>
#include <sstream>
#include "repo.h"
//#include "vector_man.h"
//#include "vector_man.cpp"

void Repo::add_medicine(const Medicine &a) {
    this->elems.push_back(a);
}

void Repo::modify_medicine(const Medicine &a, int poz) {
    this->elems[poz]=a;
}

vector<Medicine>& Repo::get_elems(){
    return elems;
}

Repo::Repo() {

}

void Repo::delete_medicine(int poz) {
    //this->elems.erase(poz);
    this->elems.erase(elems.begin()+poz);
}

ostream &operator<<(ostream &out, const RepoException &ex) {
    for(const auto& mesg : ex.msg){
        out<<mesg<<"\n";
    }
    return out;
}

FileRepo::FileRepo(string fn) {
    filename=fn;
    load_from_file();
}

void FileRepo::load_from_file() {
    ifstream fin(filename);
    string str;
    while(getline(fin,str)) {
        stringstream ss(str);

        string word;
        vector<string> med;
        while (getline(ss, word, ';')) {
            med.push_back(word);
        }
        int nr=0;
        for(int i=0; i<med[3].size(); ++i){
            nr=nr*10+(med[3][i]-'0');
        }
        Repo::add_medicine(Medicine(med[0],med[1],med[2],nr));
    }
    fin.close();
}

void FileRepo::save_to_file() {
    ofstream fout(filename);
    for(auto& it : Repo::get_elems()){
        fout<<it.get_name()<<";"<<it.get_prod()<<";"<<it.get_subst()<<";"<<it.get_price()<<"\n";
    }
    fout.close();
}

FileRepo::~FileRepo() {
    save_to_file();
}
