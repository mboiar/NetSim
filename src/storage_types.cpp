#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType type) {
    queueType = type;
    queue = std::list<Package>();
}

Package PackageQueue::pop() {
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
