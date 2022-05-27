/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "MainMenuScene.hpp"

void Scene::MainMenuScene::exitScene(void)
{
    _nextScene = Scene::Scenes::QUIT;
}

void Scene::MainMenuScene::settingsScene(void)
{
    _nextScene = Scene::Scenes::SETTINGS;
}

void Scene::MainMenuScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::GAME;
}

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    _objects = loadObject("Conf/object.json");
    // _buttons.emplace(Scene::BUTTONSNAME::NEWGAME, std::make_unique<Object::Button>("Save/button.png", 3, std::bind(&Scene::MainMenuScene::newGameScene, this), "Save/assets_sound_Click.ogg", Position(700, 300, 0)));
    // _buttons.emplace(Scene::BUTTONSNAME::EXIT, std::make_unique<Object::Button>("Save/button.png", 3, std::bind(&Scene::MainMenuScene::exitScene, this),"Save/assets_sound_Click.ogg", Position(700, 500, 0)));
    // _buttons.emplace(Scene::BUTTONSNAME::SETTINGS, std::make_unique<Object::Button>("Save/button.png", 3, std::bind(&Scene::MainMenuScene::settingsScene, this),"Save/assets_sound_Click.ogg", Position(700, 800, 0)));
    _nextScene = Scene::Scenes::MAIN_MENU;

}

Scene::MainMenuScene::~MainMenuScene()
{
}

void Scene::MainMenuScene::fadeBlack()
{

}

Scene::Scenes Scene::MainMenuScene::handelEvent()
{
    _nextScene = Scene::Scenes::MAIN_MENU;
    for (auto button : _objects)
        button->handleEvent(_settings);

    return _nextScene;
}

void Scene::MainMenuScene::draw()
{
    for (auto &button : _objects)
        button->draw();
}
