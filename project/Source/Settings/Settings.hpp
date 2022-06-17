/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
    #define SETTINGS_HPP_

    #include <nlohmann/json.hpp>

    #include <memory>
    #include <map>
    #include <utility>
    #include <vector>

    #include "Audio.hpp"
    #include "Camera.hpp"
    #include "Window.hpp"

    #include "Music.hpp"
    #include "MySound.hpp"

enum class Action {
    Next,
    Previous,
    Right,
    Left,
    Up,
    Down
};
enum class PlayerAction {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Drop
};

enum MusicsEnum {
    Menu,
    PlayerSelectMenu,
    Game,
    EndGame
};

enum SoundsEnum {
    BombExplosion,
    BombDrop,
    Bonus
};

class Settings {
    public:
        Settings(nlohmann::json const &jsonData);
        ~Settings();

        std::shared_ptr<RayLib::Window> getWindow() const;
        std::shared_ptr<RayLib::Audio> getAudio() const;
        std::shared_ptr<RayLib::CinematicCamera> getCamera() const;
        void setActionPressed(std::map<Action, bool> const &actionPressed);
        void setPlayerActionsPressed(std::vector<std::map<PlayerAction, bool>> const &playerAction);
        std::map<Action, bool> getActionPressed() const;
        std::vector<std::map<PlayerAction, bool>> getPlayerActionsPressed() const;

        void playMusic(const MusicsEnum &music);
        void updateMusicStream(const MusicsEnum &music);
        void stopMusic(const MusicsEnum &music);

        void playSound(const SoundsEnum &sound);
        void stopSound(const SoundsEnum &sound);

        void applySoundVolume(float volume);
        void applyMusicVolume(float volume);

        float getSoundVolume() const;
        float getMusicVolume() const;

        std::size_t getSaveIndex() const;
        void incrementSaveIndex();
        void resetSaveIndex();

        void updateSettingsDatas(std::string const &filepath);

    protected:
    private:
        std::shared_ptr<RayLib::Window> _window;
        std::shared_ptr<RayLib::Audio> _audio;
        std::shared_ptr<RayLib::CinematicCamera> _camera;

        std::vector<std::unique_ptr<MyMusic>> _musics;
        std::vector<std::unique_ptr<MySound>> _sounds;

        std::map<Action, bool> _actionPressed;
        std::vector<std::map<PlayerAction, bool>> _playerActions;
        std::map<PlayerAction, bool> _playerAction;
        float _soundVolume;
        float _musicVolume;
        std::size_t _saveIndex;
};

#endif /* !SETTINGS_HPP_ */
