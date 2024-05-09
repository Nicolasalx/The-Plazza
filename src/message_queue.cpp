/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** message_queue
*/

#include "MessageQueue.hpp"
#include <fstream>

Pla::MessageQueue::MessageQueue()
{
    std::ofstream file;
    std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    filename_ = "./msg_queue/";
    for (int i = 0; i < 32; ++i) {
        filename_ += charset[std::rand() % charset.length()];
    }
    file.open(filename_);

    key_ = ftok(filename_.c_str(), 65);
    id_ = msgget(key_, 0666 | IPC_CREAT);
}

Pla::MessageQueue::MessageQueue(key_t key) : key_(key)
{
    id_ = msgget(key_, 0666 | IPC_CREAT);
}

Pla::MessageQueue::~MessageQueue()
{
    msgctl(id_, IPC_RMID, NULL);
    if (!filename_.empty()) {
        std::remove(filename_.c_str());
    }
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

    msg = Pla::Message(packed_message);
    return res;
}

bool Pla::MessageQueue::pop(Pla::Message &msg) const
{
    Pla::PackedMessage packed_message;
    bool res = (msgrcv(id_, &packed_message, sizeof(Pla::PackedMessage) - sizeof(long), 1, 0) >= 0);

    msg = Pla::Message(packed_message);
    return res;
}

key_t Pla::MessageQueue::getKey() const
{
    return key_;
}
