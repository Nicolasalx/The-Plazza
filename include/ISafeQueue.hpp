/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** ISafeQueue
*/

#ifndef ISAFEQUEUE_HPP_
    #define ISAFEQUEUE_HPP_

namespace Pla
{
    template<typename T>
    class ISafeQueue
    {
    public:
        virtual ~ISafeQueue() = default;
        virtual void push(T value) const = 0;
        virtual bool tryPop(T &value) const = 0;
        virtual bool pop(T &value) const = 0;
    };
}

#endif /* !ISAFEQUEUE_HPP_ */
