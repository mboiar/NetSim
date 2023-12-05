#ifndef IMPLEMENTATION_STORAGE_TYPES_HPP
#define IMPLEMENTATION_STORAGE_TYPES_HPP

#include <list>

#include "package.hpp"

enum PackageQueueType{
    FIFO,
    LIFO
};

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
    void push(Package&&);
    bool empty();
    size_t size();
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual ~IPackageStockpile() = default;
protected:
    std::list<Package> queue;
};

class IPackageQueue : public IPackageStockpile {
public:
    Package pop();
    PackageQueueType get_queue_type();
    virtual ~IPackageQueue() = default;
protected:
    PackageQueueType queueType;
};

class PackageQueue: public IPackageQueue {
public:
    explicit PackageQueue(PackageQueueType);
    ~PackageQueue() = default;

};



#endif //IMPLEMENTATION_STORAGE_TYPES_HPP
