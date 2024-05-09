/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** thread_pool
*/

#include "ThreadPool.hpp"

void Pla::ThreadPool::executeWork()
{
    std::function<void()> work = nullptr;

    while (!this->exit_)
    {
        {
            std::unique_lock<std::mutex> lock_mutex(mutex_);
            this->new_work_.wait(lock_mutex, [this] { return this->exit_ || !this->work_.empty(); });
            if (this->exit_) {
                return;
            }
            work = std::move(this->work_.front());
            this->work_.pop();
        }
        work();
    }
}

Pla::ThreadPool::ThreadPool() : exit_(false)
{
}

Pla::ThreadPool::ThreadPool(std::size_t nb_thread) : exit_(false)
{
    this->launch(nb_thread);
}

void Pla::ThreadPool::launch(std::size_t nb_thread)
{
    for (size_t i = 0; i < nb_thread; ++i) {
        thread_.emplace_back([this]{executeWork();});
    }
}

void Pla::ThreadPool::stop()
{
    this->exit_ = true;
    for (std::thread &it : this->thread_) {
        it.join();
    }
}

Pla::ThreadPool::~ThreadPool()
{
    stop();
}
