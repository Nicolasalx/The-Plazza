/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** reception
*/

#include "Reception.hpp"
#include "Plazza.hpp"
#include "Kitchen.hpp"
#include "my_tracked_exception.hpp"
#include <iostream>

Pla::Reception::Reception(int argc, const char **argv) : exit_(false)
{
    if (argc != 4) {
        throw my::tracked_exception("Invalid number of arg.");
    }
    this->cooking_time_ = std::stod(argv[1]);
    this->nb_cook_ = std::stoi(argv[2]);
    this->ing_repl_time_ = std::stol(argv[3]);
    if (this->cooking_time_ < 0 ||
        this->nb_cook_ <= 0 ||
        this->ing_repl_time_ < 0) {
        throw my::tracked_exception("Invalid arg value.");
    }
    std::srand(std::time(nullptr));
}

void Pla::Reception::handleInput(const std::string &input)
{
    this->mutex_.lock();
    std::cerr << "Get: \"" << input << "\"\n";
    this->mutex_.unlock();
    /*
        TODO: - parse the input
        TODO: - add piza to make to "order_" queue
    */
    this->mutex_.lock();
    for (size_t i = 0; i < 10; ++i) {
        order_.push(Pla::Order(Pla::PizaType::Regina, Pla::PizaSize::L));
    }
    this->mutex_.unlock();
}

void Pla::Reception::openPlazza()
{
    std::thread kitchen_manager([this]{manageKitchen();});
    std::string input;

    while (true) {
        input.clear();
        if (!std::getline(std::cin, input)) {
            break;
        }
        handleInput(input);
    }
    this->exit_ = true;
    kitchen_manager.join();
    closeAllKitchen();
}
