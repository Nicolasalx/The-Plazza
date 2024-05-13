/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** pizza_factory
*/

#include "PizzaFactory.hpp"
#include "Regina.hpp"
#include "Margarita.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"

const std::map<Pla::PizzaType,
    std::function<Pla::APizza(Pla::PizzaSize, Pla::PizzaState)>
    > Pla::PizzaFactory::pizza_map_ =
{
    {Pla::PizzaType::Regina, [](Pla::PizzaSize size, Pla::PizzaState state) -> Pla::APizza
        {
            return Pla::Regina(size, state);
        }
    },
    {Pla::PizzaType::Margarita, [](Pla::PizzaSize size, Pla::PizzaState state) -> Pla::APizza
        {
            return Pla::Margarita(size, state);
        }
    },
    {Pla::PizzaType::Americana, [](Pla::PizzaSize size, Pla::PizzaState state) -> Pla::APizza
        {
            return Pla::Americana(size, state);
        }
    },
    {Pla::PizzaType::Fantasia, [](Pla::PizzaSize size, Pla::PizzaState state) -> Pla::APizza
        {
            return Pla::Fantasia(size, state);
        }
    }
};
