/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Order
*/

#ifndef ORDER_HPP_
    #define ORDER_HPP_

    #include "APizza.hpp"

namespace Pla
{
    struct Order
    {
        int nb = 0;
        Pla::APizza pizza;
    };
}

#endif /* !ORDER_HPP_ */
