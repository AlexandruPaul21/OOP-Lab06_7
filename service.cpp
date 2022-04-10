//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#include "service.h"
#include "vector_man.cpp"

Service::Service(Repo& rp, Validator& vd) {
    repo=rp;
    valid=vd;
}

Vector_Man<Medicine>& Service::get_all_ent() {
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
}

void Service::modify(const int poz, const string cname, const string cprod, const string csubst, const int cprice) {
    valid.validate(cname,cprod,csubst,cprice);
    vector<string> err;
    if(poz<0 || poz>=repo.get_elems().size()){
        err.push_back("Pozitie invalida");
        throw RepoException(err);
    }
    auto m=Medicine(cname,cprod,csubst,cprice);
    repo.modify_medicine(m,poz);

}

void Service::del(const int poz){
    vector<string> err;

    if(poz<0 || poz>=repo.get_elems().size()){
        err.push_back("Pozitie invalida");
        throw RepoException(err);
    }
    repo.delete_medicine(poz);
}

Service::~Service() {
    //do nothing
}

bool Service::search(const string cname, const string cprod, const string csubst, const int cprice) {
    vector<string> err;

    valid.validate(cname,cprod,csubst,cprice);

    auto m=Medicine(cname,cprod,csubst,cprice);

    auto& all=repo.get_elems();
    for(int i=0; i<all.size(); ++i){
        if(all[i]==m){
            return true;
        }
    }
    return false;

}

void Service::filter(int crit, string val,Vector_Man<Medicine>& rez) {
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

        auto& all=repo.get_elems();

        for(int i=0; i<all.size(); ++i){
            if(all[i].get_price()==prc){
                rez.push_back(all[i]);
            }
        }
        return;
    }
    auto& all=repo.get_elems();

    for(int i=0; i<all.size(); ++i){
        if(all[i].get_subst()==val){
            rez.push_back(all[i]);
        }
    }
    return;
}

void Service::sort(int crit, Vector_Man<Medicine>& rez) {
    auto& el=repo.get_elems();
    for(int i=0; i<el.size()-1; ++i){
        for(int j=i+1; j<el.size(); ++j){
            if((crit==0 && el[i].get_name()>el[j].get_name()) || (crit==1 && el[i].get_prod()>el[j].get_prod())
            || (crit==2 && (el[i].get_subst()>el[j].get_subst() || (el[i].get_subst()==el[j].get_subst() &&
            el[i].get_price()>el[j].get_price())))) {
                swap(el[i],el[j]);
            }
        }
    }
    for(int i=0; i<el.size(); ++i){
        rez.push_back(el[i]);
    }
}
