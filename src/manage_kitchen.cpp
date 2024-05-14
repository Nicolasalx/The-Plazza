/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** manage_kitchen
*/

#include "Reception.hpp"
#include "Kitchen.hpp"

void Pla::Reception::handleRecvStatus(
    const std::list<Pla::ComKitchen>::iterator &it, const Pla::Message &msg)
{
    Pla::Message status_msg;

    if (msg.getType() != Pla::MessageType::START_STATUS) {
        return;
    }
    it->nb_used_cook = msg.getCookUsed();
    it->order_.clear();
    for (int i = 0; i < it->nb_used_cook; ++i) {
        it->recv_msg_queue.pop(status_msg);
        it->order_.push_back(status_msg.getOrder());
    }
}

void Pla::Reception::handleRecvMessage()
{
    Pla::Message msg;
    std::queue<std::list<Pla::ComKitchen>::iterator> to_close;

    this->mutex_.lock();
    for (auto it = this->kitchen_list_.begin(); it != this->kitchen_list_.end(); ++it)
    {
        while (it->recv_msg_queue.tryPop(msg)) {
            if (msg.getType() == Pla::MessageType::CLOSE_KITCHEN) {
                std::cout << "\e[91mKitchen " << it->pid << " closed !\e[0m\n";
                to_close.push(it);
                break;
            } else if (msg.getType() == Pla::MessageType::PIZZA_DONE) {
                std::cout << "\e[94mKitchen " << it->pid << ": Order " << msg.getOrder().nb
                    << ": The " << msg.getOrder().type
                    << " of size: " << msg.getOrder().size
                    << " done.\e[0m\n";
                if (this->log_file_.is_open()) {
                    this->log_file_ << "Kitchen " << it->pid << ": Order " << msg.getOrder().nb
                        << ": The " << msg.getOrder().type
                        << " of size: " << msg.getOrder().size
                        << " done.\n";
                }
            } else if (msg.getType() == Pla::MessageType::INGREDIENT_STATUS) {
                it->ingredient = msg.getIngredient();
            } else {
                handleRecvStatus(it, msg);
            }
        }
    }
    while (!to_close.empty())
    {
        this->kitchen_list_.erase(to_close.front());
        to_close.pop();
    }
    this->mutex_.unlock();
}

void Pla::Reception::manageKitchen()
{
    while (!this->exit_)
    {
        this->handleRecvMessage();
        this->dispatchOrder();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}
