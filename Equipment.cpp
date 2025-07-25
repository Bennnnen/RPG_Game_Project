#include "Equipment.h"
#include <sstream>

using namespace std;

Equipment::Equipment(const string& name,
                     int attackBonus,
                     int defenseBonus)
  : name_(name)
  , attackBonus_(attackBonus)
  , defenseBonus_(defenseBonus)
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

void Equipment::setName(const string& name) {
    name_ = name;
}

void Equipment::setAttackBonus(int bonus) {
    attackBonus_ = bonus;
}

void Equipment::setDefenseBonus(int bonus) {
    defenseBonus_ = bonus;
}

string Equipment::toString() const {
    std::ostringstream ss;
    ss << name_
       << " (攻+" << attackBonus_
       << ", 防+" << defenseBonus_
       << ")";
    return ss.str();
}

ostream& operator<<(std::ostream& os, const Equipment& eq) {
    return os << eq.toString();
}