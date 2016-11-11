#include "./EngineYSE.h"
#include "EngineirrKlang.h"

namespace Pattern
{
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    EngineYSE::Sound EngineYSE::Load(std::string && _fpath)
    {
        return EngineYSE::Sound{ _fpath.c_str() };
    }

    EngineYSE::EngineYSE()
    {
        YSE::System().init();
    }

    EngineYSE::~EngineYSE()
    {
        try {
            YSE::System().close();
        }
        catch (...) {}
    }



    void EngineYSE::play(EngineYSE::Sound & _sound)
    {
        // Alias + Mapping

        // Argument check
        if (_sound.is_valid() == false && _sound.is_playing()) {
            return;
        }
        _sound.play_impl();

        // Insert into list for pause/resume support
        auto iter = std::find(sounds.begin(), sounds.end(), _sound);
        
        // Not found
        if (iter == sounds.end()) {
            sounds.emplace_back(_sound);
        }
    
    }

    void EngineYSE::play()
    {
        for (auto& snd : sounds) {
            snd.play_impl();
        }
    }

    void EngineYSE::remove(EngineYSE::Sound & _sound)
    {
        auto iter = std::find(sounds.begin(), sounds.end(), _sound);
        // Found
        if (iter != sounds.end()) {
            sounds.erase(iter);
        }
    }

    void EngineYSE::stop()
    {
        for (auto& snd : sounds) {
            snd.stop_impl();
        }
    }

    void EngineYSE::pause()
    {
        for (auto& snd : sounds) {
            snd.pause_impl();
        }
    }

    void EngineYSE::resume()
    {
        for (auto& snd : sounds) 
        {
            snd.resume_impl();
        }
    }

    void EngineYSE::update()
    {
        YSE::System().update();
    }

    void EngineYSE::sleep(int ms)
    {
        if (ms > 0) {
            YSE::System().sleep(ms);
        }
    }


    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    void EngineYSE::Sound::play_impl()
    {
        if (is_valid() == true) {
            impl->play();
        }
    }

    void EngineYSE::Sound::pause_impl()
    {
        if (is_valid() == true) {
            impl->pause();
        }
    }

    void EngineYSE::Sound::resume_impl()
    {
        if (is_valid() && impl->isPaused() ) {
            impl->toggle();
        }
    }

    void EngineYSE::Sound::stop_impl()
    {
        if (is_valid() == true) {
            impl->stop();
        }
    }


    EngineYSE::Sound::Sound(const char * _fname)
    {
        ref  = new uint32_t{1};
        impl = new YSE::sound{};
        impl->create(_fname, nullptr, true);
    }

    EngineYSE::Sound::~Sound()
    {
        if (*ref > 1) {
            *ref -= 1;
        }
        else {
            delete ref;
            delete impl;
        }
    }



    EngineYSE::Sound::Sound(Sound & _rhs):
        ref{_rhs.ref}, 
        impl{_rhs.impl}
    {
        *ref += 1;
    }


    EngineYSE::Sound & EngineYSE::Sound::operator=(Sound & _rhs)
    {
        ref  = _rhs.ref;
        impl = _rhs.impl;
        *ref += 1;

        return *this;
    }


    bool EngineYSE::Sound::operator==(const Sound & _rhs) noexcept
    {
        return _rhs.impl == this->impl;
    }


    bool EngineYSE::Sound::is_valid() noexcept
    {
        return (impl != nullptr) && (impl->isValid());
    }

    bool EngineYSE::Sound::is_playing() noexcept
    {
        return impl->isPlaying() ;
    }

    bool EngineYSE::Sound::is_paused() noexcept
    {
        return impl->isPaused();
    }



namespace Option 
{

    void Volume::set(EngineYSE & _engine)
    {
        for (auto& snd : _engine.sounds) 
        {
            const auto vol = snd.impl->getVolume() + increment;
            snd.impl->setVolume(vol);
        }
    }

    float Volume::get(EngineYSE & _engine)
    {
        float res{};
        auto& list = _engine.sounds;
        for (auto& snd : list) {
            res += snd.impl->getVolume();
        }

        return res / list.size();
    }

}// namespace Option
}// namespace Pattern
