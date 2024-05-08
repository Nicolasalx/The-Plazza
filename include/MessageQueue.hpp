/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** MessageQueue
*/

#ifndef MESSAGEQUEUE_HPP_
    #define MESSAGEQUEUE_HPP_

    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include <string>
    #include <iostream>
    #include <errno.h>
    #include <string.h>
    #include "ISafeQueue.hpp"

namespace Pla
{
    enum class MessageType {
        NEW_ORDER,
        GET_STATUS,
        CLOSE_KITCHEN
    };

    struct Message
    {
        MessageType type;
        union {
            Pla::Order order;
            int cook_used = 0;
        };

        Message() = default;
        Message(MessageType type_) : type(type_) {}
        Message(MessageType type_, Pla::Order order_) : type(type_), order(order_) {}
        Message(MessageType type_, int cook_used_) : type(type_), cook_used(cook_used_) {}
    };
    
    class MessageQueue : public Pla::ISafeQueue<Pla::Message>
    {
    private:
        key_t key_;
        int id_;

    public:
        MessageQueue()
        {
            key_ = ftok("progfile", 65);
            id_ = msgget(key_, 0666 | IPC_CREAT);
        }
        MessageQueue(key_t key) : key_(key)
        {
            id_ = msgget(key_, 0666 | IPC_CREAT);
        }

        ~MessageQueue() override
        {
            msgctl(id_, IPC_RMID, NULL);
        }

        void push(Pla::Message msg) const override
        {
            msgsnd(id_, &msg, sizeof(msg), 0);
        }

        bool tryPop(Pla::Message &msg) const override
        {
            return (msgrcv(id_, &msg, sizeof(Pla::Message), 1, IPC_NOWAIT) != -1);
        }

        bool pop(Pla::Message &msg) const override
        {
            return (msgrcv(id_, &msg, sizeof(Pla::Message), 1, 0) != -1);
        }

        key_t getKey() const
        {
            return key_;
        }
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
