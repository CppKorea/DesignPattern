#include "./game.h"

using namespace std;
using namespace magic;
using namespace chrono;
using namespace Pattern;

int main() 
{
    InGameSystem game{};

    stop_watch<high_resolution_clock> sw{};

    game.resume();
    // Game Loop
    while (game)
    {
        auto elapsed = sw.pick();

        game.processInput();
        game.update(elapsed);
        game.render();
    }

    
    return std::system("pause");
}
