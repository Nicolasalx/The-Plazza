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
    std::queue<std::list<Pla::ComKitchen>::iterator> to_close;

    this->mutex_.lock();
    for (auto it = this->kitchen_list_.begin(); it != this->kitchen_list_.end(); ++it)
    {
        while (it->recv_msg_queue.tryPop(msg)) {
            if (msg.getType() == Pla::MessageType::CLOSE_KITCHEN) {
                std::cerr << "\e[91mKitchen " << it->pid << " closed !\e[0m" << std::endl;
                to_close.push(it);
                break;
            }
            if (msg.getType() == Pla::MessageType::GET_STATUS) {
                it->nb_used_cook = msg.getCookUsed();
                std::cerr << "Kitchen: " << this->kitchen_list_.size() << ", Nb cook used: " << it->nb_used_cook << std::endl;
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

void Pla::Reception::dispatchOrder()
{
    this->mutex_.lock();
    while (!this->order_.empty())
    {
        this->kitchen_list_.sort([]
            (const Pla::ComKitchen &kitchen_1, const Pla::ComKitchen &kitchen_2) -> bool
            {
                return kitchen_1.nb_used_cook < kitchen_2.nb_used_cook;
            }
        );
        if (!this->kitchen_list_.empty() && this->kitchen_list_.front().nb_used_cook < (this->nb_cook_ * 2)) {
            this->kitchen_list_.front().send_msg_queue.push(
                Pla::Message(Pla::MessageType::NEW_ORDER, this->order_.front()));
            ++this->kitchen_list_.front().nb_used_cook;
            this->order_.pop();
        } else {
            this->mutex_.unlock();
            createKitchen();
            this->mutex_.lock();
        }
    }
    this->mutex_.unlock();
}

void Pla::Reception::manageKitchen()
{
    while (!this->exit_)
    {
        this->handleRecvMessage();
        this->dispatchOrder();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
