#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <string>

using namespace std;

/*装备实体*/
class Equipment {
public:
    string name;
    int attackBonus = 0;
    int defenseBonus = 0;
    int durability = 0;
};

#endif