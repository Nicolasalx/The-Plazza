/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** PizzaFactory
*/

#ifndef PIZZAFACTORY_HPP_
    #define PIZZAFACTORY_HPP_

    #include "APizza.hpp"
    #include "my_tracked_exception.hpp"
    #include <string>
    #include <map>
    #include <functional>


namespace Pla
{
    class PizzaFactory
    {
    private:
        static const std::map<Pla::PizzaType,
            std::function<Pla::APizza(Pla::PizzaSize, Pla::PizzaState)>> pizza_map_;

    public:
        static Pla::APizza createPizza(const Pla::PizzaType &type, Pla::PizzaSize size, Pla::PizzaState state)
        {
            if (Pla::PizzaFactory::pizza_map_.contains(type)) {
                return Pla::PizzaFactory::pizza_map_.at(type)(size, state);
            } else {
                throw my::tracked_exception("Unknow pizza: " + std::to_string(int(type)) + '.');
            }
        }
    };
}

#endif /* !PIZZAFACTORY_HPP_ */
