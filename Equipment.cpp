#include "Equipment.h"
#include <sstream>

using namespace std;

Equipment::Equipment(const string& name,
                     int attackBonus,
                     int defenseBonus,
                     int durability)
  : name_(name)
  , attackBonus_(attackBonus)
  , defenseBonus_(defenseBonus)
  , durability_(durability)
{}

const string& Equipment::getName() const {
    return name_;
}

int Equipment::getAttackBonus() const {
    return attackBonus_;
}

int Equipment::getDefenseBonus() const {
    return defenseBonus_;
}

int Equipment::getDurability() const {
    return durability_;
}

void Equipment::setName(const string& name) {
    name_ = name;
}

void Equipment::setAttackBonus(int bonus) {
    attackBonus_ = bonus;
}

void Equipment::setDefenseBonus(int bonus) {
    defenseBonus_ = bonus;
}

void Equipment::setDurability(int d) {
    durability_ = d;
}

string Equipment::toString() const {
    std::ostringstream ss;
    ss << name_
       << " (攻+" << attackBonus_
       << ", 防+" << defenseBonus_
       << ", 耐久 " << durability_ << ")";
    return ss.str();
}

ostream& operator<<(std::ostream& os, const Equipment& eq) {
    return os << eq.toString();
}