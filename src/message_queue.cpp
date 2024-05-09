/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** message_queue
*/

#include "MessageQueue.hpp"

Pla::MessageQueue::MessageQueue()
{
    key_ = ftok("progfile", 65);
    id_ = msgget(key_, 0666 | IPC_CREAT);
}

Pla::MessageQueue::MessageQueue(key_t key) : key_(key)
{
    id_ = msgget(key_, 0666 | IPC_CREAT);
}

Pla::MessageQueue::~MessageQueue()
{
    msgctl(id_, IPC_RMID, NULL);
}

void Pla::MessageQueue::push(Pla::Message msg) const
{
    Pla::PackedMessage paqued_message = msg.pack();

    msgsnd(id_, &paqued_message, sizeof(Pla::PackedMessage) - sizeof(long), 0);
}

bool Pla::MessageQueue::tryPop(Pla::Message &msg) const
{
    Pla::PackedMessage packed_message;
    bool res = (msgrcv(id_, &packed_message, sizeof(Pla::PackedMessage) - sizeof(long), 1, IPC_NOWAIT) >= 0);

    // std::cerr << res << "<- ret, cont -> "
    //     << packed_message.type << packed_message.order_type
    //     << packed_message.order_size << packed_message.cook_used << std::endl;
    msg = Pla::Message(packed_message);
    // std::cerr << "\e[95mcont -> \e[0m"
    //     << int(msg.getType()) << int(msg.getOrder().type)
    //     << int(msg.getOrder().size) << int(msg.getCookUsed()) << std::endl;

    return res;
}

bool Pla::MessageQueue::pop(Pla::Message &msg) const
{
    Pla::PackedMessage packed_message;
    bool res = (msgrcv(id_, &packed_message, sizeof(Pla::PackedMessage) - sizeof(long), 1, 0) >= 0);

    // std::cerr << res << "<- ret, cont -> "
    //     << packed_message.type << packed_message.order_type
    //     << packed_message.order_size << packed_message.cook_used << std::endl;
    msg = Pla::Message(packed_message);
        // std::cerr << "\e[95mcont -> \e[0m"
        // << int(msg.getType()) << int(msg.getOrder().type)
        // << int(msg.getOrder().size) << int(msg.getCookUsed()) << std::endl;
    return res;
}

key_t Pla::MessageQueue::getKey() const
{
    return key_;
}
