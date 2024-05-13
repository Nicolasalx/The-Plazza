/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Fantasia
*/

#ifndef FANTASIA_HPP_
    #define FANTASIA_HPP_

    #include "APizza.hpp"

namespace Pla
{
    class Fantasia : public virtual Pla::APizza
    {
    public:
        Fantasia(Pla::PizzaSize size, Pla::PizzaState state) : APizza(size, state) {}

        double getCoockingTime() const override
        {
            return 4000.0;
        }

        Pla::PizzaType getType() const override
        {
            return Pla::PizzaType::Fantasia;
        }

        std::string getName() const
        {
            return "Fantasia";
        }

        bool consumeIngredient(std::vector<int> &ingredient) const override
        {
            if (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Eggplant)] > 0 &&
            ingredient[int(Pla::Ingredient::GoatCheese)] > 0 &&
            ingredient[int(Pla::Ingredient::ChiefLove)] > 0) {
                --ingredient[int(Pla::Ingredient::Tomato)];
                --ingredient[int(Pla::Ingredient::Eggplant)];
                --ingredient[int(Pla::Ingredient::GoatCheese)];
                --ingredient[int(Pla::Ingredient::ChiefLove)];
                return true;
            }
            return false;
        }
    };
}

#endif /* !FANTASIA_HPP_ */
