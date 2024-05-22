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

namespace Pla
{
    enum class MessageType {
        NOT_INIT,
        NEW_ORDER,
        START_STATUS,
        PIZZA_STATUS,
        PIZZA_DONE,
        INGREDIENT_STATUS,
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
        int ingredient[int(Pla::Ingredient::NbIngredient)] = {0};
    };

    class Message
    {
    private:
        struct MsgData {
            Pla::MessageType type_ = Pla::MessageType::NOT_INIT;
            Pla::Order order_;
            int cook_used_ = 0;
            std::array<int, int(Pla::Ingredient::NbIngredient)> ingredient_ = {0};
        };
        MsgData msg_data;

    public:
        Message() = default;
        Message(Pla::PackedMessage &packed_message);
        Message(Pla::MessageType type);
        Message(Pla::MessageType type, Pla::Order order);
        Message(Pla::MessageType type, int cook_used);
        Message(Pla::MessageType type, const std::vector<int> &ingredient);
        ~Message() = default;

        Pla::MessageType getType() const;
        Pla::Order getOrder() const;
        int getCookUsed() const;
        std::array<int, int(Pla::Ingredient::NbIngredient)> getIngredient() const;

        Pla::PackedMessage pack() const;

        friend std::ostream &operator << (std::ostream &output_stream, const Pla::Message &message)
        {
            Pla::PackedMessage packed_message = message.pack();
            output_stream << packed_message.type
               << packed_message.order_nb
               << packed_message.order_state
               << packed_message.order_type
               << packed_message.order_size
               << packed_message.cook_used;
            for (size_t i = 0; i < int(Pla::Ingredient::NbIngredient); ++i) {
                output_stream << packed_message.ingredient[i];
            }
            return output_stream;
        }

        friend std::istream &operator >> (std::istream &input_stream, Pla::Message &message)
        {
            Pla::PackedMessage packed_message;
            input_stream >> packed_message.type
               >> packed_message.order_nb
               >> packed_message.order_state
               >> packed_message.order_type
               >> packed_message.order_size
               >> packed_message.cook_used;
            for (size_t i = 0; i < int(Pla::Ingredient::NbIngredient); ++i) {
                input_stream >> packed_message.ingredient[i];
            }
            message = Pla::Message(packed_message);
            return input_stream;
        }
    };
}

#endif /* !MESSAGE_HPP_ */
