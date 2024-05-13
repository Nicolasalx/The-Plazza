/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** cook
*/

#include "Cook.hpp"
#include <cmath>
#include <iostream>
#include <mutex>

bool Pla::Cook::consumeIngrediant(const Pla::APizza &pizza,
    std::vector<int> &ingredient, std::mutex &mutex)
{
    std::unique_lock lock(mutex);

    return pizza.consumeIngredient(ingredient);
}

void Pla::Cook::makePizza(double time_mult, Pla::Order &order,
    std::vector<int> &ingredient, std::mutex &mutex,
    std::atomic_bool &need_exit)
{
    mutex.lock();
    order.pizza.setState(Pla::PizzaState::WAITING_INGREDIENT);
    mutex.unlock();
    while (!Pla::Cook::consumeIngrediant(order.pizza, ingredient, mutex) && !need_exit) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if (need_exit) {
        return;
    }
    mutex.lock();
    order.pizza.setState(Pla::PizzaState::CURRENTLY_COOKING);
    mutex.unlock();
    std::this_thread::sleep_for(
        std::chrono::milliseconds(long(order.pizza.getCoockingTime() * time_mult)));
    mutex.lock();
    order.pizza.setState(Pla::PizzaState::DONE);
    mutex.unlock();
}
