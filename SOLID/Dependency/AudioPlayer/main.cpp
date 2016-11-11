
#include <iostream>
#include <cstdlib>
#include <conio.h>

#include "./Player.h"
#include "./Engine/EngineYSE.h"

using namespace std;
using namespace Pattern;


int main() {

    {


        Player<EngineYSE> player{};

        EngineYSE::Sound music = EngineYSE::Load("./IWBTB_Boss5_Sonic.ogg");
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

/*
#include <iostream>
#include <cstdlib>
#include "yse.hpp"
#if defined YSE_WINDOWS
#include <conio.h>
#else
//#include "wincompat.h"
#endif

YSE::sound sound;

int main() {
    // initialize audio system
    YSE::System().init();

    // load a sound in memory
    sound.create("./IWBTB_Boss5_Sonic.ogg", NULL, true);

    // false on validation means the sound could not be loaded
    if (!sound.isValid()) {
        std::cout << "sound not found" << std::endl;
        std::cin.get();
        goto exit;
    }

    std::cout << "This is a bare-bones YSE example. It contains the minimum you need to start your own projects." << std::endl;
    std::cout << "Press spacebar to toggle sound playing." << std::endl;
    std::cout << "Or e to exit." << std::endl;

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
                // toggle function toggles play / pause
            case ' ': sound.toggle(); break;
            case 'a': sound.play(); break;
            case 's': sound.pause(); break;
            case 'd': sound.stop(); break;
            case 'e': goto exit;
            }
        }


        YSE::System().sleep(100);


        YSE::System().update();
    }

exit:
    // don't forget this...
    YSE::System().close();
    return 0;
}
*/