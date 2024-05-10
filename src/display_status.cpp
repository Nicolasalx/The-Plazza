/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** display_status
*/

#include "Reception.hpp"

void Pla::Reception::displayStatus()
{
    this->mutex_.lock();
    std::cout << "------\n";
    for (const Pla::ComKitchen &kitchen : this->kitchen_list_) {
        std::cout << "Kitchen " << kitchen.pid << ":\n";
        int nb_cook_disp = 0;
        for (size_t i = 0; i < kitchen.order_.size(); ++i) {
            if (kitchen.order_[i].state == Pla::PizzaState::WAITING_INGREDIENT) {
                std::cout << "    Cook " << nb_cook_disp << ": Order " << kitchen.order_[i].nb
                    << ": " << kitchen.order_[i].type << ' ' << kitchen.order_[i].size << " \e[93m[WAITING FOR INGREDIENT]\e[0m\n";
                ++nb_cook_disp;
            }
            if (kitchen.order_[i].state == Pla::PizzaState::CURRENTLY_COOKING) {
                std::cout << "    Cook " << nb_cook_disp << ": Order " << kitchen.order_[i].nb
                    << ": " << kitchen.order_[i].type << ' ' << kitchen.order_[i].size << " \e[96m[CURRENTLY COOK]\e[0m\n";
                ++nb_cook_disp;
            }
        }
        for (int i = nb_cook_disp; i < this->nb_cook_; ++i) {
            std::cout << "    Cook " << nb_cook_disp << ": \e[90m[INACTIVE]\e[0m\n";
            ++nb_cook_disp;
        }
        std::cout << "Order queue:\n";
        size_t nb_waiting = 0;
        for (size_t i = 0; i < kitchen.order_.size(); ++i) {
            if (kitchen.order_[i].state == Pla::PizzaState::WAITING_TO_BE_COOK) {
                std::cout << "    Order " << kitchen.order_[i].nb <<
                    ": " << kitchen.order_[i].type << " " << kitchen.order_[i].size << "\n";
                ++nb_waiting;
            }
        }
        if (nb_waiting == 0) {
            std::cout << "    \e[90m[EMPTY]\e[0m\n";
        }
    }
    std::cout << "------\n";
    this->mutex_.unlock();
}
