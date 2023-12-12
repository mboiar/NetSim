#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType type) {
    queueType_ = type;
    queue_ = std::list<Package>();
}

Package PackageQueue::pop() {
    if (queueType_ == LIFO) {
        auto val = queue_.back();
        queue_.pop_back();
        return val;
    } else {
        auto val = queue_.front();
        queue_.pop_front();
        return val;
    }
}
