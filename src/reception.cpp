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
#include "ParseCommand.hpp"

Pla::Reception::Reception(int argc, const char **argv) : exit_(false)
{
    if (argc != 4) {
        throw my::tracked_exception("Invalid number of arg.");
    }
    this->cooking_time_ = std::stod(argv[1]);
    this->nb_cook_ = std::stoi(argv[2]);
    this->ing_repl_time_ = std::stol(argv[3]);

    this->isGraphical_ = true;
    // Graphical
    // bool isGraphical_

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
    Pla::ParseCommand parseCmd;
    std::vector<Pla::Order> allOrder;

    if (input == "status") {
        displayStatus();
    } else {
        allOrder = parseCmd.parsingCommand(input, this->order_index_);
        if (allOrder.empty()) {
            return;
        }
        for (const auto &ord: allOrder) {
            this->mutex_.lock();
            order_.push(ord);
            this->mutex_.unlock();
        }
    }
}

void Pla::Reception::openPlazza()
{
    std::thread kitchen_manager([this]{manageKitchen();});

    //if (this->isGraphical_ == true) {
        std::thread graphical_interface_manager([this]{this->graphicalInterface.launch(this->kitchen_list_, this->mutex_, this->exit_);});
    //}
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
