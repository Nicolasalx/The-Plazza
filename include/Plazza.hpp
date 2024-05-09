/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Plazza
*/

#ifndef PLAZZA_HPP_
    #define PLAZZA_HPP_

    #include <thread>
    #include "Clock.hpp"

namespace Pla
{
    enum class PizaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum class PizaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum class Ingredient
    {
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        Eggplant,
        GoatCheese,
        ChiefLove,
        NbIngredient
    };

    struct Order
    {
        Pla::PizaType type = Pla::PizaType::Regina;
        Pla::PizaSize size = Pla::PizaSize::S;
    };

    static constexpr std::array<double, 4> coocking_time = {1000, 2000, 2000, 4000};
}

#endif /* !PLAZZA_HPP_ */
