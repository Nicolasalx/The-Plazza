/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_

    #include "Plazza.hpp"

namespace Pla
{
    class Cook
    {
    public:
        ~Cook() = default;

        static bool consumeIngrediant(Pla::PizzaType type, std::vector<int> &ingredient, std::mutex &mutex);
        static void makePizza(double time_mult, Pla::Order &order, std::vector<int> &ingredient,
            std::mutex &mutex, std::atomic_bool &need_exit);
    };
}

#endif /* !COOK_HPP_ */
