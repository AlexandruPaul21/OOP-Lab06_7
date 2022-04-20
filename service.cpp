//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#include <algorithm>
#include "service.h"
//#include "vector_man.cpp"

using std::sort;

Service::Service(FileRepo& rp, Validator& vd) {
    repo=rp;
    valid=vd;
    undo_act.clear();
}

vector<Medicine>& Service::get_all_ent() {
    return repo.get_elems();
}

void Service::add(const string cname, const string cprod, const string csubst, int cprice) {
    valid.validate(cname,cprod,csubst,cprice);
    auto m=Medicine(cname,cprod,csubst,cprice);
    auto& v=repo.get_elems();
    vector<string> err;
    for(int i=0; i<v.size(); ++i){
        if(v[i]==m){
            err.push_back("Element deja existent");
        }
    }
    if(!err.empty()){
        throw RepoException(err);
    }
    repo.add_medicine(m);
    undo_act.push_back(new UndoAdd{&repo,m});
}

void Service::modify(const int poz, const string cname, const string cprod, const string csubst, const int cprice) {
    valid.validate(cname,cprod,csubst,cprice);
    vector<string> err;
    if(poz<0 || poz>=repo.get_elems().size()){
        err.push_back("Pozitie invalida");
        throw RepoException(err);
    }
    auto m=repo.get_elems()[poz];
    repo.modify_medicine(Medicine(cname,cprod,csubst,cprice),poz);
    undo_act.push_back(new UndoMod{&repo,m,poz});
}

void Service::del(const int poz){
    vector<string> err;

    if(poz<0 || poz>=repo.get_elems().size()){
        err.push_back("Pozitie invalida");
        throw RepoException(err);
    }
    auto dlt=repo.get_elems()[poz];
    repo.delete_medicine(poz);
    undo_act.push_back(new UndoDel{&repo,dlt,poz});
}

Service::~Service() {
    //do nothing
    while(!undo_act.empty()){
        ActUndo* act=undo_act.back();
        undo_act.pop_back();
        delete act;
    }
}

bool Service::search(const string cname, const string cprod, const string csubst, const int cprice) {
    //vector<string> err;

    valid.validate(cname,cprod,csubst,cprice);

    auto m=Medicine(cname,cprod,csubst,cprice);

    auto it= find_if(repo.get_elems().begin(),repo.get_elems().end(),[=](Medicine& med){
       return med.get_subst()==m.get_subst() && med.get_price()==m.get_price() && med.get_name()==m.get_name() &&
       med.get_prod()==m.get_prod();
    });

    return it<repo.get_elems().end();

}

void Service::filter(int crit, string val,vector<Medicine>& rez) {
    if(crit==0){
        vector <string> err;
        int prc=0;
        bool vld=true;
        for(int i=0; i<val.size(); ++i){
            if('0'<=val[i] && val[i]<='9'){
                prc=prc*10+(val[i]-'0');
            } else {
                vld=false;
            }
        }
        if(!vld){
            err.push_back("Pret invalid");
            throw RepoException(err);
        }

        rez.clear();
        copy_if(repo.get_elems().begin(), repo.get_elems().end(), back_inserter(rez), [=](Medicine& m){
            return m.get_price()==prc;
        });
        return;
    }

    rez.clear();
    copy_if(repo.get_elems().begin(),repo.get_elems().end(), back_inserter(rez), [=](Medicine& m){
        return m.get_subst()==val;
    });

}

bool crit_0(const Medicine& el1, const Medicine& el2){
    return el1.get_name()<el2.get_name();
}

bool crit_1(const Medicine& el1, const Medicine& el2){
    return el1.get_prod()<el2.get_prod();
}

bool crit_2(const Medicine& el1, const Medicine& el2){
    return el1.get_subst()<el2.get_subst() || (el1.get_subst()==el2.get_subst() &&
    el1.get_price()<el2.get_price());
}

void Service::sort(int crit, vector<Medicine>& rez) {
    rez=repo.get_elems();
    if(crit==0){
        ::sort(rez.begin(),rez.end(), crit_0);
    } else if(crit==1){
        ::sort(rez.begin(),rez.end(), crit_1);
    } else if(crit==2){
        ::sort(rez.begin(),rez.end(), crit_2);
    }
}

void Service::undo() {
    if(undo_act.empty()){
        vector<string> err;
        err.push_back("Nu exista operatii la care sa se faca undo");
        throw RepoException(err);
    }
    ActUndo* act=undo_act.back();
    act->doUndo();
    undo_act.pop_back();
    delete act;
}
