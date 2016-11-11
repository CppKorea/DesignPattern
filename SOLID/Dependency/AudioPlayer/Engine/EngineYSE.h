#ifndef _ENGINE_YSE_H_
#define _ENGINE_YSE_H_

#include <string>
#include <vector>
#include "yse.hpp"

namespace Pattern
{

    namespace Option
    {
        class Volume;
    }


    class EngineYSE
    {
        friend class Option::Volume;

    public: // ---- ---- ---- ---- ----
        class Sound;


    public: // ---- ---- ---- ---- ----
        static Sound Load(std::string&& _fpath);

    public:

        EngineYSE();
        ~EngineYSE();

        void play(EngineYSE::Sound& _sound);
        void play();
        void remove(EngineYSE::Sound& _sound);

        void stop();
        void pause();
        void resume();
        void update();

        void sleep(int ms);

    private:
        std::vector<Sound> sounds;

    };

    class EngineYSE::Sound
    {
        friend class EngineYSE;
        friend class Option::Volume;

    private:
        uint32_t*   ref  = nullptr;
        YSE::sound* impl = nullptr;

    private:
        void play_impl();
        void pause_impl();
        void resume_impl();
        void stop_impl();

    public:
        explicit Sound(const char* _fname);
        ~Sound();
        
        Sound(Sound&);

        Sound& operator=(Sound&);

        bool operator==(const Sound&) noexcept;

        bool is_valid()     noexcept;
        bool is_playing()   noexcept;
        bool is_paused()    noexcept;

    };


    namespace Option
    {
        class Volume
        {
            float increment;
        public:
            explicit Volume(float _inc) :increment{ _inc } {}

            void    set(EngineYSE& _engine);
            float   get(EngineYSE& _engine);
        };

    }// namespace Option

}// namespace Pattern

#endif
