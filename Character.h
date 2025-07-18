#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Character
{
protected:
    string name_;
    int hp_;
    int attackPower_;
    int defendPower_;
    string agility_;
public:
    Character(const string& name, int hp, int attackPower, int defendPower, const string& agility)
    : name_(name), hp_(hp), attackPower_(attackPower), defendPower_(defendPower), agility_(agility){}

    virtual ~Character() = default;

    string getName() const { return name_; }
    int getHp() const { return hp_; }

    void takeDamage(int damage) {hp_ -= damage;}
};

#endif

