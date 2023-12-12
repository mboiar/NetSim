#include "package.hpp"
#include "storage_types.hpp"

int main(){
    PackageQueue q(PackageQueueType::FIFO);
    q.push(Package(1));
    q.push(Package(2));

    Package p(std::move(q.pop()));

    return 0;
};
