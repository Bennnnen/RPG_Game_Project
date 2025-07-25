#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:
    // 构造：设置初始值（默认为 0）
    Resources(double stone  = 0.0,
              double robber = 0.0,
              double iron   = 0.0,
              double wood   = 0.0,
              double money  = 0.0)
    {
        data_["stone"]  = stone;
        data_["robber"] = robber;
        data_["iron"]   = iron;
        data_["wood"]   = wood;
        data_["money"]  = money;
    }

    virtual ~Resources() = default;

    // 获取指定资源的当前数量（不存在则返回 0）
    double getResource(const std::string& name) const {
        auto it = data_.find(name);
        return (it != data_.end()) ? it->second : 0.0;
    }

    // 增加指定资源
    void addResource(const std::string& name, double amount) {
        data_[name] += amount;
    }

    // 扣除指定资源（不足则归零）
    void consumeResource(const std::string& name, double amount) {
        double have = getResource(name);
        data_[name] = (have > amount) ? (have - amount) : 0.0;
    }

    // 获取所有资源及其数量（只读）
    const std::map<std::string,double>& allResources() const {
        return data_;
    }

private:
    std::map<std::string,double> data_;  // 存储资源名称 → 数量
};

#endif 

