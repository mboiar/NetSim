#include "package.hpp"
#include "storage_types.hpp"
#include "factory.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    PackageQueue q(PackageQueueType::FIFO);
    q.push(Package(1));
    q.push(Package(2));

    Package p(std::move(q.pop()));

    std::istringstream iss("LOADING_RAMP id=1 delivery-interval=3\n"
                           "WORKER id=1 processing-time=2 queue-type=FIFO\n"
                           "STOREHOUSE id=1");

    load_factory_structure(iss);
    return 0;
};
