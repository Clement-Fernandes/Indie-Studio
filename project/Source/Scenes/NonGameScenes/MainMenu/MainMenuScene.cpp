/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** MainMenuScene
*/

#include <functional>

#include "tools.hpp"
#include "MainMenuScene.hpp"

#include "FileError.hpp"


void Scene::MainMenuScene::exitScene(void)
{
    _nextScene = Scene::Scenes::QUIT;
}

void Scene::MainMenuScene::gameScene(void)
{
    _nextScene = Scene::Scenes::GAME;
}

void Scene::MainMenuScene::newGameScene(void)
{
    _nextScene = Scene::Scenes::GAME;
}

Scene::MainMenuScene::MainMenuScene(std::shared_ptr<Settings> settings) : AScene(settings)
{
    std::vector<std::function<void(void)>> callBacks = {std::bind(&Scene::MainMenuScene::newGameScene, this), std::bind(&Scene::MainMenuScene::gameScene, this), std::bind(&Scene::MainMenuScene::exitScene, this)};

    _buttons = loadObjects<Object::Button>("Conf/Scenes/MainMenu/button.json");
    for (std::size_t index = 0; index !=_buttons.size(); index++) {
        _buttons.at(index)->setCallBack(callBacks.at(index));
    }
    _images = loadObjects<Object::Image>("Conf/Scenes/MainMenu/image.json");
    _texts = loadObjects<Object::Text>("Conf/Scenes/MainMenu/text.json");

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

    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    return _nextScene;
}

void Scene::MainMenuScene::draw()
{
    std::float_t speed = 0.0;

    for (std::int8_t i = 0; i < 10; i++) {
        if (i % 2 == 0)
            speed += 0.1;

        _images.at(i)->setPosition(_images.at(i)->getPosition().getX() - speed, _images.at(i)->getPosition().getY());

        if (_images.at(i)->getPosition().getX() <= -1930)
            _images.at(i)->setPosition(1928, _images.at(i)->getPosition().getY());
    }

    for (auto &image : _images)
        image->draw();
    for (auto &text : _texts)
        text->draw();
    for (auto &button : _buttons)
        button->draw();
}
