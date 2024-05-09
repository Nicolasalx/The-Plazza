/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

    #include <vector>
    #include <list>
    #include "Cook.hpp"
    #include "Plazza.hpp"
    #include "MessageQueue.hpp"
    #include "ThreadPool.hpp"

namespace Pla
{
    class Kitchen
    {
    private:
        Pla::ThreadPool cook_;
        double cook_time_;
        std::vector<int> ingredient_;
        std::list<Pla::Order> pizza_;
        long ing_repl_time_;
        std::mutex mutex_;
        Pla::Clock clock_;
        std::unique_ptr<Pla::MessageQueue> send_msg_queue_;
        std::unique_ptr<Pla::MessageQueue> recv_msg_queue_;
        std::atomic_bool has_order_;
        std::atomic_bool exit_;

        void loop();
        void handleNewMessage(const Pla::Message &msg);
        void refillIngredient();
        void sendStatus();

    public:
        Kitchen(std::size_t nb_cook, double cook_time, long ing_repl_time, key_t send_msg_key, key_t recv_msg_key);
        ~Kitchen() = default;
    };
}

#endif /* !KITCHEN_HPP_ */
