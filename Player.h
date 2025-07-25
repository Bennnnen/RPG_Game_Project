#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Character.h"
#include <map>
#include <vector>
#include "Equipment.h"
#include "Resources.h"


using namespace std;

class Player : public Character{
    public:
    Player(const string& name, const string& agility) : Character(name, 1000, 50, 100, agility){}


// ===== 资源接口，全部委托给 Resources =====
    double getResource(const std::string& res) const {
        return resources_.getResource(res);
    }

    void addResource(const std::string& res, double amount) {
        resources_.addResource(res, amount);
    }

    void consumeResource(const std::string& res, int amount) {
        resources_.consumeResource(res, amount);
    }



// ===== 背包接口 =====
    void addEquipment(const Equipment& eq) {
        inventory_.push_back(eq);
    }

    const std::vector<Equipment>& getInventory() const {
        return inventory_;
    }

private:
    Resources                resources_;  // 统一的资源管理
    std::vector<Equipment>   inventory_;  // 玩家背包
};

#endif





