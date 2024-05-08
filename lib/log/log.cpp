/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** log
*/

#include "my_log.hpp"

void my::log::info(const std::string &msg,
    std::source_location info)
{
    std::cerr << std::format("\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[96minfo: \033[0m{}\n", info.file_name(), info.line(), msg);
}

void my::log::warning(const std::string &msg,
    std::source_location info)
{
    std::cerr << std::format("\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[95mwarning: \033[0m{}\n", info.file_name(), info.line(), msg);
}

void my::log::error(const std::string &msg,
    std::source_location info)
{
    std::cerr << std::format("\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[91merror: \033[0m{}\n", info.file_name(), info.line(), msg);
}
