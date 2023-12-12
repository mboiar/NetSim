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
    virtual void push(Package&&) = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator end() const = 0;
    virtual ~IPackageStockpile() {};
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
    virtual ~IPackageQueue() = default;
};

class PackageQueue: public IPackageQueue {
public:
    PackageQueue(PackageQueueType type);

    //IPackageQueue
    Package pop() override;
    PackageQueueType get_queue_type() override {return queueType_;}

    //IPackageStockpile
    void push(Package&& package) override {queue_.emplace_back(package);}
    bool empty() const override {return queue_.empty();}
    size_t size() const override {return queue_.size();}
    const_iterator cbegin() const override {return queue_.cbegin();}
    const_iterator begin() const override {return queue_.begin();}
    const_iterator cend() const override {return queue_.cend();}
    const_iterator end() const override {return queue_.end();}

    ~PackageQueue() = default;
private:
    std::list<Package> queue_;
    PackageQueueType queueType_;
};

#endif //IMPLEMENTATION_STORAGE_TYPES_HPP
