/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** manage_kitchen
*/

#include "Reception.hpp"
#include "Kitchen.hpp"

void Pla::Reception::handleRecvMessage()
{
    Pla::Message msg;

    for (auto it = this->kitchen_list_.begin(); it != this->kitchen_list_.end();)
    {
        while (it->msg_queue.tryPop(msg)) {
            if (msg.type == Pla::MessageType::CLOSE_KITCHEN) {
                this->kitchen_list_.erase(it++);
                continue;
            }
        }
        ++it;
    }
}

void Pla::Reception::dispatchOrder()
{
    Pla::Message msg;

    for (Pla::ComKitchen &it : this->kitchen_list_)
    {
        it.msg_queue.push(Pla::Message(Pla::MessageType::GET_STATUS));
        it.msg_queue.pop(msg);
        it.nb_used_cook = msg.cook_used;
    }
    while (!this->order_.empty())
    {
        this->kitchen_list_.sort([]
            (const Pla::ComKitchen &kitchen_1, const Pla::ComKitchen &kitchen_2) -> bool
            {
                return kitchen_1.nb_used_cook < kitchen_2.nb_used_cook;
            }
        );
        if (this->kitchen_list_.front().nb_used_cook < (this->nb_cook_ * 2)) {
            this->kitchen_list_.front().msg_queue.push(
                Pla::Message(Pla::MessageType::NEW_ORDER, this->order_.front()));
            this->order_.pop();
        } else {
            createKitchen();
        }
    }
}

void Pla::Reception::manageKitchen()
{
    while (!this->exit_)
    {
        this->mutex_.lock();
        std::cout << this->order_.size() << std::endl;
        this->handleRecvMessage();
        this->dispatchOrder();
        this->mutex_.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

