//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#include <iostream>
#include "UI.h"

using namespace std;

int get_pos_nr(){
    string S;
    getline(cin,S);
    if(S=="") getline(cin,S);

    bool ch=(S[0]==0);

    int ret=0;
    for(int i=0; i<S.size(); ++i){
        if('0'<=S[i] && S[i]<='9'){
            ret=ret*10+(S[i]-'0');
        } else {
            ch=true;
        }
    }
    if(ch){
        ret=-1;
    }
    return ret;
}

void Console::add_ui() const{
    string cname,cprod,csubst;
    int cprice;
    cout<<"Introduceti numele: ";
    getline(cin,cname);

    cout<<"Introduceti producatorul: ";
    getline(cin,cprod);

    cout<<"Introduceti subst. activa: ";
    getline(cin,csubst);

    cout<<"Introduceti pretul: ";
    cprice=get_pos_nr();

    try{
        srv.add(cname,cprod,csubst,cprice);
        cout<<"Adaugare realizata cu succes!\n";
    } catch(ValidationException& re){
        cout<<re;
    } catch(RepoException& exc){
        cout<<exc;
    }

}

void Console::del_ui() const{
    int ind;
    cout<<"Introduceti indicele de sters: ";
    ind=get_pos_nr();

    try {
        srv.del(ind);
        cout<<"Stergere efectuata cu succes!\n";
    } catch(RepoException&  re){
        cout<<re;
    }

}

void Console::cautare() const {
    cout<<"Introduceti datele despre medicamentul cautat!\n";

    string cname,cprod,csubst;

    int cprice;
    cout<<"Introduceti numele: ";
    getline(cin,cname);

    cout<<"Introduceti producatorul: ";
    getline(cin,cprod);

    cout<<"Introduceti subst. activa: ";
    getline(cin,csubst);

    cout<<"Introduceti pretul: ";
    cprice=get_pos_nr();

    try{
        bool res=srv.search(cname,cprod,csubst,cprice);
        if(res){
            cout<<"A fost gasit medicamentul!\n";
        } else {
            cout<<"Nu a fost gasit medicamentul\n";
        }
    } catch (ValidationException& ve){
        cout<<ve;
    }

}

void Console::filter() const {
    cout<<"Selectati criteriul de filtrare\n";
    cout<<"1. Pret\n";
    cout<<"2. Substanta activa\n";
    cout<<"Optiunea dvs. este: ";

    string op;
    getline(cin,op);

    vector<Medicine> rez(srv.get_all_ent().size());

    if(op=="1"){
        cout<<"Introduceti pretul de cautat: ";
        string price;
        getline(cin,price);
        try {
            srv.filter(0, price, rez);
        } catch(...){

        }
        if(rez.size()==0){
            cout<<"Nu a fost gasit nici-un rezultat\n";
            return;
        }
        cout<<"\n------------------Medicamente existente------------------\n";
        for(int i=0; i<rez.size(); ++i){
            cout<<i<<". Nume: "<<rez[i].get_name()<<"; Producator: "<<rez[i].get_prod()<<"; Subst.act: "<<rez[i].get_subst();
            cout<<"; Pret: "<<rez[i].get_price()<<"\n";
        }
        cout<<"\n";
    } else if(op=="2"){
        cout<<"Introduceti substanta activa de cautat: ";
        string subs;
        getline(cin,subs);
        try {
            srv.filter(1, subs, rez);
        } catch (...){

        }
        if(rez.size()==0){
            cout<<"Nu a fost gasit nici-un rezultat\n";
            return;
        }
        cout<<"\n------------------Medicamente existente------------------\n";
        for(int i=0; i<rez.size(); ++i){
            cout<<i<<". Nume: "<<rez[i].get_name()<<"; Producator: "<<rez[i].get_prod()<<"; Subst.act: "<<rez[i].get_subst();
            cout<<"; Pret: "<<rez[i].get_price()<<"\n";
        }
        cout<<"\n";
    } else {
        cout<<"Criteriu indisponibil momentant\n";
    }
}

void Console::sort() const {
    cout<<"Selectati criteriul de sortare\n";
    cout<<"1. Nume\n";
    cout<<"2. Producator\n";
    cout<<"3. Subst.activa + pret\n";
    cout<<"Optiunea dvs. este: ";

    string op;
    getline(cin,op);

    vector<Medicine> rez(srv.get_all_ent().size());

    if(op=="1" || op=="2" || op=="3"){
        srv.sort((op[0]-'0')-1,rez);
    } else {
        cout<<"Comanda invalida!\n";
        return;
    }
    cout<<"\n------------------Medicamente existente------------------\n";
    for(int i=0; i<rez.size(); ++i){
        cout<<i<<". Nume: "<<rez[i].get_name()<<"; Producator: "<<rez[i].get_prod()<<"; Subst.act: "<<rez[i].get_subst();
        cout<<"; Pret: "<<rez[i].get_price()<<"\n";
    }
    cout<<"\n";
}

void Console::show_all() const {
    vector<Medicine>& farm=srv.get_all_ent();
    if(farm.size()==0) return;
    cout<<"\n------------------Medicamente existente------------------\n";
    for(int i=0; i<farm.size(); ++i){
        cout<<i<<". Nume: "<<farm[i].get_name()<<"; Producator: "<<farm[i].get_prod()<<"; Subst.act: "<<farm[i].get_subst();
        cout<<"; Pret: "<<farm[i].get_price()<<"\n";
    }
    cout<<"\n";
}

void Console::mod_ui() const{
    int ind;

    cout<<"Introduceti indicele de sters: ";
    ind=get_pos_nr();

    string cname,cprod,csubst;
    int cprice;
    cout<<"Introduceti numele: ";
    getline(cin,cname);

    cout<<"Introduceti producatorul: ";
    getline(cin,cprod);

    cout<<"Introduceti subst. activa: ";
    getline(cin,csubst);

    cout<<"Introduceti pretul: ";
    cprice=get_pos_nr();

    try {
        srv.modify(ind, cname, cprod, csubst, cprice);
        cout << "Modificare facuta cu succes!\n";
    } catch(ValidationException& ve){
        cout<<ve;
    } catch(RepoException& re){
        cout<<re;
    }
}

void Console::show_ui() const {
    cout<<"Bine ati venit!\n";
    bool end=false;
    while(!end) {
        cout << "Comenzi disponibile:\n";
        cout<<"1. Adauga un element\n";
        cout<<"2. Modifica un elemnt\n";
        cout<<"3. Sterge un element\n";
        cout<<"4. Afiseaza toate medicamentele\n";
        cout<<"5. Cautare medicament\n";
        cout<<"6. Filtrare\n";
        cout<<"7. Sortare\n";
        cout<<"0. Exit\n";
        cout << "Comanda dvs: ";
        string ans;
        getline(cin, ans);
        if(ans==""){
            getline(cin, ans);
        }
        if(ans=="1"){
            add_ui();
        } else if(ans=="2"){
            mod_ui();
        } else if(ans=="3"){
            del_ui();
        } else if(ans=="4"){
            show_all();
        } else if(ans=="5") {
            cautare();
        } else if(ans=="6") {
            filter();
        } else if(ans=="7") {
            sort();
        } else if(ans=="0"){
            end=true;
        } else {
            cout<<"Comanada introdusa nu este corecta!\n";
        }
    }

}
