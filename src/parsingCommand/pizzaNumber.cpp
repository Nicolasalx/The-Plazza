/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** pizzaTYpe
*/

#include "ParseCommand.hpp"
#include "Plazza.hpp"
#include "my_tracked_exception.hpp"

void Pla::ParseCommand::definePizzaNumber(std::string &input, int &pizzaNumber)
{
    if (input.size() >= 2 && input.front() == 'x') {
        std::string subString = input.substr(1);
        int pizzaNb = getInt(subString);
        if (pizzaNb > 0) {
            pizzaNumber = pizzaNb;
        }
    }
    if (pizzaNumber == 0) {
        throw my::tracked_exception("Invalid number of pizzas to prepare!");
    }
}
