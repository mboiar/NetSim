#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType type) {
    queueType = type;
    queue = std::list<Package>();
}

PackageQueueType IPackageQueue::get_queue_type() {
    return queueType;
}

void IPackageStockpile::push(Package&& pckg) {
    queue.emplace_back(std::move(pckg));
}

Package IPackageQueue::pop() {
    if (queueType == LIFO) {
        auto val = queue.back();
        queue.pop_back();
        return val;
    } else {
        auto val = queue.front();
        queue.pop_front();
        return val;
    }
}

bool IPackageStockpile::empty() const{
    return queue.empty();
}

size_t IPackageStockpile::size() const{
    return queue.size();
}
