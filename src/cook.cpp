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

bool Pla::Cook::hasIngrediant(Pla::PizzaType type, std::vector<int> &ingredient, std::mutex &mutex)
{
    std::unique_lock lock(mutex);

    switch (type)
    {
    case Pla::PizzaType::Regina:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0 &&
            ingredient[int(Pla::Ingredient::Ham)] > 0 &&
            ingredient[int(Pla::Ingredient::Steak)] > 0);
    case Pla::PizzaType::Margarita:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0);
    case Pla::PizzaType::Americana:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0 &&
            ingredient[int(Pla::Ingredient::Steak)] > 0);
    case Pla::PizzaType::Fantasia:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Eggplant)] > 0 &&
            ingredient[int(Pla::Ingredient::GoatCheese)] > 0 &&
            ingredient[int(Pla::Ingredient::ChiefLove)] > 0);
    }
    return false;
}

void Pla::Cook::makePizza(double time_mult, Pla::Order &order,
    std::vector<int> &ingredient, std::mutex &mutex,
    std::atomic_bool *need_exit)
{
    mutex.lock();
    order.state = Pla::PizzaState::WAITING_INGREDIENT;
    mutex.unlock();
    while (!Pla::Cook::hasIngrediant(order.type, ingredient, mutex) && !*need_exit) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if (*need_exit) {
        return;
    }
    mutex.lock();
    order.state = Pla::PizzaState::CURRENTLY_COOKING;
    mutex.unlock();
    std::this_thread::sleep_for(
        std::chrono::milliseconds(long(Pla::coocking_time[int(std::log2(int(order.type)))] * time_mult)));
    mutex.lock();
    order.state = Pla::PizzaState::DONE;
    mutex.unlock();
}
