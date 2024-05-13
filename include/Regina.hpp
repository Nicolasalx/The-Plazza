/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Regina
*/

#ifndef REGINA_HPP_
    #define REGINA_HPP_

    #include "APizza.hpp"

namespace Pla
{
    class Regina : public virtual Pla::APizza
    {
    public:
        Regina(Pla::PizzaSize size, Pla::PizzaState state) : APizza(size, state) {}

        double getCoockingTime() const override
        {
            return 1000.0;
        }

        Pla::PizzaType getType() const override
        {
            return Pla::PizzaType::Regina;
        }

        std::string getName() const
        {
            return "Regina";
        }
        
        bool consumeIngredient(std::vector<int> &ingredient) const override
        {
            if (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0 &&
            ingredient[int(Pla::Ingredient::Ham)] > 0 &&
            ingredient[int(Pla::Ingredient::Steak)] > 0) {
                --ingredient[int(Pla::Ingredient::Tomato)];
                --ingredient[int(Pla::Ingredient::Gruyere)];
                --ingredient[int(Pla::Ingredient::Ham)];
                --ingredient[int(Pla::Ingredient::Steak)];
                return true;
            }
            return false;
        }
    };
}

#endif /* !REGINA_HPP_ */
