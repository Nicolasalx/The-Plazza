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
    #include "Message.hpp"

namespace Pla
{
    class MessageQueue : public Pla::ISafeQueue<Pla::Message>
    {
    private:
        key_t key_;
        int id_;

    public:
        MessageQueue();
        MessageQueue(key_t key);
        ~MessageQueue() override;

        void push(Pla::Message msg) const override;
        bool tryPop(Pla::Message &msg) const override;
        bool pop(Pla::Message &msg) const override;
        key_t getKey() const;
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
