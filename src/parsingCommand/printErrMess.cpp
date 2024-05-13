/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** printErrMess
*/

#include "ParseCommand.hpp"
#include <iostream>

void Pla::ParseCommand::printErrMess(const std::string &str)
{
    std::cerr << "\033[1;93m" << str << "\033[0;0m\n";
}
