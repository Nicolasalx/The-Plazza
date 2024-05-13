/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Margarita
*/

#ifndef MARGARITA_HPP_
    #define MARGARITA_HPP_

    #include "APizza.hpp"

namespace Pla
{
    class Margarita : public virtual Pla::APizza
    {
    public:
        Margarita(Pla::PizzaSize size, Pla::PizzaState state) : APizza(size, state) {}

        double getCoockingTime() const override
        {
            return 2000.0;
        }

        Pla::PizzaType getType() const override
        {
            return Pla::PizzaType::Margarita;
        }

        std::string getName() const
        {
            return "Margarita";
        }

        bool consumeIngredient(std::vector<int> &ingredient) const override
        {
            if (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0) {
                --ingredient[int(Pla::Ingredient::Tomato)];
                --ingredient[int(Pla::Ingredient::Gruyere)];
                return true;
            }
            return false;
        }
    };
}

#endif /* !MARGARITA_HPP_ */
