//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#ifndef LAB06_7_REPO_H
#define LAB06_7_REPO_H

#include <iostream>
#include <vector>
#include "domain.h"
#include <sstream>
//#include "vector_man.h"
//#include "vector_man.cpp"

using namespace std;

/**
 * Clasa repository
 */
class Repo{
public:
    Repo();
    //Repo(const Repo& ot){*this=ot;}
    /**
     * Adauga un medicament in repo
     * @param a medicamentul de adaugat
     */
    void add_medicine(const Medicine& a);

    /**
     * Modifica un medicament deja existent
     * @param a medicamentul de modificat
     * @param poz pozitia medicamentului
     */
    void modify_medicine(const Medicine& a, int poz);

    /**
     * Functie getter
     * @return un vector cu elemente de tip medcicine
     */
    vector<Medicine>& get_elems();

    /**
     * Sterge medicamentul de pe o pozitie
     * @param poz pozitia medicamentului
     */
    void delete_medicine(int poz);

    virtual ~Repo(){};

private:
    vector<Medicine> elems;
};


class FileRepo: public Repo{
private:
    string filename;

    void load_from_file();

    void save_to_file();

public:
    FileRepo()=default;
    FileRepo(string fn);
    //FileRepo(const FileRepo& ot){*this=ot;};

    ~FileRepo();

};


/**
 * Clasa custom de exceptie
 */
class RepoException{
    vector<string> msg;
public:
    RepoException(const vector<string>& errors): msg{errors}{}

    friend ostream& operator<<(ostream& out,const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);


class ActUndo{
public:
    virtual void doUndo()=0;
    virtual ~ActUndo(){};
};

class UndoAdd:public ActUndo{
private:
    FileRepo* fr;
    Medicine last;
public:
    UndoAdd(FileRepo* f,const Medicine& lst): fr{f}, last{lst} {}
    void doUndo() override{
        int i=0;
        for(auto& it : fr->get_elems()){
            if(it==last){
                break;
            }
            ++i;
        }
        fr->delete_medicine(i);
    }
};

class UndoMod:public ActUndo{
private:
    FileRepo* fr;
    Medicine last;
    int l_poz;
public:
    UndoMod(FileRepo* f,const Medicine& m,const int l_p): fr{f}, last{m}, l_poz{l_p} {}
    void doUndo() override{
        fr->modify_medicine(last,l_poz);
    }
};

class UndoDel:public ActUndo{
private:
    FileRepo* fr;
    Medicine dlt;
    int poz;
public:
    UndoDel(FileRepo* f, const Medicine& m, const int pz): fr{f}, dlt{m}, poz{pz} {}
    void doUndo() override{
        auto it=fr->get_elems().begin();
        it+=poz;
        fr->get_elems().insert(it,dlt);
    }
};

#endif //LAB06_7_REPO_H
