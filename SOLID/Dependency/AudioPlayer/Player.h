#ifndef _PLAYER_H_
#define _PLAYER_H_

namespace Pattern
{
    template <typename Engine>
    class Player 
    {
        using sound_type = typename Engine::Sound;

        Engine eng;
    public:

        void play(sound_type& _sound);
        void play();

        void remove(sound_type& _sound);

        void pause();
        void resume();
        void stop();

        void update();
        void sleep(int ms);

        template <typename SetOption>
        decltype(auto) set(SetOption&& option)
        {
            return option.set(eng);
        }

        template <typename GetOption>
        decltype(auto) get(GetOption&& option)
        {
            return option.get(eng);
        }

    };


    template<typename Engine>
    void Player<Engine>::update() { eng.update(); }

    template<typename Engine>
    void Player<Engine>::sleep(int ms)
    {
        if (ms < 0) {   return;        }
        eng.sleep(ms);
    }

    template<typename Engine>
    void Player<Engine>::pause() { eng.pause(); }

    template<typename Engine>
    void Player<Engine>::resume() { eng.resume(); }

    template<typename Engine>
    void Player<Engine>::stop() { eng.stop(); }

    template<typename Engine>
    void Player<Engine>::play(sound_type& _sound) { eng.play(_sound); }

    template<typename Engine>
    void Player<Engine>::play() {   eng.play(); }

    template<typename Engine>
    void Player<Engine>::remove(sound_type & _sound)
    {
        eng.remove(_sound);
    }

}// namespace Pattern

#endif
