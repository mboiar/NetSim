#ifndef IMPLEMENTATION_NODES_HPP
#define IMPLEMENTATION_NODES_HPP

#include <memory>
#include <optional>
#include <map>

#include "storage_types.hpp"
#include "package.hpp"
#include "types.hpp"
#include "helpers.hpp"


enum class ReceiverType{
Worker,
Storehouse
};

class IPackageReceiver{
public:
    IPackageReceiver() = default;
    virtual void receive_package(Package&& p);
    virtual ElementID get_id() const;
    virtual IPackageStockpile::const_iterator cbegin() const;
    virtual IPackageStockpile::const_iterator cend() const;
    virtual ~IPackageReceiver() = default;
};

class Storehouse: public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>()): id_(id), storage_(std::move(d)){};
private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> storage_;
};

class ReceiverPreferences{
public:
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator): pg_(pg){};
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();

    const_iterator cbegin() const { return preferences_.cbegin(); }
    const_iterator cend() const { return preferences_.cend(); }
    const_iterator begin() const { return preferences_.cbegin(); }
    const_iterator end() const { return preferences_.cend(); }
    const preferences_t& get_preferences() const { return preferences_; };
    preferences_t preferences_;
private:
    ProbabilityGenerator pg_;
};

class PackageSender{
public:
    PackageSender(PackageSender&& ps) = default;
    void send_package();
    const std::optional<Package>& get_sending_buffer() const { return buffer_; };
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&& p) { buffer_.emplace(p); };
private:
    std::optional<Package> buffer_;
};

class Ramp: public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di): id_(id), di_(di){};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return di_; };
    ElementID get_id() const { return id_; };
private:
    ElementID id_;
    TimeOffset di_;
};

class Worker: public IPackageReceiver, public PackageSender {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q): id_(id), pd_(pd), q_(std::move(q)){};
    void do_work(Time t);
    TimeOffset get_processing_duration() const { return pd_; };
    Time get_package_processing_start_time() const { return pst_; };
private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    Time pst_;
};

#endif //IMPLEMENTATION_NODES_HPP
