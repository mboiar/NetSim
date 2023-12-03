#ifndef IMPLEMENTATION_STORAGE_TYPES_HPP
#define IMPLEMENTATION_STORAGE_TYPES_HPP

#include <list>

#include "package.hpp"

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual ~IPackageStockpile() = default;
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual ~IPackageQueue() = default;
};

class PackageQueue: public IPackageQueue {
public:
    ~PackageQueue() = default;
};

enum PackageQueueType{
    FIFO,
    LIFO
};

#endif //IMPLEMENTATION_STORAGE_TYPES_HPP
