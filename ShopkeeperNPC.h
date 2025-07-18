#include "NPC.h"
#include "Equipment.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

/*
 * 商人NPC：商品列表由 AI 随机生成，购买后将装备加入玩家背包
 */

class ShopkeeperNPC : public NPC {
public:
    ShopkeeperNPC(const std::string& name, const std::string& description, const std::string& systemPrompt);
    virtual ~ShopkeeperNPC();

    /* 购买一件商品 */
    string buyItem(const string& itemName);

    /* 接口：查看商品、购买 <name>、帮助 */
    string respondToPlayer(const string& input, OpenAIClient* aiClient) override;

private:
    /*首次调用时由 AI 生成 N 件商品并填充 inventory_*/
    void generateInventory(OpenAIClient* aiClient);

    /** 库存项：装备模板 + 单价 */
    class InventoryItem {
    public:
        Equipment equipTemplate;
        int price;
    };

    map<std::string, InventoryItem> inventory_;
    bool inventoryGenerated_{false};
};