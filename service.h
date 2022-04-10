//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#ifndef LAB06_7_SERVICE_H
#define LAB06_7_SERVICE_H

#include "repo.h"
#include "domain.h"

/**
 * Clasa Service din arhitectura GRASP
 */
class Service{
public:
    /**
     * Functia constructor
     * @param rp repo
     * @param vd validator
     */
    Service(Repo& rp, Validator& vd);

    /**
     * Functia returneaza toate entitatile
     * @return un vector cu elemente de tip medcine
     */
    Vector_Man<Medicine>& get_all_ent() ;

    /**
     * Adauaga un element in lista de obicete
     * @param cname numele
     * @param cprod producatorul
     * @param csubst substanta activa
     * @param cprice pretul obiectului
     * @raises un string de erori
     */
    void add(const string cname, const string cprod, const string csubst, const int cprice);

    /**
     * Modifica o entitate deja existenta
     * @param poz pozitia de sters
     * @param cname numele
     * @param cprod producatorul
     * @param csubst substanta activa
     * @param cprice pretul obiectului
     * @raises un string de erori
     */
    void modify(const int poz,const string cname, const string cprod, const string csubst, const int cprice);

    /**
     * Functia sterge entitatea de pe pozitia poz
     * @param poz pozitia de sters
     * @raises string de erori
     */
    void del(const int poz);

    /**
     * Functia cauta o anumita entitate
     * @param cname numele
     * @param cprod producatorul
     * @param csubst substanata activa
     * @param cprice pretul
     * @return 0 sau 1, daca se gaseste sau nu
     */
    bool search(const string cname, const string cprod, const string csubst, const int cprice);

    /**
     * Functia de filtrare
     * @param crit criteriul
     * @param val valoarea
     * @param res vectorul rezultat
     */
    void filter(int crit,string val,Vector_Man<Medicine>&);

    /**
     * Functia de sortare
     * @param crit criteriul
     * @param rez rezultateu
     */
    void sort(int crit,Vector_Man<Medicine>& rez);

    ~Service();
private:
    Repo repo;
    Validator valid;
};

#endif //LAB06_7_SERVICE_H