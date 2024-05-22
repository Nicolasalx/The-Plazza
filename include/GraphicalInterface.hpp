/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** GraphicalInterface
*/

#ifndef GRAPHICALINTERFACE_HPP_
    #define GRAPHICALINTERFACE_HPP_

    #include "ComKitchen.hpp"
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <cmath>
    #include <map>

    #define WIDTH 1400
    #define HEIGHT 1080

namespace Pla
{
    class GraphicalInterface
    {
        struct pos_box_t {
            int x = 10.0f;
            int y = 5.0f;
        };

        struct all_data_kitchen_t
        {
            std::vector<sf::Sprite> listIngredients;
            std::vector<sf::Text> listText;           
        };

        struct kitchen_t
        {
            std::size_t id;
            sf::RectangleShape rectangle;
            sf::Text text;
            all_data_kitchen_t all_data;
            Pla::ComKitchen infos;
            bool orderIsEmpty = false;
        };

        public:
            GraphicalInterface() = default;
            ~GraphicalInterface() = default;

            void launch(const std::list<Pla::ComKitchen> &kitchen_list, std::mutex &mutex, std::atomic_bool &exit);
            void addEachKitchen(const std::list<Pla::ComKitchen> &kitchen_list, std::mutex &mutex);
            void manageKitchen(const std::list<Pla::ComKitchen> &kitchen_list, std::mutex &mutex);
            void initFont();
            void handleEvent(sf::RenderWindow &window);
            void drawInfosKitchen(sf::RenderWindow &window);
            void initTexture();
            sf::Texture loadATexture(const std::string &filepath);
            void createWindowDataKitchen(const Pla::ComKitchen &kitch, kitchen_t &kitchen, int &xAxis, int &yAxis);
            void selectIngredient(const Pla::Ingredient &ingredient, sf::Sprite &sprite);
            void displayCookInfos(const Pla::ComKitchen &kitch, kitchen_t &kitchen, int &xAxis, int &yAxis);
            void createGrid(float boxWidth, float boxHeight, int columns, kitchen_t &kitchen, const Pla::ComKitchen &kitch, std::size_t index);
            void printAllKitchen(sf::RenderWindow &window, sf::Vector2f &mousePosF);

        private:
            std::map<std::string, sf::Texture> _allTexture;

            std::vector<kitchen_t> _listKitchen;
            std::size_t _nbKitchen = 0;
            sf::Font _font;
            pos_box_t _pos_box;
            bool _mousePressed = false;
            int _kitchenIdx = -1;
            bool _kitchenHasBeenSelected = false;
            Pla::GraphicalInterface::kitchen_t _kitchenSelectionned;
    };
}

#endif /* !GRAPHICALINTERFACE_HPP_ */
