/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** graphicalInterface
*/

#include "GraphicalInterface.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>

void Pla::GraphicalInterface::selectIngredient(const Pla::Ingredient &ingredient, sf::Sprite &sprite)
{
    switch (ingredient) {
        case Pla::Ingredient::Tomato:
            sprite.setTexture(_allTexture["tomato"]);
            sprite.setScale(sf::Vector2f{0.2, 0.2});
            break;
        case Pla::Ingredient::Gruyere:
            sprite.setTexture(_allTexture["gruyere"]);
            sprite.setScale(sf::Vector2f{0.15, 0.15});
            break;
        case Pla::Ingredient::Ham:
            sprite.setTexture(_allTexture["ham"]);
            sprite.setScale(sf::Vector2f{0.15, 0.15});
            break;
        case Pla::Ingredient::Mushrooms:
            sprite.setTexture(_allTexture["mushrooms"]);
            sprite.setScale(sf::Vector2f{0.15, 0.15});
            break;
        case Pla::Ingredient::Steak:
            sprite.setTexture(_allTexture["steak"]);
            sprite.setScale(sf::Vector2f{0.1, 0.1});
            break;
        case Pla::Ingredient::Eggplant:
            sprite.setTexture(_allTexture["eggplant"]);
            sprite.setScale(sf::Vector2f{0.2, 0.2});
            break;
        case Pla::Ingredient::GoatCheese:
            sprite.setTexture(_allTexture["goatcheese"]);
            sprite.setScale(sf::Vector2f{0.15, 0.15});
            break;
        case Pla::Ingredient::ChiefLove:
            sprite.setTexture(_allTexture["chieflove"]);
            sprite.setScale(sf::Vector2f{0.2, 0.2});
            break;
        default:
            break;
    }
}

void Pla::GraphicalInterface::createWindowDataKitchen(const Pla::ComKitchen &kitch, kitchen_t &kitchen, int &xAxis, int &yAxis)
{
    for (size_t i = 0; i < 8; ++i) {
        sf::Sprite sprite;
        sf::Text text;
        int ingredientCount = kitch.ingredient[i];

        selectIngredient(Pla::Ingredient(i), sprite);

        std::string nbIngredient = std::to_string(ingredientCount);
        text.setFont(_font);
        text.setString(nbIngredient);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

        sprite.setPosition(xAxis, yAxis += 70);
        text.setPosition(xAxis + 100, yAxis);
        kitchen.all_data.listIngredients.push_back(sprite);
        kitchen.all_data.listText.push_back(text);
    }
}

void Pla::GraphicalInterface::displayCookInfos(const Pla::ComKitchen &kitch, kitchen_t &kitchen, int &xAxis, int &yAxis)
{
    int nb_cook_disp = 0;

    for (const Pla::Order &order : kitch.order_) {
        if (order.state == Pla::PizzaState::WAITING_INGREDIENT || order.state == Pla::PizzaState::CURRENTLY_COOKING) {
            sf::Text text;
            std::ostringstream oss;
            oss << "    Cook " << nb_cook_disp << ": Order " << order.nb
                << ":\n"
                << order.type << ' ' << order.size << std::endl;
            std::string result = oss.str();
            text.setFont(_font);
            text.setString(result);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            text.setPosition(xAxis - 50, yAxis += 50);
            kitchen.all_data.listText.push_back(text);
            ++nb_cook_disp;
        }
    }
}

void Pla::GraphicalInterface::createGrid(float boxWidth, float boxHeight, int columns, kitchen_t &kitchen, const Pla::ComKitchen &kitch, std::size_t index)
{
    sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
    int row = index / columns;
    int col = index % columns;
    int x_axis = col * boxWidth;
    int y_axis = row * boxHeight;

    box.setPosition(x_axis, y_axis);
    box.setFillColor(sf::Color(0, 170, 255));
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);
    kitchen.rectangle = box;
    std::string strKitchen = "Kitchen Id:\n" + std::to_string(kitch.pid);
    kitchen.text.setFont(_font);
    kitchen.text.setString(strKitchen);
    kitchen.text.setCharacterSize(20);
    kitchen.text.setFillColor(sf::Color::White);
    kitchen.text.setStyle(sf::Text::Bold);
    kitchen.text.setPosition(x_axis, y_axis += 25);
    kitchen.id = kitch.pid;
    kitchen.orderIsEmpty = kitch.order_.empty();
}

