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
    this->log_file_.open("reception.log");
    if (!this->log_file_.is_open()) {
        throw my::tracked_exception("Fail to open logfile.");
    }
}

void Pla::Reception::handleInput(const std::string &input)
{
    Pla::Order new_order;

    std::cerr << "Get: \"" << input << "\"\n";

    //    TODO: - parse the input

    if (input == "status") {
        displayStatus();
    } else {
        this->mutex_.lock();
        // ! Data to fill with parsing :
        new_order.nb = this->order_index_++;
        new_order.type = Pla::PizzaType::Regina;
        new_order.size = Pla::PizzaSize::L;
        new_order.state = Pla::PizzaState::WAITING_TO_BE_COOK;
        // ! ---------------------------
        order_.push(new_order);
        this->mutex_.unlock();
    }
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
