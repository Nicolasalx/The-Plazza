/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** main
*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include "my_log.hpp"
#include <vector>
#include <iomanip>
#include <thread>
#include "Plazza.hpp"
#include "Reception.hpp"
#include "MessageQueue.hpp"
#include "Kitchen.hpp"
#include "Regina.hpp"

int main(int argc, const char *argv[])
{
    try {
        Pla::Reception reception(argc, argv);
        reception.openPlazza();
    } catch (const std::exception &exception) {
        my::log::error(exception.what());
        return 84;
    }
    return 0;
}
