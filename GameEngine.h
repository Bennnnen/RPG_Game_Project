#include <iostream>
#include <memory>
#include "Player.h"
#include "OpenAIClient.h"
#include <vector>
#include "NPC.h"
#include "ShopkeeperNPC.h"
using namespace std;

class GameEngine
{
private:
    unique_ptr<Player> player_;
    unique_ptr<OpenAIClient> openAIClient_;
    void initializeNPCs();
    map<std::string, NPC*> npcMap_;
    vector<unique_ptr<NPC>> npcs_;
    bool isRunning_;
    bool inConversation_ = false;
public:
    bool initialize(); 
    void run();
    void shutdown(); 
    void showNPCMenu() const;                     // 显示可交互的 NPC 列表
    void listAvailableNPCs() const;               // 同上
    NPC* findNPC(const std::string& name) const;  // 名字查 NPC
    void startConversation(NPC* npc);             // 切换到和某 NPC 对话
    void endConversation();                       // 结束当前对话
    void handlePlayerInput(const std::string& input);
};





































/*#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "Player.h"
#include "OpenAIClient.h"
#include "NPC.h"
#include "ShopkeeperNPC.h"  // 注册商人 NPC

class GameEngine {
public:
    bool initialize();
    void run();
    void shutdown();

    // 新增：NPC 相关接口
    void showNPCMenu() const;                     // 显示可交互的 NPC 列表
    void listAvailableNPCs() const;               // 同上
    NPC* findNPC(const std::string& name) const;  // 名字查 NPC
    void startConversation(NPC* npc);             // 切换到和某 NPC 对话
    void endConversation();                       // 结束当前对话

    void handlePlayerInput(const std::string& input);

private:
    void initializeNPCs();  // 创建并注册 NPC

    std::unique_ptr<Player>       player_;
    std::unique_ptr<OpenAIClient> openAIClient_;
    std::vector<std::unique_ptr<NPC>> npcs_;  // 持有所有 NPC
    std::map<std::string, NPC*>       npcMap_;      // 名字 → NPC* 映射
    NPC*                              currentNPC_;  // 当前正在对话的 NPC
    bool                              isRunning_   = false;
    bool                              inConversation_ = false;
};
*/
