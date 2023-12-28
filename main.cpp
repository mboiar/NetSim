#include "package.hpp"
#include "storage_types.hpp"
#include "factory.hpp"
#include "reports.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    Factory factory;

    factory.add_ramp(Ramp(1, 1));
    factory.add_ramp(Ramp(2, 2));
    factory.add_worker(Worker(1, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_worker(Worker(2, 2, std::make_unique<PackageQueue>(PackageQueueType::LIFO)));
    factory.add_storehouse(Storehouse(1));
    factory.add_storehouse(Storehouse(2));

    Ramp& r1 = *(factory.find_ramp_by_id(1));
    r1.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(1)));

    Ramp& r2 = *(factory.find_ramp_by_id(2));
    r2.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(1)));
    r2.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(2)));

    Worker& w1 = *(factory.find_worker_by_id(1));
    w1.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(2)));

    Worker& w2 = *(factory.find_worker_by_id(2));
    w2.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(1)));
    w2.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(2)));

    std::ostringstream oss;

    generate_structure_report(factory, oss);

    std::cout << oss.str() << std::endl;
    return 0;
};
