/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** ParseCommand
*/

#ifndef PARSECOMMAND_HPP_
    #define PARSECOMMAND_HPP_

    #include <string>
    #include <vector>
    #include <cctype>
    #include "Plazza.hpp"

namespace Pla
{
    enum command_state_e {
        NAME,
        NUMBER,
        SIZE
    };
    class ParseCommand
    {
        public:
            std::vector<Order> parsingCommand(const std::string &input, int &orderCommand);
            void toLowerCase(std::string &str);
            void definePizzaType(Order &order, std::string &input);
            void definePizzaSize(Order &order, std::string &input);
            void definePizzaNumber(std::string &input, int &pizzaNumber);
            void analyseOneCommand(const std::string &command, int &orderCommand);
            void printErrMess(const std::string &str);
            int getInt(const std::string &input);

        private:
            std::vector<Pla::Order> _allOrders;
    };
};

#endif /* !PARSECOMMAND_HPP_ */
