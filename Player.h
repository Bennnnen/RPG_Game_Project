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


//*获取资源
/*double getResource(const string& res) const {
    auto it = resources_.find(res);
        // it->first 键，it->second 值
    if (it != resources_.end()) {
        return it->second;
    }

    return 0;
}

//*添加资源
void addResource(const string& res, double amount) {
        resources_[res] += amount;
    }

//*扣除资源
void consumeResource(const string& res, int amount) {
    // 当前拥有量
    double have = getResource(res);        
    if (have > amount) {
        // 足够扣掉
        resources_[res] = have - amount;
    } else {
        // 不足归零
        resources_[res] = 0;
    }
}*/


//背包
void addEquipment(const Equipment& eq) { inventory_.push_back(eq); }   //装备放进背包
const vector<Equipment>& getInventory() const { return inventory_; }   //读取背包所有装备

private:
    map<string, double> resources_;
    vector<Equipment> inventory_;
};





