/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** pizzaTYpe
*/

#include "ParseCommand.hpp"
#include "Plazza.hpp"
#include "my_tracked_exception.hpp"

void Pla::ParseCommand::definePizzaSize(Order &order, std::string &input)
{
    if (input == "S") {
        order.size = Pla::PizzaSize::S;
    } else if (input == "M") {
        order.size = Pla::PizzaSize::M;
    } else if (input == "L") {
        order.size = Pla::PizzaSize::L;
    } else if (input == "XL") {
        order.size = Pla::PizzaSize::XL;
    } else if (input == "XXL") {
        order.size = Pla::PizzaSize::XXL;
    } else {
        throw my::tracked_exception("Size unrecognized in the command of the customer!");
    }
}
