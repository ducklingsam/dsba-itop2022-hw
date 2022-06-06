#ifndef POKEMON_H
#define POKEMON_H

#include <string>

using std::string;

struct Pokemon {
    int number;
    string name;
    string ftype;
    string stype;
    int cp;
    int hp;
    string url;
};

#endif // POKEMON_H
