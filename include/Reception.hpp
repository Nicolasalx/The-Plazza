/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_

    #include "Plazza.hpp"
    #include "MessageQueue.hpp"
    #include <list>
    #include <queue>
    #include <fstream>

namespace Pla
{
    struct ComKitchen
    {
        pid_t pid;
        Pla::MessageQueue send_msg_queue;
        Pla::MessageQueue recv_msg_queue;
        std::vector<Pla::Order> order_;
        int nb_used_cook = 0;

        ComKitchen() = default;
        ComKitchen(pid_t pid_) : pid(pid_) {};
    };

    class Reception
    {
    private:
        double cooking_time_;
        int nb_cook_;
        long ing_repl_time_;
        int order_index_ = 0;
        std::list<Pla::ComKitchen> kitchen_list_;
        std::queue<Pla::Order> order_;
        std::mutex mutex_;
        std::atomic_bool exit_;
        std::ofstream log_file_;

    public:
        Reception(int argc, const char **argv);
        ~Reception() = default;

        void openPlazza();
        void handleInput(const std::string &input);
        void manageKitchen();
        void handleRecvMessage();
        void handleRecvStatus(const std::list<Pla::ComKitchen>::iterator &it, const Pla::Message &msg);
        void dispatchOrder();
        void displayStatus();
        void displayCookWork(const Pla::ComKitchen &kitchen) const;
        static void displayWaitingOrder(const Pla::ComKitchen &kitchen);
        void createKitchen();
        void closeAllKitchen();
    };
}

#endif /* !RECEPTION_HPP_ */
