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
    return false;
}

void Factory::remove_worker(ElementID id) {
    workers_.remove_by_id(id);
}
