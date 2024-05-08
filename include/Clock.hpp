/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

    #include <chrono>

namespace Pla
{
    class Clock
    {
    public:
        Clock() = default;
        Clock(std::chrono::milliseconds cooldown) : _cooldown(cooldown) {}
        ~Clock() = default;

        void setCooldown(std::chrono::milliseconds cooldown)
        {
            this->_cooldown = cooldown;
        }

        void start()
        {
            this->_start = std::chrono::steady_clock::now();
        }

        bool isElapsed() const
        {
            return (std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - this->_start) >= this->_cooldown);
        }

        void reset()
        {
            this->_start = std::chrono::steady_clock::now();
        }

        std::chrono::milliseconds getCurrentTime() const
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - this->_start);
        }

        void addTime(std::chrono::milliseconds time)
        {
            this->_start += time;
            if (this->getCurrentTime() <= std::chrono::milliseconds(0)) {
                this->reset();
            }
        }

    private:
        std::chrono::milliseconds _cooldown;
        std::chrono::steady_clock::time_point _start;
    };
}

#endif /* !CLOCK_HPP_ */
