
#include <iostream>
#include <cstdlib>
#include <conio.h>

#include "./Player.h"
#include "./Engine/EngineYSE.h"
//#include "./Engine/EngineirrKlang.h"
using namespace std;
using namespace Pattern;


int main(void) {
    using Engine = EngineYSE;

    {
        Player<Engine> player{};

        Engine::Sound music = Engine::Load("../Resource/IWBTB_Boss5_Sonic.ogg");

        if (music.is_valid() == false) {
            std::cerr << "Loading failed" << std::endl;
            return std::system("pause");
        }

        player.play(music);

        while (true)
        {
            if (_kbhit()) {
                char ch = _getch();
                switch (ch)
                {
                case 'y': player.play();                        break;
                case 'p': player.pause();                       break;
                case 's': player.stop();                        break;
                case 'r': player.resume();                      break;
                case 'u': player.set(Option::Volume{ 0.5 });    break;
                case 'd': player.set(Option::Volume{ -0.5 });   break;
                case 'q': 
                    player.stop();
                    goto Exit;
                }
            }
    
            player.sleep(300);

            player.update();

        }
    }
Exit:
    return std::system("pause");
}
