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

bool Pla::Cook::hasIngrediant(Pla::PizaType type, std::vector<int> &ingredient, std::mutex &mutex)
{
    std::unique_lock lock(mutex);

    switch (type)
    {
    case Pla::PizaType::Regina:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0 &&
            ingredient[int(Pla::Ingredient::Ham)] > 0 &&
            ingredient[int(Pla::Ingredient::Steak)] > 0);
    case Pla::PizaType::Margarita:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0);
    case Pla::PizaType::Americana:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Gruyere)] > 0 &&
            ingredient[int(Pla::Ingredient::Steak)] > 0);
    case Pla::PizaType::Fantasia:
        return (ingredient[int(Pla::Ingredient::Tomato)] > 0 &&
            ingredient[int(Pla::Ingredient::Eggplant)] > 0 &&
            ingredient[int(Pla::Ingredient::GoatCheese)] > 0 &&
            ingredient[int(Pla::Ingredient::ChiefLove)] > 0);
    }
    return false;
}

void Pla::Cook::makePizza(double time_mult, Pla::PizaType type,
    Pla::PizaSize size, std::vector<int> &ingredient, std::mutex &mutex, std::atomic_int &active_pizza)
{
    while (!Pla::Cook::hasIngrediant(type, ingredient, mutex)) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Currently making a pizza." << std::endl;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(long(Pla::coocking_time[int(std::log2(int(type)))] * time_mult)));
    std::cout << "A pizza has been finished." << std::endl;
    --active_pizza;
}
