/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_

    #include "Plazza.hpp"
    #include "APizza.hpp"
    #include "Order.hpp"

namespace Pla
{
    class Cook
    {
    public:
        ~Cook() = default;

        static bool consumeIngrediant(const Pla::APizza &pizza, std::vector<int> &ingredient, std::mutex &mutex);
        static void makePizza(double time_mult, Pla::Order &order, std::vector<int> &ingredient,
            std::mutex &mutex, std::atomic_bool &need_exit);
    };
}

#endif /* !COOK_HPP_ */
