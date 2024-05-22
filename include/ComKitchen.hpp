/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Reception
*/

#ifndef COMKITCHEN_HPP_
    #define COMKITCHEN_HPP_

    #include <list>
    #include <queue>
    #include <fstream>
    #include <array>
    #include <vector>
    #include "MessageQueue.hpp"
    #include "Plazza.hpp"

namespace Pla
{
    struct ComKitchen
    {
        pid_t pid;
        Pla::MessageQueue send_msg_queue;
        Pla::MessageQueue recv_msg_queue;
        std::vector<Pla::Order> order_;
        int nb_used_cook = 0;
        std::array<int, int(Pla::Ingredient::NbIngredient)> ingredient;

        ComKitchen() = default;
        ComKitchen(pid_t pid_) : pid(pid_) {};
    };
}

#endif /* !COMKITCHEN_HPP_ */
