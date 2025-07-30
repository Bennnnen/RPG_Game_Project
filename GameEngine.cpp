#include "GameEngine.h"


using namespace std;

bool GameEngine::initialize()
{
    player_ = make_unique<Player>("Hero","Agility");
    openAIClient_ = make_unique<OpenAIClient>("test");
    initializeNPCs();
    isRunning_ = true;
    return true;
}

void GameEngine::initializeNPCs()
{
    // 生成商人 NPC，使用中文名称以匹配内置交互命令
    auto shopkeeper = make_unique<ShopkeeperNPC>(
        player_.get(),        //传入player
        "商人",
        "一个友好的商店老板",
        "你是游戏中的商店老板，负责管理商品、处理购买请求并与玩家互动。"
    );
    shopkeeper->setAvailable(true);
    npcs_.push_back(move(shopkeeper));

    // 填充快速查找表
    for (auto& npcPtr : npcs_) {
        npcMap_[npcPtr->getName()] = npcPtr.get();
    }
}

void GameEngine::listNPCs() const
{
    cout << "可与之交互的 NPC：" << endl;
    for (const auto& kv : npcMap_) {
        cout << "- " << kv.first
             << " : " << kv.second->getDescription()
             << endl;
    }
}

void GameEngine::showResources() const
{
    cout << "当前资源情况：" << endl;
    // 由于 Player 没有暴露 allResources 接口，这里硬编码已知资源名
    vector<string> names = {"stone", "robber", "iron", "wood", "money"};
    for (const auto& resName : names) {
        cout << resName << ": " << player_->getResource(resName) << endl;
    }
}

void GameEngine::showInventory() const
{
    cout << "玩家背包：" << endl;
    const auto& items = player_->getInventory();  
    if (items.empty()) {
        cout << "背包为空。" << endl;
    } else {
        for (const auto& eq : items) {
            cout << "- " << eq << endl;
        }
    }
}

void GameEngine::run()
{
    cout << "Welcome to the game, if you wanna exit the game please click 'exit'" << endl;
    string input;

    while (isRunning_)
    {
        cout << "Your next step is:" << endl;
        getline(cin, input);

    if (input == "exit")
    {
        isRunning_ = false;
    } else{
        handlePlayerInput(input);

    }
}
    
}


void GameEngine::handlePlayerInput(const string& input)
{
        if (!inConversation_) {
        // 全局命令
        if (input == "help") {
            cout << "可用命令：\n"
                 << "- help: 显示此帮助\n"
                 << "- npcs: 列出所有 NPC\n"
                 << "- talk <NPC名>: 与指定 NPC 开始对话\n"
                 << "- resources: 查看当前资源\n"
                 << "- inventory: 查看背包\n"
                 << "- exit: 退出游戏" << endl;
        }
        else if (input == "npcs") {
            listNPCs();
        }
        else if (input.rfind("talk ", 0) == 0) {
            string target = input.substr(5);
            auto it = npcMap_.find(target);
            if (it != npcMap_.end() && it->second->isAvailable()) {
                currentNPC_    = it->second;
                inConversation_ = true;
                // 打招呼并显示话题
                cout << currentNPC_->getGreeting() << endl; 
                cout << currentNPC_->getHelp() << endl;
            } else {
                cout << "无法找到 NPC：" << target << endl;
            }
        }
        else if (input == "resources") {
            showResources();
        }
        else if (input == "inventory") {
            showInventory();
        }
        else {
            // 自由故事模式，调用 OpenAIClient
            string resp = openAIClient_->generateStorySegment(input);
            cout << "The story developed: " << resp << endl;
        }
    }
    else { // inConversation_
        // 对话中输入
        if (input == "bye") {
            cout << "结束与 " << currentNPC_->getName() << " 的对话。" << endl;
            inConversation_ = false;
            currentNPC_ = nullptr;
        } else {
            // 转给 NPC 处理（如商店的“查看商品”、“购买 <商品名>”等）
            auto resp = currentNPC_->respondToPlayer(input, openAIClient_.get());
            cout << resp << endl;
        }
    }
    
}



void GameEngine::shutdown(){
    cout << "Game shutting down. Goodbye!" << endl;
}





















