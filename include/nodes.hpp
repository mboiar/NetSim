#ifndef IMPLEMENTATION_NODES_HPP
#define IMPLEMENTATION_NODES_HPP

#include <memory>
#include <optional>
#include <map>

#include "storage_types.hpp"
#include "package.hpp"
#include "types.hpp"


enum class ReceiverType{
Worker,
Storehouse
};

class IPackageReceiver{
public:
    IPackageReceiver() = default;
    virtual void receive_package(Package&& p);
    ElementID get_id() const;
    IPackageStockpile::const_iterator cbegin() const;
    IPackageStockpile::const_iterator cend() const;
    virtual ~IPackageReceiver() = default;
};

class Storehouse: public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d);
};

class ReceiverPreferences{
public:
    ReceiverPreferences(ProbabilityGenerator pg);
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    void add_package_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();

    const_iterator cbegin() const { return preferences_.cbegin(); }
    const_iterator cend() const { return preferences_.cend(); }
    const preferences_t& get_preferences() const { return preferences_; };
    preferences_t preferences_;
};

class PackageSender{
public:
    PackageSender(PackageSender&& ps) = default;
    void send_package();
    std::optional<Package>& get_sending_buffer() const;
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&& p);
};

class Ramp: public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const;
    ElementID get_id() const;
};

class Worker: public IPackageReceiver, public PackageSender {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);
    void do_work(Time t);
    TimeOffset get_processing_duration() const;
    Time get_package_processing_start_time() const;
};

#endif //IMPLEMENTATION_NODES_HPP
