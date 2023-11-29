#ifndef IMPLEMENTATION_STORAGE_TYPES_HPP
#define IMPLEMENTATION_STORAGE_TYPES_HPP

#include <list>

#include "package.hpp"

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
};

class IPackageQueue : public IPackageStockpile {};

class PackageQueue: public IPackageQueue {};

enum PackageQueueType{
    FIFO,
    LIFO
};

#endif //IMPLEMENTATION_STORAGE_TYPES_HPP
