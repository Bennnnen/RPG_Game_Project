#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "OpenAIClient.h"
#include "external/httplib/httplib.h"
#include <iostream>

using json = nlohmann::json;

const std::string kSystemPrompt = "You are the narrator of a fantasy adventure game. Your task is to describe the detailed story development, environmental changes, and character dialogues based on the player's actions. Do not skip any details. Respond only to the result of the current step. Background: A brave adventurer is traversing a mysterious underground maze in search of the legendary magic treasure.";


std::string clean(const std::string& input) {
    std::string output;
    for (char c : input) {
        if ((unsigned char)c >= 0x20 || c == '\n' || c == '\t') {
            output += c;
        }
    }
    return output;
}

std::string OpenAIClient::generateStorySegment(const std::string& playerAction) {
    httplib::SSLClient cli("api.deepseek.com");
    cli.set_default_headers({
        {"Authorization", "Bearer sk-c72d182938c24428bdb96bf891910a99"},
        {"Content-Type", "application/json"},
        {"Accept", "application/json"}
    });

    json request = {
        {"model", "deepseek-chat"},
        {"messages", {
            {{"role", "system"}, {"content", kSystemPrompt}},
            {{"role", "user"}, {"content", playerAction}}
        }},
        {"frequency_penalty", 0},
        {"max_tokens", 2048},
        {"presence_penalty", 0},
        {"response_format", {{"type", "text"}}},
        {"stream", false},
        {"temperature", 1},
        {"top_p", 1}
    };

    auto res = cli.Post("/v1/chat/completions", request.dump(), "application/json");

    if (res && res->status == 200) {
        try {
            json response = json::parse(res->body);
            if (response.contains("choices") && !response["choices"].empty()) {
                return clean(response["choices"][0]["message"]["content"]);
            } else {
                std::cerr << "Lack of Response Information" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error in parsing JSON" << e.what() << std::endl;
        }
    } else {
        std::cerr << "API Request Failed" << (res ? res->body : "Unknown Error") << std::endl;
    }

    return "The world falls in silence";
}