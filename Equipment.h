#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

/**
 * 装备实体：携带名称、攻击加成和防御加成，
 * 支持基础的属性访问与文本输出。
 */
class Equipment {
public:
    Equipment() = default;
    Equipment(const std::string& name,
              int attackBonus,
              int defenseBonus);

    // 访问器
    const std::string& getName() const;
    int getAttackBonus() const;
    int getDefenseBonus() const;

    // 修改器
    void setName(const std::string& name);
    void setAttackBonus(int bonus);
    void setDefenseBonus(int bonus);

    // 文本描述
    std::string toString() const;

    // 方便输出到流
    friend std::ostream& operator<<(std::ostream& os, const Equipment& eq);

private:
    std::string name_;
    int attackBonus_  = 0;
    int defenseBonus_ = 0;
};

#endif 