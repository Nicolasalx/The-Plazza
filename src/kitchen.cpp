/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** kitchen
*/

#include "Kitchen.hpp"
#include "my_tracked_exception.hpp"

Pla::Kitchen::Kitchen(std::size_t nb_cook, double cook_time, long ing_repl_time, key_t send_msg_key, key_t recv_msg_key)
    : cook_time_(cook_time), ing_repl_time_(ing_repl_time), has_order_(false), exit_(false)
{
    cook_.launch(nb_cook);
    ingredient_.resize(static_cast<std::size_t>(Pla::Ingredient::NbIngredient), 5);
    clock_.setCooldown(std::chrono::milliseconds(5000));
    clock_.start();
    send_msg_queue_ = std::make_unique<Pla::MessageQueue>(send_msg_key);
    recv_msg_queue_ = std::make_unique<Pla::MessageQueue>(recv_msg_key);
    loop();
}

void Pla::Kitchen::refillIngredient()
{
    while (!this->exit_)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(this->ing_repl_time_));
        this->mutex_.lock();
        for (int &ing : this->ingredient_) {
            ing += 1;
        }
        this->mutex_.unlock();
    }
}

void Pla::Kitchen::handleNewMessage(const Pla::Message &msg)
{
    if (msg.getType() == Pla::MessageType::NEW_ORDER)
    {
        this->mutex_.lock();
        this->pizza_.push_back(msg.getOrder());
        Pla::Order &pizza_to_make = this->pizza_.back();
        std::vector<int> &ing = this->ingredient_;
        this->mutex_.unlock();

        this->cook_.addWork([&]{Cook::makePizza(
            this->cook_time_, pizza_to_make,
            ing, this->mutex_, &this->exit_);});
    }
}

void Pla::Kitchen::sendStatus()
{
    std::queue<std::list<Pla::Order>::iterator> to_remove;

    this->mutex_.lock();
    for (auto it = this->pizza_.begin(); it != this->pizza_.end(); ++it) {
        if (it->state == Pla::PizzaState::DONE) {
            this->send_msg_queue_->push(Pla::Message(Pla::MessageType::PIZZA_DONE, *it));
            to_remove.push(it);
        }
    }
    while (!to_remove.empty()) {
        this->pizza_.erase(to_remove.front());
        to_remove.pop();
    }
    this->send_msg_queue_->push(Pla::Message(Pla::MessageType::START_STATUS, this->pizza_.size()));
    for (const Pla::Order &it : this->pizza_) {
        this->send_msg_queue_->push(Pla::Message(Pla::MessageType::PIZZA_STATUS, it));
    }
    this->has_order_ = (!this->pizza_.empty());
    this->mutex_.unlock();
}

void Pla::Kitchen::loop()
{
    Pla::Message msg;
    std::thread refill_thread([this]{refillIngredient();});

    while (!this->clock_.isElapsed() || this->has_order_)
    {
        if (this->has_order_) {
            this->clock_.reset();
        }
        while (this->recv_msg_queue_->tryPop(msg)) {
            if (msg.getType() == Pla::MessageType::CLOSE_KITCHEN) {
                this->exit_ = true;
                this->cook_.stop();
                refill_thread.join();
                this->send_msg_queue_->push(Pla::Message(Pla::MessageType::CLOSE_KITCHEN));
                return;
            }
            handleNewMessage(msg);
        }
        sendStatus();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    this->exit_ = true;
    this->cook_.stop();
    refill_thread.join();
    this->send_msg_queue_->push(Pla::Message(Pla::MessageType::CLOSE_KITCHEN));
}
