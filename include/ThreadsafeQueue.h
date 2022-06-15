#ifndef __THREADSAFEQUEUE_H__
#define __THREADSAFEQUEUE_H__

#include <mutex>
#include <condition_variable>
#include <queue>

template<typename T>
class ThreadsafeQueue
{
private:
    mutable std::mutex mut;
    std::queue<T> dataQueue;
    std::condition_variable dataCond;
public:
    ThreadsafeQueue() {}
    void push(T newValue) {
        std::unique_lock<std::mutex> lk(mut);
        dataQueue.push(std::move(newValue));
        dataCond.notify_one();
    }

    void waitAndPop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        dataCond.wait(lk, [this] {return !dataQueue.empty();});
        value = std::move(dataQueue.front());
        dataQueue.pop();
    }

    std::shared_ptr<T> waitAndPop() {
        std::unique_lock<std::mutex> lk(mut);
        dataCond.wait(lk, [this]{return !dataQueue.empty();});
        std::shared_ptr<T> value(std::make_shared<T>(std::move(dataQueue.front())));
        dataQueue.pop();
        return value;
    }

    bool tryPop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        if (dataQueue.empty()) {
            return false;
        }
        value = dataQueue.front();
        dataQueue.pop();
        return true;
    }

    std::shared_ptr<T> tryPop() {
        std::unique_lock<std::mutex> lk(mut);
        if (dataQueue.empty()) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> value(std::make_unique<T>(std::move(dataQueue.front())));
        dataQueue.pop();
        return value;
    }

    bool empty() const {
        std::unique_lock<std::mutex> lk(mut);
        return dataQueue.empty();
    }

    size_t size() const {
        std::unique_lock<std::mutex> lk(mut);
        return dataQueue.size();
    }
};

#endif // __THREADSAFEQUEUE_H__
