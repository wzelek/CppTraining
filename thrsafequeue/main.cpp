#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

struct ThrdSafeQueue {
    [[nodiscard]] bool write(int val) {
        std::unique_lock<std::mutex> lk(mtx);
        if(stop) {
            return false;
        }
        q.push(val);
        cv.notify_one();
        return true;
    }
    [[nodiscard]] bool read(int& result) {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [this]{ return (! q.empty()) || stop; });
        if(stop) {
            return false;
        }
        result = q.front();
        q.pop();
        return true;
    }
    void imStop() {
        std::lock_guard<std::mutex> lk(mtx);
        stop = true;
        cv.notify_all();
    }
private:
    std::queue<int> q;
    mutable std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
};

void reader(ThrdSafeQueue& q) {
    for(auto i = 0U; i < 5; ++i) {
        int value;
        if(q.read(value)) {
            std::cout << "value = " << value << '\n';
        } else {
            std::cerr << "Queue stopped!!!\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(ThrdSafeQueue& q) {
    for(auto i = 0U; i < 10; ++i) {
        if(!q.write(i)) {
            break;
        }
        std::cout << "Write value = " << i << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    ThrdSafeQueue q;
    std::thread rthrd1(reader, std::ref(q));
    std::thread rthrd2(reader, std::ref(q));
    std::thread wthrd1(writer, std::ref(q));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    q.imStop();
    for(auto t: {&rthrd1, &rthrd2, &wthrd1}) {
        t->join();
    }
}
