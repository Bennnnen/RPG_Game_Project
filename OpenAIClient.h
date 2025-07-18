//
// Created by 陈佳民 on 25-6-28.
//
#ifndef OPENAICLIENT_H
#define OPENAICLIENT_H

#include <string>
#include "json.hpp"

class OpenAIClient {
private:
    std::string apiKey_;

public:
    OpenAIClient(const std::string& apiKey) : apiKey_(apiKey) {}
    std::string generateStorySegment(const std::string& playerAction);
};

#endif
