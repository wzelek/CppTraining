#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template<typename T>
struct Instances {
protected:
    Instances() {
        Instances<T>::instances.push_back(static_cast<T*>(this));
    }
    ~Instances() {
        auto& inst = Instances<T>::instances;
        inst.erase(std::remove(inst.begin(), inst.end(), this), inst.end());
    }
public:
    static std::vector<T *> getInstances();
private:
    static std::vector<T *> instances;
};

template<typename T>
std::vector<T*> Instances<T>::getInstances() {
    return Instances<T>::instances;
}

template<typename T>
std::vector<T *> Instances<T>::instances;

struct Airplane : Instances<Airplane> {
    explicit Airplane(const std::string& name_)
      : name{name_} {
    }
    void info() const {
        std::cout << "Airplane: name = " << name << '\n';
    }
private:
    std::string name;
};

int main() {
    {
        Airplane a1{"F35"};
        Airplane a2{"F22"};
        for(auto a: Instances<Airplane>::getInstances()) {
            a->info();
        }
    }
    for(auto a: Instances<Airplane>::getInstances()) {
        a->info();
    }
}
