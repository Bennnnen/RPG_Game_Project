#include "NPC.h"
#include <sstream>

using namespace std;

string NPC::respondToPlayer(const string& playerInput, OpenAIClient* aiClient) {
    if (!aiClient) {
        return "抱歉，我现在无法回应。";
    }

    // 构建完整的提示，包括系统提示和玩家输入
    string fullPrompt = systemPrompt_ + "\n\n玩家说: " +
        playerInput + "\n\n请以" + name_ + "的身份作答：";

    // 使用 AI 客户端生成回应
    return aiClient->generateStorySegment(fullPrompt);
}

string NPC::getGreeting() const {
    return "你好，我是" + name_ + "。" + description_;
}

string NPC::getHelp() const {
    std::stringstream ss;
    ss << name_ << " 可以和你讨论以下话题：\n";
    for (const auto& topic : availableTopics_) {
        ss << "- " << topic << "\n";
    }
    return ss.str();
}

bool NPC::isAvailable() const{ return false;}

void NPC::setAvailable(bool avail){}

void NPC::addTopic(const std::string &topic){}
