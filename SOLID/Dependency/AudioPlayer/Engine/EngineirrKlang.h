#ifndef _ENGINE_IRRKLANG_H_
#define _ENGINE_IRRKLANG_H_


#include <string>
#include "irrKlang.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

namespace Pattern
{

    namespace Option
    {
        class Volume;
    }


    class EngineirrKlang 
    {
        friend class Option::Volume;

        static std::uint32_t&          RefCount();
        static irrklang::ISoundEngine& getDevice();


    public: // ---- ---- ---- ---- ----
        class Sound;


    public: // ---- ---- ---- ---- ----
        static Sound Load(std::string&& _fpath);

    public:
        EngineirrKlang();
        ~EngineirrKlang();

        void play(EngineirrKlang::Sound& _sound);
        void play();
        void remove(EngineirrKlang::Sound& _sound);

        void stop();
        void pause();
        void resume();
        void update();

        void sleep(int ms);

    
    };

    class EngineirrKlang::Sound
    {
        friend class EngineirrKlang;

        irrklang::ISound* impl = nullptr;
    private:
        void play_impl();
        void pause_impl();
        void resume_impl();
        void stop_impl();

        explicit Sound(irrklang::ISound*);
    public:
        ~Sound() = default;

        Sound(Sound&) = default;
        Sound& operator=(Sound&) = default;

        bool is_valid()     noexcept;
        bool is_playing()   noexcept;
        bool is_paused()    noexcept;
    };


    /*
    namespace Option
    {
        class Volume
        {
            float increment;
        public:
            explicit Volume(float _inc) :increment{ _inc } {}

            void    set(EngineirrKlang& _engine);
            float   get(EngineirrKlang& _engine);

        };

    }// namespace Option
    */
}// namespace Pattern

#endif
