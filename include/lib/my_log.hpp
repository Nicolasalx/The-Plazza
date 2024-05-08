/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** my_log
*/

#ifndef MY_LOG_HPP_
    #define MY_LOG_HPP_

    #include <stdexcept>
    #include <string>
    #include <source_location>
    #include <format>
    #include <iostream>

namespace my::log
{
    void info(const std::string &msg,
        std::source_location info = std::source_location::current());

    void warning(const std::string &msg,
        std::source_location info = std::source_location::current());

    void error(const std::string &msg,
        std::source_location info = std::source_location::current());
}

#endif /* !MY_LOG_HPP_ */
