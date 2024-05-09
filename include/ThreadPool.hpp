/*
** EPITECH PROJECT, 2024
** B-CCP-400-PAR-4-1-theplazza-thibaud.cathala
** File description:
** ThreadPool
*/

#ifndef THREADPOOL_HPP_
    #define THREADPOOL_HPP_

    #include <functional>
    #include <queue>
    #include <thread>
    #include <condition_variable>

namespace Pla
{
    class ThreadPool
    {
    private:
        std::vector<std::thread> thread_;
        std::queue<std::function<void()>> work_;
        std::mutex mutex_;
        std::condition_variable new_work_;
        std::atomic_bool exit_;

        void executeWork();

    public:
        ThreadPool();
        ThreadPool(std::size_t nb_thread);
        ~ThreadPool();

        void launch(std::size_t nb_thread);

        template<typename Func>
        void addWork(Func &&func)
        {
            this->mutex_.lock();
            this->work_.emplace(std::forward<Func>(func));
            this->new_work_.notify_one();
            this->mutex_.unlock();
        }

        void stop();
    };
}

#endif /* !THREADPOOL_HPP_ */
