//
// Created by Alexandru-Paul Sirbu on 12.04.2022.
//

#ifndef LAB06_7_RECIPE_CLASS_H
#define LAB06_7_RECIPE_CLASS_H

#include <vector>
#include <string>
#include "domain.h"

using std::vector;

class Recipe{
private:
    vector<Medicine> comp;
public:
    Recipe();

    vector<Medicine> get_all()const;

    void add_to_recipe(const Medicine& m);

    void empty_recipe();

    void random_add(const vector<Medicine>& elems,const int q);

    void save_to_file(const string filename);
};

#endif //LAB06_7_RECIPE_CLASS_H
