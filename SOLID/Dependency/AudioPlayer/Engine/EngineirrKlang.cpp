#include "./EngineirrKlang.h"

using namespace irrklang;

namespace Pattern
{
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    std::uint32_t & EngineirrKlang::RefCount()
    {
        static uint32_t count{ 0 };
        return count;
    }

    irrklang::ISoundEngine & EngineirrKlang::getDevice()
    {
        static irrklang::ISoundEngine* engine = createIrrKlangDevice();
        return *engine;
    }


    EngineirrKlang::Sound EngineirrKlang::Load(std::string && _fpath)
    {
        auto& device = EngineirrKlang::getDevice();
        ISound* snd = device.play2D(_fpath.c_str(), false, true, true);
        return EngineirrKlang::Sound{ snd };
    }


    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


    EngineirrKlang::EngineirrKlang()
    {
        RefCount() += 1;
    }

    EngineirrKlang::~EngineirrKlang()
    {
        RefCount() -= 1;
        if (RefCount() == 0) {
            getDevice().drop();
        }
    }

    void EngineirrKlang::play(EngineirrKlang::Sound & _sound)
    {
        _sound.play_impl();
    }

    void EngineirrKlang::play()
    {
        getDevice().setAllSoundsPaused(false);
    }

    void EngineirrKlang::remove(EngineirrKlang::Sound & _sound)
    {
        getDevice().removeSoundSource(_sound.impl->getSoundSource());
    }

    void EngineirrKlang::stop()
    {
        getDevice().stopAllSounds();
    }

    void EngineirrKlang::pause()
    {
        getDevice().setAllSoundsPaused(true);
    }

    void EngineirrKlang::resume()
    {
        getDevice().setAllSoundsPaused(false);
    }

    void EngineirrKlang::update()
    {
        getDevice().update();
    }

    void EngineirrKlang::sleep(int ms)
    {
        return;
    }







    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    EngineirrKlang::Sound::Sound(irrklang::ISound * _pimpl):
        impl{_pimpl}
    {
    }


    void EngineirrKlang::Sound::play_impl()
    {
        impl->setIsPaused(false);
    }
    void EngineirrKlang::Sound::pause_impl()
    {
        impl->setIsPaused();
    }
    void EngineirrKlang::Sound::resume_impl()
    {
        impl->setIsPaused(false);
    }
    void EngineirrKlang::Sound::stop_impl()
    {
        impl->stop();
    }

    bool EngineirrKlang::Sound::is_valid()     noexcept
    {
        return impl != nullptr;
    }

    bool EngineirrKlang::Sound::is_playing()   noexcept
    {
        return impl->isFinished() == false;
    }

    bool EngineirrKlang::Sound::is_paused()    noexcept
    {
        return impl->getIsPaused();
    }


namespace Option
{

    void Volume::set(EngineirrKlang & _engine)
    {
        auto& device = EngineirrKlang::getDevice();
        const auto vol = device.getSoundVolume() + increment;
        if (vol > 1.0) {
            device.setSoundVolume(1.0);
        }
        else {
            device.setSoundVolume(vol);
        }
        
    }

    float Volume::get(EngineirrKlang & _engine)
    {
        auto& device = EngineirrKlang::getDevice();

        return device.getSoundVolume();
    }

}// namespace Option
}// namespace Pattern