void Pla::GraphicalInterface::addEachKitchen(const std::list<Pla::ComKitchen> &kitchen_list)
{
    if (_nbKitchen == 0) {
        _kitchenSelectionned.all_data.listIngredients.clear();
        _kitchenSelectionned.all_data.listText.clear();
        return;
    }

    int columns = static_cast<int>(std::sqrt(_nbKitchen));
    int rows = (_nbKitchen + columns - 1) / columns;
    float boxWidth = 1120 / columns;
    float boxHeight = 1020 / rows;
    std::size_t index = 0;

    for (const auto &kitch : kitchen_list) {
        kitchen_t kitchen;
        int xAxis = 1200;
        int yAxis = -50;
        createGrid(boxWidth, boxHeight, columns, kitchen, kitch, index);
        createWindowDataKitchen(kitch, kitchen, xAxis, yAxis);
        displayCookInfos(kitch, kitchen, xAxis, yAxis);
        _listKitchen.push_back(kitchen);
        ++index;
    }
}

void Pla::GraphicalInterface::manageKitchen(const std::list<Pla::ComKitchen> &kitchen_list, std::mutex &mutex)
{
    mutex.lock();
    std::size_t numberOfKitchen = kitchen_list.size();
    mutex.unlock();

    _listKitchen.clear();
    _nbKitchen = numberOfKitchen;
    mutex.lock();
    addEachKitchen(kitchen_list);
    mutex.unlock();
}

void Pla::GraphicalInterface::initFont()
{
    std::string fontPath = "./fonts/Borniarte.ttf";

    if (!std::filesystem::exists(fontPath)) {
        std::cerr << "Font file does not exist at path: " << fontPath << std::endl;
        return;
    }
    if (!_font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font from path: " << fontPath << std::endl;
        return;
    }
}

void Pla::GraphicalInterface::handleEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            _mousePressed = true;
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            _mousePressed = false;
        }
    }
}

void Pla::GraphicalInterface::drawInfosKitchen(sf::RenderWindow &window)
{
    for (const auto &ingredient: _kitchenSelectionned.all_data.listIngredients) {
        window.draw(ingredient);
    }
    for (const auto &text: _kitchenSelectionned.all_data.listText) {
        window.draw(text);
    }
}

sf::Texture Pla::GraphicalInterface::loadATexture(const std::string &filepath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filepath)) {
        return texture;
    }
    return texture;
}

void Pla::GraphicalInterface::initTexture()
{
    _allTexture["eggplant"] = loadATexture("./assets/eggplant.jpg");
    _allTexture["goatcheese"] = loadATexture("./assets/goatcheese.png");
    _allTexture["gruyere"] = loadATexture("./assets/gruyere.png");
    _allTexture["ham"] = loadATexture("./assets/ham.jpg");
    _allTexture["chieflove"] = loadATexture("./assets/chieflove.png");
    _allTexture["mushrooms"] = loadATexture("./assets/mushrooms.png");
    _allTexture["steak"] = loadATexture("./assets/steak.jpg");
    _allTexture["tomato"] = loadATexture("./assets/tomato.png");
}

void Pla::GraphicalInterface::printAllKitchen(sf::RenderWindow &window, sf::Vector2f &mousePosF)
{
    int idx = 0;
    for (auto &kitchen : _listKitchen) {
        if (kitchen.rectangle.getGlobalBounds().contains(mousePosF) && _mousePressed) {
            _kitchenIdx = idx;
            _kitchenSelectionned = kitchen;
            _kitchenHasBeenSelected = true;
        } else if (kitchen.rectangle.getGlobalBounds().contains(mousePosF) && !_mousePressed) {
            kitchen.rectangle.setFillColor(sf::Color(0, 50, 255));
        } else if (kitchen.orderIsEmpty) {
            kitchen.rectangle.setFillColor(sf::Color(255, 0, 0));
        } else if (idx == _kitchenIdx) {
            kitchen.rectangle.setFillColor(sf::Color(0, 204, 0));
        } else {
            kitchen.rectangle.setFillColor(sf::Color(204, 204, 0));
        }
        window.draw(kitchen.rectangle);
        window.draw(kitchen.text);
        ++idx;
    }
    drawInfosKitchen(window);
}

void Pla::GraphicalInterface::launch(const std::list<Pla::ComKitchen> &kitchen_list, std::mutex &mutex)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "The plazza management");
    sf::RectangleShape middleBar(sf::Vector2f(100.f, 100.f));
    Pla::GraphicalInterface::kitchen_t kitchenSelectionned;

    window.setFramerateLimit(60);
    middleBar.setPosition((WIDTH * 0.8), 0.f);
    middleBar.setFillColor(sf::Color::White);
    middleBar.setScale(sf::Vector2f(0.1, 30.f));
    initFont();
    initTexture();

    while (window.isOpen()) {
        handleEvent(window);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        window.clear(sf::Color::Black);
        manageKitchen(kitchen_list, mutex);
        printAllKitchen(window, mousePosF);
        window.draw(middleBar);
        window.display();
    }
}
