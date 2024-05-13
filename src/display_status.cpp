/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** display_status
*/

#include "Reception.hpp"

void Pla::Reception::displayCookWork(const Pla::ComKitchen &kitchen)
{
    int nb_cook_disp = 0;

    for (size_t i = 0; i < kitchen.order_.size(); ++i) {
        if (kitchen.order_[i].state == Pla::PizzaState::WAITING_INGREDIENT
        || kitchen.order_[i].state == Pla::PizzaState::CURRENTLY_COOKING) {
            std::cout << "    Cook " << nb_cook_disp << ": Order " << kitchen.order_[i].nb
                << ": " << kitchen.order_[i].type << ' ' << kitchen.order_[i].size
                << ' ' << kitchen.order_[i].state << '\n';
            ++nb_cook_disp;
        }
    }
    for (int i = nb_cook_disp; i < this->nb_cook_; ++i) {
        std::cout << "    Cook " << nb_cook_disp << ": \e[90m[INACTIVE]\e[0m\n";
        ++nb_cook_disp;
    }
}

void Pla::Reception::displayWaitingOrder(const Pla::ComKitchen &kitchen)
{
    size_t nb_waiting = 0;

    for (size_t i = 0; i < kitchen.order_.size(); ++i) {
        if (kitchen.order_[i].state == Pla::PizzaState::WAITING_TO_BE_COOK) {
            std::cout << "    Order " << kitchen.order_[i].nb <<
                ": " << kitchen.order_[i].type << ' ' << kitchen.order_[i].size << '\n';
            ++nb_waiting;
        }
    }
    if (nb_waiting == 0) {
        std::cout << "    \e[90m[EMPTY]\e[0m\n";
    }
}

void Pla::Reception::displayStatus()
{
    this->mutex_.lock();
    std::cout << "------\n";
    if (this->kitchen_list_.empty()) {
        std::cout << "\e[90m[NO KITCHEN]\e[0m\n";
    }
    for (const Pla::ComKitchen &kitchen : this->kitchen_list_) {
        std::cout << "Kitchen " << kitchen.pid << ":\n";
        displayCookWork(kitchen);
        std::cout << "Order queue:\n";
        displayWaitingOrder(kitchen);
    }
    std::cout << "------\n";
    this->mutex_.unlock();
}
