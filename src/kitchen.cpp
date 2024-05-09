/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** kitchen
*/

#include "Kitchen.hpp"
#include "my_tracked_exception.hpp"

Pla::Kitchen::Kitchen(std::size_t nb_cook, double cook_time, long ing_repl_time, key_t msg_queue_key)
    : cook_time_(cook_time), active_pizza_(0), ing_repl_time_(ing_repl_time), exit_(false)
{
    cook_.launch(nb_cook);
    ingredient_.resize(static_cast<std::size_t>(Pla::Ingredient::NbIngredient), 5);
    clock_.setCooldown(std::chrono::milliseconds(5000));
    clock_.start();
    msg_queue_ = std::make_unique<Pla::MessageQueue>(msg_queue_key);
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
    switch (msg.getType())
    {
    case Pla::MessageType::NEW_ORDER:
        ++this->active_pizza_;
        this->cook_.addWork([this, msg]{Cook::makePizza(
            this->cook_time_, msg.getOrder().type, msg.getOrder().size,
            this->ingredient_, this->mutex_, this->active_pizza_, &this->exit_);});
        break;
    case Pla::MessageType::GET_STATUS:
        this->msg_queue_->push(Pla::Message(Pla::MessageType::GET_STATUS, this->active_pizza_));
        break;
    default:
        break;
    }
}

void Pla::Kitchen::loop()
{
    Pla::Message msg;

    while (!this->clock_.isElapsed() || this->active_pizza_ > 0)
    {
        if (this->active_pizza_ > 0) {
            this->clock_.reset();
        }
        while (this->msg_queue_->tryPop(msg)) {
            if (msg.getType() == Pla::MessageType::CLOSE_KITCHEN) {
                this->exit_ = true;
                return;
            }
            handleNewMessage(msg);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    this->exit_ = true;
    std::cout << "push close kitchen" << std::endl;
    this->msg_queue_->push(Pla::Message(Pla::MessageType::CLOSE_KITCHEN));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}
