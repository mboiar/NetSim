#include <stdexcept>
#include <string>
#include "factory.hpp"



void Factory::do_deliveries(Time time) {
    for(auto& el : ramps_)
        el.deliver_goods(time);
}

void Factory::do_package_passing() {
    for(auto& el : ramps_)
        el.send_package();
    for(auto& el : workers_)
        el.send_package();
}

void Factory::do_work(Time time) {
    for(auto& el : workers_)
        el.do_work(time);
}

bool Factory::is_consistent() {
    std::map<const PackageSender *, NodeColor> node_colors;
    for (Worker &worker: workers_) {
        const PackageSender *worker_ptr = &worker;
        node_colors[worker_ptr] = NodeColor::UNVISITED;
    }
    for (Ramp &ramp: ramps_) {
        const PackageSender *ramp_ptr = &ramp;
        node_colors[ramp_ptr] = NodeColor::UNVISITED;
        try {
            has_reachable_storehouse(ramp_ptr, node_colors);
        }
        catch (std::logic_error& error) {
            return false;
        }
    }
    return true;
}

bool Factory::has_reachable_storehouse(const PackageSender *sender,
                                       std::map<const PackageSender *, NodeColor> &node_colors) {
    if (node_colors[sender] == NodeColor::VERIFIED) return true;
    node_colors[sender] = NodeColor::VISITED;

    if (sender->receiver_preferences_.get_preferences().empty()) throw std::logic_error("Sender has no receivers");

    bool other_receiver = false;
    for (auto& [receiver, priority] : sender->receiver_preferences_.get_preferences()) {
        if (receiver->get_receiver_type() == ReceiverType::Storehouse) other_receiver = true;
        else if (receiver->get_receiver_type() == ReceiverType::Worker) {
            IPackageReceiver* receiver_ptr = receiver;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if (sendrecv_ptr == sender) continue;
            other_receiver = true;
            if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED) has_reachable_storehouse(sendrecv_ptr, node_colors);
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;

    if (other_receiver) return true;
    else throw std::logic_error("Sender has no receiver other than themself");
}

void Factory::remove_storehouse(ElementID id) {
    remove_receiver(storehouses_, id);
    storehouses_.remove_by_id(id);
}

void Factory::remove_worker(ElementID id) {
    remove_receiver(workers_, id);
    workers_.remove_by_id(id);
}

template <class Node>
void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
    auto ptr = dynamic_cast<IPackageReceiver*>(&(*collection.find_by_id(id)));
    for (Worker& sender: workers_) sender.receiver_preferences_.remove_receiver(ptr);
    if (std::is_same<Node, Worker>::value) {
        for (Ramp& sender: ramps_) sender.receiver_preferences_.remove_receiver(ptr);
    }
}
