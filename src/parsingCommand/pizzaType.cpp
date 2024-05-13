/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** pizzaTYpe
*/

#include "ParseCommand.hpp"
#include "Plazza.hpp"
#include "my_tracked_exception.hpp"

void Pla::ParseCommand::definePizzaType(Order &order, std::string &input)
{
    toLowerCase(input);
    if (input == "regina") {
        order.type = Pla::PizzaType::Regina;
    } else if (input == "margarita") {
        order.type = Pla::PizzaType::Margarita;
    } else if (input == "americana") {
        order.type = Pla::PizzaType::Americana;
    } else if (input == "fantasia") {
        order.type = Pla::PizzaType::Fantasia;
    } else {
        throw my::tracked_exception("Type unrecognized in the command of the customer!");
    }
}
