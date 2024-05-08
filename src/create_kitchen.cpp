/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** create_kitchen
*/

#include "Reception.hpp"
#include "Kitchen.hpp"
#include "my_tracked_exception.hpp"
#include <unistd.h>
#include <sys/wait.h>

void Pla::Reception::createKitchen()
{
    pid_t pid = fork();
    this->kitchen_list_.emplace_back(Pla::ComKitchen(pid));

    if (pid == -1) {
        throw my::tracked_exception("Failed to fork.");
    } else if (pid == 0) {
        Pla::Kitchen kitchen_1(
            nb_cook_,
            cooking_time_,
            ing_repl_time_,
            this->kitchen_list_.back().msg_queue.getKey()
        );
    }
}

void Pla::Reception::closeAllKitchen()
{
    int status = 0;
    pid_t pid = 0;

    while (!this->kitchen_list_.empty()) {
        pid = waitpid(this->kitchen_list_.back().pid, &status, WNOHANG);
        if (pid == 0) {
            this->kitchen_list_.back().msg_queue.push(Pla::Message(Pla::MessageType::CLOSE_KITCHEN));
            this->kitchen_list_.pop_back();
        } else if (pid > 0) {
            this->kitchen_list_.pop_back();
        } else {
            break;
        }
    }
}
