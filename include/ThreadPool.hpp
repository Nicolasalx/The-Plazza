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
        bool exit_ = false;

        bool needExit()
        {
            bool need_exit = false;

            this->mutex_.lock();
            need_exit = this->exit_;
            this->mutex_.unlock();
            return need_exit;
        }

        void executeWork()
        {
            std::function<void()> work;

            while (!this->needExit())
            {
                {
                    std::unique_lock<std::mutex> lock_mutex;
                    this->new_work_.wait(lock_mutex);
                    if (this->exit_) {
                        return;
                    }
                    if (!this->work_.empty()) {
                        work = this->work_.front();
                        this->work_.pop();
                    }
                }
                work();
            }
        }

    public:
        ThreadPool() = default;
        ThreadPool(std::size_t nb_thread)
        {
            this->launch(nb_thread);
        }

        void launch(std::size_t nb_thread)
        {
            for (size_t i = 0; i < nb_thread; ++i) {
                thread_.emplace_back([this]{executeWork();});
            }
        }

        template<typename Func>
        void addWork(Func &&func)
        {
            this->mutex_.lock();
            this->work_.emplace(std::forward<Func>(func));
            this->mutex_.unlock();
        }

        void stop()
        {
            this->mutex_.lock();
            this->exit_ = true;
            this->mutex_.unlock();
            this->new_work_.notify_all();
            for (std::thread &it : this->thread_) {
                it.join();
            }
        }

        ~ThreadPool()
        {
            stop();
        }
    };
}

#endif /* !THREADPOOL_HPP_ */
