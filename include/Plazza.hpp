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

    struct Order
    {
        int nb = 0;
        Pla::PizzaType type = Pla::PizzaType::Regina;
        Pla::PizzaSize size = Pla::PizzaSize::S;
        Pla::PizzaState state = Pla::PizzaState::WAITING_TO_BE_COOK;
    };

    static constexpr std::array<double, 4> coocking_time = {1000, 2000, 2000, 4000};
}

std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaType &pizza_type);
std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaSize &pizza_size);
std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaState &pizza_state);
std::ostream &operator << (std::ostream &output_stream, const Pla::Ingredient &ingredient);

#endif /* !PLAZZA_HPP_ */
