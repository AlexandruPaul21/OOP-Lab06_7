//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#ifndef LAB06_7_REPO_H
#define LAB06_7_REPO_H

#include <vector>
#include "domain.h"
#include <sstream>
#include "vector_man.h"
//#include "vector_man.cpp"

using namespace std;

/**
 * Clasa repository
 */
class Repo{
public:
    Repo();
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
    Vector_Man<Medicine>& get_elems();

    /**
     * Sterge medicamentul de pe o pozitie
     * @param poz pozitia medicamentului
     */
    void delete_medicine(int poz);


private:
    Vector_Man<Medicine> elems{5};
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

#endif //LAB06_7_REPO_H
