#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <map>
#include <string>
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
    map<std::string, NPC*> npcMap_;
    vector<unique_ptr<NPC>> npcs_;
    bool isRunning_;
    bool inConversation_ = false;
    void initializeNPCs();      // 加载并注册所有 NPC
    void listNPCs() const;      // 列出所有可用 NPC
    void showResources() const; // 打印玩家所有资源
    void showInventory() const; // 打印玩家背包
public:
    bool initialize(); 
    void run();
    void shutdown(); 
    void handlePlayerInput(const std::string& input);
};

#endif





































