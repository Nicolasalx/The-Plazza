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
    this->msg_data.order_.type = static_cast<Pla::PizaType>(packed_message.order_type);
    this->msg_data.order_.size = static_cast<Pla::PizaSize>(packed_message.order_size);
    this->msg_data.cook_used_ = static_cast<int>(packed_message.cook_used);
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

Pla::PackedMessage Pla::Message::pack() const
{
    Pla::PackedMessage packed_message;

    packed_message.type = static_cast<long>(this->msg_data.type_);
    packed_message.order_type = static_cast<long>(this->msg_data.order_.type);
    packed_message.order_size = static_cast<long>(this->msg_data.order_.size);
    packed_message.cook_used = static_cast<long>(this->msg_data.cook_used_);
    return packed_message;
}
