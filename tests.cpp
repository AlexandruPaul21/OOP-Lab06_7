//
// Created by Alexandru-Paul Sirbu on 26.03.2022.
//

#include "tests.h"

#include "vector_man.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <iostream>
#include "vector_man.cpp"

using namespace std;

void test_all(){
    test_gen();
    test_domain();
    test_repo();
    test_service();
    test_vector();
    cout<<"Le-o luat\n";
}

void test_gen(){
    Vector_Man<Medicine> v;
    auto m=Medicine("Parasinus","Bayer","paracetamol",5);
    v.push_back(m);
    Vector_Man<Medicine> v1;
    v1=v;
    assert(v1.size()==1);
    assert(v1[0].get_price()==5);
}

void test_domain(){
    //test constructor
    Medicine mn;
    mn=Medicine("Parasinus","Bayer","paracetamol",5);
    assert(mn.get_price()==5);
    Medicine m=Medicine("Parasinus","Bayer","paracetamol",5);
    assert(m.get_name()=="Parasinus");
    assert(m.get_prod()=="Bayer");
    assert(m.get_subst()=="paracetamol");
    assert(m.get_price()==5);

    //test validator
    Validator v;

    try {
        v.validate("", "Bayer", "paracetamol", 10);
        assert(false);
    } catch (ValidationException& val){
        //cout<<val;
        assert(true);
    }

    try {
        v.validate("", "", "", -5);
        assert(false);
    } catch (ValidationException& val){
        assert(true);
    }

    try{
        v.validate("Parasinus","Bayer","paracetamol",-5);
        assert(false);
    } catch(ValidationException& val){
        assert(true);
    }

    try{
        v.validate("Parasinus","Bayer","paracetamol",10);
        assert(true);
    } catch(ValidationException& val){
        assert(false);
    }

    try{
        v.validate("Parasinus","","paracetamol",10);
        assert(false);
    } catch(ValidationException& val){
        assert(true);
        //cout<<val;
    }

    try{
        v.validate("Parasinus","Bayer","",10);
        assert(false);
    } catch(ValidationException& val){
        assert(true);
    }

    try{
        v.validate("-5748654","-5748654","-5748654",10);
        assert(false);
    } catch(ValidationException& val){
        assert(true);
    }

    //test has letters
    assert(has_letters("-5748654")==false);
    assert(has_letters("48654")==false);
    assert(has_letters("4d86a54")==true);
    assert(has_letters("a48654")==true);
    assert(has_letters("a48654")==true);
}

void test_repo(){
    Repo repo;
    Medicine m=Medicine("Parasinus","Bayer","paracetamol",5);


    //test add elem & test get elems
    repo.add_medicine(m);
    Vector_Man<Medicine> mv;
    repo.get_elems().copy(mv);

    assert(mv.size() == 1);
    assert(mv[0].get_name() == "Parasinus");
    assert(mv[0].get_prod() == "Bayer");
    assert(mv[0].get_subst() == "paracetamol");
    assert(mv[0].get_price() == 5);

    //test modify elem
    Medicine m1=Medicine("Parasinus","Pharma","paracetamol",10);
    repo.modify_medicine(m1,0);

    repo.get_elems().copy(mv);

    assert(mv.size()==1);
    assert(mv[0].get_name()=="Parasinus");
    assert(mv[0].get_prod()=="Pharma");
    assert(mv[0].get_subst()=="paracetamol");
    assert(mv[0].get_price()==10);

    //test delete elems
    repo.add_medicine(m);
    repo.delete_medicine(0);

    repo.get_elems().copy(mv);

    assert(mv.size()==1);
    assert(mv[0].get_name()=="Parasinus");
    assert(mv[0].get_prod()=="Bayer");
    assert(mv[0].get_subst()=="paracetamol");
    assert(mv[0].get_price()==5);
}

