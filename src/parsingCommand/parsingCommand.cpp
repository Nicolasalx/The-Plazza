/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** parsingCommand
*/

#include "ParseCommand.hpp"
#include "Plazza.hpp"
#include "split_string.hpp"
#include "my_tracked_exception.hpp"

void Pla::ParseCommand::analyseOneCommand(const std::string &command, int &orderCommand)
{
    Pla::Order order;
    std::vector<std::string> instructionCmd;
    command_state_e cmd_state = NAME;
    int pizzaNumber = 0;

    my::split_string(command, " ", instructionCmd);
    if (instructionCmd.empty()) {
        throw my::tracked_exception("One command gived by the customer is empty!");
    }
    for (auto &inst: instructionCmd) {
        switch (cmd_state) {
            case NAME:
                definePizzaType(order, inst);
                cmd_state = SIZE;
                break;
            case SIZE:
                definePizzaSize(order, inst);
                cmd_state = NUMBER;
                break;
            case NUMBER:
                definePizzaNumber(inst, pizzaNumber);
                break;
            default:
                break;
        }
    }
    if (pizzaNumber <= 0) {
        throw my::tracked_exception("In the command, we can't get all parameters for the preparation!");
    }
    order.state = Pla::PizzaState::WAITING_TO_BE_COOK;
    for (int i = 0; i < pizzaNumber; ++i) {
        order.nb = orderCommand;
        _allOrders.push_back(order);
    }
}

std::vector<Pla::Order> Pla::ParseCommand::parsingCommand(const std::string &input, int &orderCommand)
{
    std::vector<std::string> allCommand;
    my::split_string(input, ";", allCommand);

    if (allCommand.empty()) {
        printErrMess("Command gived by the customer is empty!");
        return _allOrders;
    }
    try {
        for (auto &token: allCommand) {
            analyseOneCommand(token, orderCommand);
        }
    } catch(const my::tracked_exception &exception) {
        printErrMess(exception.what());
    }
    orderCommand++;
    return _allOrders;
}
