/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** APizza
*/

#ifndef APIZZA_HPP_
    #define APIZZA_HPP_

#include "Plazza.hpp"

namespace Pla
{
    class APizza
    {
    protected:
        Pla::PizzaState state_;
        Pla::PizzaSize size_;

    public:
        APizza() = default;
        APizza(Pla::PizzaSize size, Pla::PizzaState state)
        {
            size_ = size;
            state_ = state;
        }

        virtual double getCoockingTime() const
        {
            return 0.0;
        }

        Pla::PizzaSize getSize() const
        {
            return size_;
        };

        Pla::PizzaState getState() const
        {
            return state_;
        }

        void setState(const Pla::PizzaState &new_state)
        {
            this->state_ = new_state;
        }

        virtual Pla::PizzaType getType() const
        {
            return Pla::PizzaType::Regina;
        }
        
        virtual std::string getName() const
        {
            return "Unknown";
        }

        virtual bool consumeIngredient(std::vector<int> &) const
        {
            return false;
        }
    };
}

#endif /* !APIZZA_HPP_ */
