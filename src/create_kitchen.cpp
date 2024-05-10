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
    this->mutex_.lock();
    this->kitchen_list_.emplace_back();
    key_t send_key = this->kitchen_list_.back().recv_msg_queue.getKey();
    key_t recv_key = this->kitchen_list_.back().send_msg_queue.getKey();
    this->mutex_.unlock();

    pid_t pid = fork();

    if (pid == -1) {
        throw my::tracked_exception("Failed to fork.");
    } else if (pid == 0) {
        Pla::Kitchen kitchen(
            nb_cook_, cooking_time_, ing_repl_time_, send_key, recv_key
        );
        std::exit(0);
    }
    this->mutex_.lock();
    std::cout << "\e[92mKitchen " << pid << " created !\e[0m" << std::endl;
    this->kitchen_list_.back().pid = pid;
    this->mutex_.unlock();
}

void Pla::Reception::closeAllKitchen()
{
    int status = 0;
    pid_t pid = 0;
    Pla::Message msg;

    while (!this->kitchen_list_.empty()) {
        pid = waitpid(this->kitchen_list_.back().pid, &status, WNOHANG);
        if (pid == 0) {
            this->kitchen_list_.back().send_msg_queue.push(Pla::Message(Pla::MessageType::CLOSE_KITCHEN));
            do {
                this->kitchen_list_.back().recv_msg_queue.pop(msg);
            } while (msg.getType() != Pla::MessageType::CLOSE_KITCHEN);
            this->kitchen_list_.pop_back();
        } else if (pid > 0) {
            this->kitchen_list_.pop_back();
        } else {
            break;
        }
    }
}
