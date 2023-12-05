#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType type) {
    queueType = type;
    queue = std::list<Package>();
}

PackageQueueType IPackageQueue::get_queue_type() {
    return queueType;
}

void IPackageStockpile::push(Package&& pckg) {
    queue.insert(cend(), pckg);
}

Package IPackageQueue::pop() {
    if (queueType == LIFO) return *queue.erase(cend());
    else return *queue.erase(cbegin());
}

bool IPackageStockpile::empty() {
    return queue.empty();
}

size_t IPackageStockpile::size() {
    return queue.size();
}
