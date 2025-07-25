#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <string>
#include <vector>
#include "OpenAIClient.h"
#include "Player.h"
using namespace std;

/*
 * 抽象 NPC 基类：统一接口，集成 AI 对话和话题管理
 */
class NPC {
public:
    NPC(const string& name,
        const string& description,
        const string& systemPrompt)
        :name_(name), description_(description), systemPrompt_(systemPrompt){};
    virtual ~NPC() = default;

    // 属性访问
    string getName() const;
    string getDescription() const;
    string getSystemPrompt() const;
    bool isAvailable() const;
    void setAvailable(bool avail);

    // 话题管理
    void addTopic(const std::string& topic);
    vector<string> getAvailableTopics() const;

    // 对话接口
    virtual string getGreeting() const;
    virtual string getHelp() const;
    virtual string respondToPlayer(const string& input, OpenAIClient* aiClient);

protected:
    string name_;
    string description_;
    string systemPrompt_;
    vector<string> availableTopics_;
    bool isAvailable_;
};

#endif