/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** utils
*/

#include "ParseCommand.hpp"
#include "my_tracked_exception.hpp"

void Pla::ParseCommand::toLowerCase(std::string &str)
{
    for (char &c : str) {
        c = std::tolower(c);
    }
}

int Pla::ParseCommand::getInt(const std::string &input)
{
    for (const auto &chr: input) {
        if (!std::isdigit(chr)) {
            throw my::tracked_exception("Parsing input: Failed to get a int!");
            return -1;
        }
    }
    return (std::stoi(input));
}
