#ifndef IMPLEMENTATION_STORAGE_TYPES_HPP
#define IMPLEMENTATION_STORAGE_TYPES_HPP

#include <list>

#include "package.hpp"

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
};

class IPackageQueue{};

class PackageQueue{};

enum PackageQueueType{};

#endif //IMPLEMENTATION_STORAGE_TYPES_HPP
