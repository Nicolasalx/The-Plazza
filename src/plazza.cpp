/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** plazza
*/

#include "Plazza.hpp"


std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaType &pizza_type)
{
    switch(pizza_type)
    {
        case Pla::PizzaType::Regina:
            output_stream << "Regina";
            break;
        case Pla::PizzaType::Margarita:
            output_stream << "Margarita";
            break;
        case Pla::PizzaType::Americana:
            output_stream << "Americana";
            break;
        case Pla::PizzaType::Fantasia:
            output_stream << "Fantasia";
            break;
    }
    return output_stream;
}

std::ostream &operator << (std::ostream &output_stream, const Pla::PizzaSize &pizza_size)
{
    switch(pizza_size)
    {
        case Pla::PizzaSize::S:
            output_stream << "S";
            break;
        case Pla::PizzaSize::M:
            output_stream << "M";
            break;
        case Pla::PizzaSize::L:
            output_stream << "L";
            break;
        case Pla::PizzaSize::XL:
            output_stream << "XL";
            break;
        case Pla::PizzaSize::XXL:
            output_stream << "XXL";
            break;
    }
    return output_stream;
}
