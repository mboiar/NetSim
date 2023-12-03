#include "nodes.hpp"

void Storehouse::receive_package(Package&& p) {
    storage_->push(p);
}

void Worker::receive_package(Package&& p) {
    q_->push(p);
}

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    double preference = pg_();// TODO sum to 1
    preferences_.emplace(r, preference);
    for (auto item: preferences_){
        item.second /= (1 + preference);
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double diff = preferences_.at(r);
    preferences_.erase(r);
    for (auto item: preferences_){
        item.second /= (1 - diff);
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double prob = pg_();

    double cdf = 0;
    for (auto item: preferences_){
        cdf += item.second;
        if (prob <= cdf){
            return item.first;
        }
    }
}

void PackageSender::send_package() {
    if (buffer_) {
        receiver_preferences_.choose_receiver()->receive_package(std::move(buffer_.value()));
    }
}

void Ramp::deliver_goods(Time t) {
    if (t % di_ == 0){
        push_package(Package());
    }
}

void Worker::do_work(Time t) {
    if (pst_ == 0){ // worker is idle, start work
        if (!q_->empty()){
            pst_ = t;
        } else {
            return;
        }
    }
    if (t - (pst_ + pd_) == 0){ // if work finished
        push_package(std::move(q_->pop()));
        pst_ = 0;
    }
}