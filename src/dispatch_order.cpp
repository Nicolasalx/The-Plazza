/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** dispatch_order
*/

#include "Reception.hpp"
#include "Kitchen.hpp"

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
