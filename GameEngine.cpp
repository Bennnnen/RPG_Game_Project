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
    string response = openAIClient_->generateStorySegment(input);

    cout << "The story developed: " << response << endl;
}



void GameEngine::shutdown(){

}




















// GameEngine.cpp
#include "GameEngine.h"

bool GameEngine::initialize() {
    player_       = std::make_unique<Player>("Hero", "High");
    openAIClient_ = std::make_unique<OpenAIClient>(/* api key */);

    initializeNPCs();     // 注册所有 NPC
    isRunning_ = true;
    return true;
}

void GameEngine::initializeNPCs() {
    // 商人 NPC
    auto shop = std::make_unique<ShopkeeperNPC>(
        "Shopkeeper",
        "热情的商人，出售各种装备。",
        "你是一位富有想象力的商人，随机挑选并售卖装备给玩家。"
    );
    // 注入 player
    shop->setPlayer(player_.get());
    // 先放到容器，再映射名字到指针
    npcMap_[shop->getName()] = shop.get();
    npcs_.push_back(std::move(shop));

    // 如果还有别的 NPC，同样在这里注册：
    // auto other = make_unique<OtherNPC>(...);
    // npcMap_[other->getName()] = other.get();
    // npcs_.push_back(move(other));
}

void GameEngine::run() {
    std::string line;
    while (isRunning_) {
        if (!inConversation_) {
            // 当前不在对话，先让玩家选一个 NPC
            showNPCMenu();
            std::getline(std::cin, line);
            if (line == "exit") { isRunning_ = false; break; }
            NPC* npc = findNPC(line);
            if (npc) startConversation(npc);
            continue;
        }

        // 已经和 currentNPC_ 对话中
        std::getline(std::cin, line);
        if (line == "exit") { isRunning_ = false; break; }
        if (line == "quit") { endConversation(); continue; }
        // 普通交互，交给 NPC 处理
        std::cout << currentNPC_->respondToPlayer(line, openAIClient_.get()) 
                  << std::endl;
    }
}

void GameEngine::shutdown() {
    // 这里可以做资源清理
}

// 列出所有 NPC 名称
void GameEngine::showNPCMenu() const {
    std::cout << "可交互的 NPC 列表：" << std::endl;
    listAvailableNPCs();
    std::cout << "输入 NPC 名称，或输入 'exit' 退出。" << std::endl;
}

void GameEngine::listAvailableNPCs() const {
    for (auto& kv : npcMap_) {
        std::cout << " - " << kv.first << std::endl;
    }
}

// 名字查找 NPC*
NPC* GameEngine::findNPC(const std::string& name) const {
    auto it = npcMap_.find(name);
    return (it != npcMap_.end()) ? it->second : nullptr;
}

// 开始与某个 NPC 对话
void GameEngine::startConversation(NPC* npc) {
    currentNPC_ = npc;
    inConversation_ = true;
    std::cout << npc->getGreeting() << std::endl;
    std::cout << npc->getHelp() << std::endl;
}

// 结束当前对话
void GameEngine::endConversation() {
    if (!inConversation_) return;
    std::cout << "结束与 " << currentNPC_->getName() << " 的对话。" << std::endl;
    currentNPC_ = nullptr;
    inConversation_ = false;
}

void GameEngine::handlePlayerInput(const std::string& input) {
    // 上面 run() 里已经按对话状态分发，不再需要这里做额外处理
}