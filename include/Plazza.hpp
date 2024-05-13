/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Plazza
*/

#ifndef PLAZZA_HPP_
    #define PLAZZA_HPP_

    #include <thread>
    #include <iostream>
    #include "Clock.hpp"

namespace Pla
{
    enum class PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum class PizzaSize
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

    enum class PizzaState
    {
        WAITING_TO_BE_COOK,
        WAITING_INGREDIENT,
        CURRENTLY_COOKING,
        DONE
    };
}

std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaType &pizza_type);
std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaSize &pizza_size);
std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaState &pizza_state);

#endif /* !PLAZZA_HPP_ */