void test_service(){
    auto r=Repo();
    auto v=Validator();

    auto s=Service(r,v);

    //test add
    s.add("Parasinus","Bayer","paracetamol",10);

    Vector_Man<Medicine> mv;
    s.get_all_ent().copy(mv);
    assert(mv[0].get_price()==10);
    assert(mv[0].get_name()=="Parasinus");
    assert(mv[0].get_prod()=="Bayer");
    assert(mv[0].get_subst()=="paracetamol");

    try{
        s.add("","Bayer","paracetamol",10);
        assert(false);
    } catch(ValidationException& ex){
        assert(true);
    }

    try{
        s.add("Parasinus","","paracetamol",10);
        assert(false);
    } catch(ValidationException& ex){
        assert(true);
        cout<<ex;
    }

    try{
        s.add("Parasinus","Bayer","",10);
        assert(false);
    } catch(ValidationException& ex){
        assert(true);
    }

    try{
        s.add("Parasinus","Bayer","paracetamol",-5);
        assert(false);
    } catch(ValidationException& ex){
        assert(true);
    }

    try{
        s.add("57486","Bayer","paracetamol",10);
        assert(false);
    } catch(ValidationException& ex){
        assert(true);
    }

    try{
        s.add("Parasinus","5788","paracetamol",10);
        assert(false);
    } catch(ValidationException& ex){
        assert(true);
    }

    try{
        s.add("Parasinus","Bayer","95874",10);
        assert(false);
    } catch(ValidationException& ex){
        assert(true);
    }

    //test mod
    s.modify(0,"ParaPenta","Dona","paracetamol",15);

    s.get_all_ent().copy(mv);

    assert(mv[0].get_price()==15);
    assert(mv[0].get_name()=="ParaPenta");
    assert(mv[0].get_prod()=="Dona");
    assert(mv[0].get_subst()=="paracetamol");

    try {
        s.modify(-5, "ParaPenta", "Dona", "paracetamol", 15);
        assert(false);
    } catch (RepoException& re){
        assert(true);
    }

    try {
        s.modify(8, "ParaPenta", "Dona", "paracetamol", 15);
        assert(false);
    } catch(RepoException&  re){
        assert(true);
    }

    //test del
    s.add("Parasinus","Bayer","paracetamol",10);

    //+test_search
    assert(s.search("Parasinus","Bayer","paracetamol",10)==1);
    assert(s.search("Parasinus","Bayr","paracetamol",10)==0);

    s.del(0);
    s.get_all_ent().copy(mv);

    assert(mv[0].get_price()==10);
    assert(mv[0].get_name()=="Parasinus");
    assert(mv[0].get_prod()=="Bayer");
    assert(mv[0].get_subst()=="paracetamol");

    try{
        s.add("Parasinus","Bayer","paracetamol",10);
        assert(false);
    } catch(RepoException& re){
        assert(true);
    }

    s.del(0);
    try {
        s.del(-8);
        assert(false);
    } catch(RepoException&  re){
        assert(true);
    }

    try {
        s.del(7);
        assert(false);
    } catch(RepoException&  re){
        assert(true);
        cout<<re;
    }

    //filter test
    s.add("Parasinus","Bayer","parasinus",10);
    s.add("ParaPenta","Pharma","parasinus",5);
    s.add("Algocalmin","Pharma1","ibuprofen",10);

    {
        Vector_Man<Medicine> res(5);
        s.filter(1, "parasinus", res);
        assert(res.size() == 2);
        assert(res[0].get_price() == 10);
        assert(res[0].get_subst() == "parasinus");
        assert(res[0].get_prod() == "Bayer");
        assert(res[0].get_name() == "Parasinus");

        assert(res[1].get_price() == 5);
        assert(res[1].get_subst() == "parasinus");
        assert(res[1].get_prod() == "Pharma");
        assert(res[1].get_name() == "ParaPenta");
    }

    {
        Vector_Man<Medicine> res(5);
        s.filter(0, "10", res);
        assert(res.size() == 2);
        assert(res[0].get_price() == 10);
        assert(res[0].get_subst() == "parasinus");
        assert(res[0].get_prod() == "Bayer");
        assert(res[0].get_name() == "Parasinus");

        assert(res[1].get_price() == 10);
        assert(res[1].get_subst() == "ibuprofen");
        assert(res[1].get_prod() == "Pharma1");
        assert(res[1].get_name() == "Algocalmin");

        try{
            s.filter(0,"a3",res);
            assert(false);
        } catch(...){
            assert(true);
        }
    }

    //sort

    {
        Vector_Man<Medicine> res(5);
        s.sort(0,res);
        assert(res.size()==3);
        assert(res[0].get_name()=="Algocalmin");
        assert(res[1].get_name()=="ParaPenta");
        assert(res[2].get_name()=="Parasinus");
    }

    {
        Vector_Man<Medicine> res(5);
        s.sort(1,res);
        assert(res.size()==3);
        assert(res[0].get_name()=="Parasinus");
        assert(res[1].get_name()=="ParaPenta");
        assert(res[2].get_name()=="Algocalmin");
    }

    {
        Vector_Man<Medicine> res(5);
        s.sort(2,res);
        assert(res.size()==3);
        assert(res[0].get_name()=="Algocalmin");
        assert(res[1].get_name()=="ParaPenta");
        assert(res[2].get_name()=="Parasinus");
    }

}

void test_vector(){
    Vector_Man<int> v1(5);
    v1.push_back(10);
    Vector_Man<int> v;

    assert(v.empty());

    v.push_back(5);

    assert(!v.empty());

    for(auto it=v.begin(); it!=v.end(); ++it){
        assert(*it==5);
    }
    v.push_back(10);

    Vector_Man<int> cp;
    v.copy(cp);

    assert(cp.size()==2);
    assert(cp[0]==5);
    assert(cp[1]==10);

    assert(v[1]==10);

    assert(v.size()==2);
    v.push_back(15);
    v.push_back(20);

    v.erase(0);
    assert(v.size()==3);

    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);

    try{
        Vector_Man<int> v5(-5);
        assert(false);
    } catch(...){
        assert(true);
    }

    try{
        v[-3]=5;
        assert(false);
    } catch(...){
        assert(true);
    }

    Vector_Man<Medicine> A;
    auto m=Medicine("Parasinus","Pharma","paracetamol",10);
    A.push_back(m);
}