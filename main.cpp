#include <iostream>
#include <memory>
#include "GameEngine.h"


int main() {
    std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>();

    if (!engine->initialize())
    {
        std::cerr << "Loading Failed!" << std::endl;
        return 1;
    }
    
    engine->run();

    engine->shutdown();

    return 0;
}






#include "GameEngine.h"

int main() {
    GameEngine engine;
    if (!engine.initialize()) return -1;
    engine.run();
    engine.shutdown();
    return 0;
}

