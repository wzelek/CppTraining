#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

struct Mariner {
public:
    Mariner(unsigned width_);
    ~Mariner();
private:
    void run() const;
    void walk(int delta);
    void showRoad() const;
    std::thread leftThread;
    std::thread rightThread;
    mutable std::mutex mtx;
    const unsigned width;
    unsigned position;
    bool stop;
};

Mariner::Mariner(unsigned width_)
    : leftThread{}, rightThread{}, mtx{}, width{width_}, position(width / 2), stop{false} {
    {
        std::lock_guard<std::mutex> lk(mtx);
        leftThread = std::thread(&Mariner::walk, this, -1);
        rightThread = std::thread(&Mariner::walk, this, 1);
    }
    run();
}

Mariner::~Mariner() {
    stop = true;
    leftThread.join();
    rightThread.join();
}

void Mariner::run() const {
    while(!stop) {
        showRoad();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    showRoad();
}

void Mariner::walk(int delta) {
    while(!stop) {
        {
            std::lock_guard<std::mutex> lk(mtx);
            position = static_cast<unsigned>(static_cast<int>(position) + delta);
            if((position == 0) || (position == (width -1))) {
                stop = true;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //std::this_thread::sleep_for(std::chrono::milliseconds(100 + delta * 10));
        //std::this_thread::sleep_for(std::chrono::milliseconds(100 - delta * 10));
    }
}

void Mariner::showRoad() const {
    unsigned pos;
    {
        std::lock_guard<std::mutex> lk(mtx);
        pos = position;
    }
    std::cout << '|' << std::string(pos, '-') << '*'
              << std::string(width - pos - 1, '-') << "|\n";
}

int main() {
    Mariner mariner(20);
}
