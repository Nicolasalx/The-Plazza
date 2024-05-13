/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Americana
*/

#ifndef AMERICANA_HPP_
    #define AMERICANA_HPP_

    #include "APizza.hpp"

namespace Pla
{
    class Americana : public virtual Pla::APizza
    {
    public:
        Americana(Pla::PizzaSize size, Pla::PizzaState state) : APizza(size, state) {}

        double getCoockingTime() const override
        {
            return 2000.0;
        }

        Pla::PizzaType getType() const override
        {
            return Pla::PizzaType::Americana;
        }

        std::string getName() const
        {
            return "Americana";
        }

        bool consumeIngredient(std::vector<int> &ingredient) const override
        {
            if (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0 &&
            ingredient[int(Pla::Ingredient::Steak)] > 0) {
                --ingredient[int(Pla::Ingredient::Tomato)];
                --ingredient[int(Pla::Ingredient::Gruyere)];
                --ingredient[int(Pla::Ingredient::Steak)];
                return true;
            }
            return false;
        }
    };
}

#endif /* !AMERICANA_HPP_ */
