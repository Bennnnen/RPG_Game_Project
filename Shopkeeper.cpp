#include "ShopkeeperNPC.h"
#include "Player.h"
#include <sstream>
#include <stdexcept>
#include "json.hpp"

using namespace std;


ShopkeeperNPC::ShopkeeperNPC(Player* player, const std::string& name, const std::string& description, const std::string& systemPrompt)
    : NPC(name, description, systemPrompt), player_(player) //玩家指针存入成员
{
    addTopic("查看商品");
    addTopic("购买 <商品名>");
    addTopic("帮助");
}

ShopkeeperNPC::~ShopkeeperNPC() = default;

//检测AI客户端是否正常
void ShopkeeperNPC::generateInventory(OpenAIClient* aiClient) {
    if (inventoryGenerated_) {
        return;
    }
    if (!aiClient) {
        cout << "错误: AI 客户端不可用" << endl;
        return;
    }

    // 提示 AI 随机生成 5 件商品，返回纯 JSON 数组
    static const string prompt =
        "请随机生成 5 件可在商店售卖的装备，严格输出 JSON 数组，每件包含字段："
        "name, price, attackBonus, defenseBonus, durability。示例：\n"
        "[{\"name\":\"火焰之剑\",\"price\":120,\"attackBonus\":15,"
        "\"defenseBonus\":0,\"durability\":80}, …]";
    string resp = aiClient->generateStorySegment(prompt);

    //json字符变成c++可以编译的方式
    auto arr = nlohmann::json::parse(resp);
    //提取各项属性，创建InventoryItem，然后按名字存到商店的库存
    for (auto& obj : arr) {
        InventoryItem item;
        /*item.equipTemplate.name         = obj.at("name").get<string>();
        item.equipTemplate.attackBonus  = obj.at("attackBonus").get<int>();
        item.equipTemplate.defenseBonus = obj.at("defenseBonus").get<int>();
        item.equipTemplate.durability   = obj.at("durability").get<int>();
        item.price                      = obj.at("price").get<int>();
        inventory_[item.equipTemplate.name] = item;*/
        item.equipTemplate = Equipment(
            obj.at("name").get<string>(),
            obj.at("attackBonus").get<int>(),
            obj.at("defenseBonus").get<int>(),
            obj.at("durability").get<int>()
        );
        item.price = obj.at("price").get<int>();
        inventory_[item.equipTemplate.getName()] = item;
    }
    
}

   std::string ShopkeeperNPC::buyItem(const std::string& itemName) {
    auto it = inventory_.find(itemName);
    if (it == inventory_.end()) {
        return "商品不存在：" + itemName;
    }

    int price = it->second.price;
    if (player_->getResource("money") < price) {
        // 字符串字面量要先转 std::string
        return std::string("金币不足，无法购买 ") + itemName;
    }

    // 扣除金币
    player_->consumeResource("money", price);

    // 克隆并发放装备
    Equipment eq = it->second.equipTemplate;
    player_->addEquipment(eq);

    std::ostringstream oss;
    oss << "成功购买：" << itemName
        << "（花费 " << price << " 金币，"
        << "攻+" << eq.attackBonus
        << ", 防+" << eq.defenseBonus
        << "）";         
    return oss.str();
}



string ShopkeeperNPC::respondToPlayer(const string& input, OpenAIClient* aiClient)
{
    //查看商品
    if (input == "查看商品") {
        generateInventory(aiClient);
        std::ostringstream ss;
        ss << "商店当前商品：\n";
        for (auto& kv : inventory_) {
            const auto& name = kv.first;
            const auto& info = kv.second;
            ss << " - " << name
               << " : " << info.price << " 金币"
               << " (攻+" << info.equipTemplate.attackBonus
               << ", 防+" << info.equipTemplate.defenseBonus
               << ", 耐久 " << info.equipTemplate.durability << ")\n";
        }
        return ss.str();
    }

    //"购买 <商品名>"
    if (input.rfind("购买 ", 0) == 0) {
        generateInventory(aiClient);
        return buyItem(input.substr(3));
    }
    
    //帮助
    if (input == "帮助") {
        return getHelp();
    }
    
    // 其余交给 AI 处理
    return NPC::respondToPlayer(input, aiClient);
}