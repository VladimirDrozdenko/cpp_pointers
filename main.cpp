#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>

#include "headers/base.h"
#include "headers/derived.h"


void PlayWithSharedPointers() {
    std::shared_ptr<Base> s_base = std::make_shared<Base>();
    s_base->speak();

    std::shared_ptr<Base> s_derived_custom(new Derived, Derived::custom_deleter);
    s_derived_custom->speak();

    std::shared_ptr<Base> sp = s_base;
    sp->speak();

    std::shared_ptr<Base> sp1 = s_base;

    std::cout << "SP usecount = " << sp.use_count() << std::endl;

    sp.reset(new Derived);
    std::cout << "SP usecount = " << sp.use_count() << std::endl;
    sp->speak();


    std::vector<std::shared_ptr<Base>> vec;
    vec.push_back(s_base);
    vec.push_back(sp);
    vec.push_back(s_derived_custom);

    for (const auto& item : vec) {
        item->speak();
    }
}

void PlayWithWeakPointers() {

    std::shared_ptr<Base> sp1 = std::make_shared<Base>();
    std::cout << "SP1 usecount = " << sp1.use_count() << std::endl;

    std::weak_ptr<Base> wp1 = sp1;
    std::cout << "SP1 usecount is still = " << sp1.use_count() << std::endl;

    if (std::shared_ptr<Base> locked = wp1.lock()) {
        std::cout << "SP1 usecount = " << sp1.use_count() << std::endl;
        locked->speak(); 
    }

    sp1.reset();
    std::cout << "SP1 usecount after reset = " << sp1.use_count() << std::endl;

    if (wp1.expired()) {
        std::cout << "Weak_ptr expired after reset." << std::endl;
    }
}


void PlayWithSharedPtrAlias() {

    std::shared_ptr<Base> sp1 = std::make_shared<Base>();
    std::cout << "SP1 usecount = " << sp1.use_count() << std::endl;

    std::shared_ptr<Base> alias(sp1, new Derived);
    std::cout << "SP1 usecount = " << sp1.use_count() << std::endl;

    const std::size_t N = 3;
    std::shared_ptr<Base[]> sp_array(new Base[N]);
    for (std::size_t i = 0; i < N; ++i) {
        sp_array[i].speak();
    }
}

void PlayWithAtomic() {

    std::shared_ptr<Base> sp1 = std::make_shared<Base>();
    std::shared_ptr<Base> sp2;

    std::thread t1([&]() {
        std::atomic_store(&sp2, std::atomic_load(&sp1));
    });

    std::thread t2([&]() {
        std::atomic_store(&sp1, std::shared_ptr<Base>(nullptr));
    });

    t1.join();
    t2.join();

    if (sp2) {
        sp2->speak();
    }
}

int main() {

    PlayWithSharedPointers();

    std::cout << "\n-----------------\n" << std::endl;

    PlayWithWeakPointers();

    std::cout << "\n-----------------\n" << std::endl;

    PlayWithSharedPtrAlias();

    std::cout << "\n-----------------\n" << std::endl;

    PlayWithAtomic();
}
