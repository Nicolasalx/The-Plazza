/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** message
*/

#include "Message.hpp"

Pla::Message::Message(Pla::PackedMessage &packed_message)
{
    this->msg_data.type_ = static_cast<Pla::MessageType>(packed_message.type);
    this->msg_data.order_.nb = static_cast<int>(packed_message.order_nb);
    this->msg_data.order_.state = static_cast<Pla::PizzaState>(packed_message.order_state);
    this->msg_data.order_.type = static_cast<Pla::PizzaType>(packed_message.order_type);
    this->msg_data.order_.size = static_cast<Pla::PizzaSize>(packed_message.order_size);
    this->msg_data.cook_used_ = static_cast<int>(packed_message.cook_used);
    for (size_t i = 0; i < size_t(Pla::Ingredient::NbIngredient); ++i) {
        this->msg_data.ingredient_[i] = packed_message.ingredient[i];
    }
}

Pla::Message::Message(Pla::MessageType type)
{
    this->msg_data.type_ = type;
}

Pla::Message::Message(Pla::MessageType type, Pla::Order order)
{
    this->msg_data.type_ = type;
    this->msg_data.order_ = order;
}

Pla::Message::Message(Pla::MessageType type, int cook_used)
{
    this->msg_data.type_ = type;
    this->msg_data.cook_used_ = cook_used;
}

Pla::Message::Message(Pla::MessageType type, const std::vector<int> &ingredient)
{
    this->msg_data.type_ = type;
    for (size_t i = 0; i < size_t(Pla::Ingredient::NbIngredient); ++i) {
        this->msg_data.ingredient_[i] = ingredient[i];
    }
}

Pla::MessageType Pla::Message::getType() const
{
    return this->msg_data.type_;
}

Pla::Order Pla::Message::getOrder() const
{
    return this->msg_data.order_;
}

int Pla::Message::getCookUsed() const
{
    return this->msg_data.cook_used_;
}

std::array<int, int(Pla::Ingredient::NbIngredient)> Pla::Message::getIngredient() const
{
    return this->msg_data.ingredient_;
}

Pla::PackedMessage Pla::Message::pack() const
{
    Pla::PackedMessage packed_message;

    packed_message.type = static_cast<long>(this->msg_data.type_);
    packed_message.order_nb = static_cast<long>(this->msg_data.order_.nb);
    packed_message.order_state = static_cast<long>(this->msg_data.order_.state);
    packed_message.order_type = static_cast<long>(this->msg_data.order_.type);
    packed_message.order_size = static_cast<long>(this->msg_data.order_.size);
    packed_message.cook_used = static_cast<long>(this->msg_data.cook_used_);
    for (size_t i = 0; i < size_t(Pla::Ingredient::NbIngredient); ++i) {
        packed_message.ingredient[i] = this->msg_data.ingredient_[i];
    }
    return packed_message;
}
