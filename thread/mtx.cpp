#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

int counter = 65535;
std::mutex mtx;

using namespace std::chrono_literals;

void worker(int delta) {
    for(auto i = 0U; i < 100; ++i) {
        std::this_thread::sleep_for(10ms);
        {
            std::lock_guard<std::mutex> _(mtx);
            //mtx.lock();
            counter += delta;
            //mtx.unlock();
        }
    }
}

int main() {
    std::thread thr1(worker, 1);
    std::thread thr2(worker, -1);
    thr1.join();
    thr2.join();
    std::cout << "65535 = " << counter << '\n';
}
