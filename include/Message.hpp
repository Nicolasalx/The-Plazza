/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
    #define MESSAGE_HPP_

    #include "Plazza.hpp"
    #include <cstring>
    #include "APizza.hpp"
    #include "Order.hpp"

namespace Pla
{
    enum class MessageType {
        NOT_INIT,
        NEW_ORDER,
        START_STATUS,
        PIZZA_STATUS,
        PIZZA_DONE,
        CLOSE_KITCHEN
    };

    struct PackedMessage
    {
        long mtype = 1;
        long type = 0;
        long order_nb = 0;
        long order_type = 0;
        long order_size = 0;
        long order_state = 0;
        long cook_used = 0;
    };

    class Message
    {
    private:
        struct MsgData {
            Pla::MessageType type_ = Pla::MessageType::NOT_INIT;
            Pla::Order order_;
            int cook_used_ = 0;
        };
        MsgData msg_data;

    public:
        Message() = default;
        Message(Pla::PackedMessage &packed_message);
        Message(Pla::MessageType type);
        Message(Pla::MessageType type, Pla::Order order);
        Message(Pla::MessageType type, int cook_used);
        ~Message() = default;

        Pla::MessageType getType() const;
        Pla::Order getOrder() const;
        int getCookUsed() const;

        Pla::PackedMessage pack() const;
    };
}

#endif /* !MESSAGE_HPP_ */
