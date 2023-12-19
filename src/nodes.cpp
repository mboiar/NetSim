#include "nodes.hpp"

void Storehouse::receive_package(Package&& p) {
    storage_->push(std::move(p));
}

void Worker::receive_package(Package&& p) {
    q_->push(std::move(p));
}

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    preferences_.emplace(r, 0.0);

    for (auto& item: preferences_){
        item.second = 1/(double)preferences_.size();
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    auto num_of_removed = preferences_.erase(r);
    if (num_of_removed > 0) {
        for (auto& item: preferences_){
            item.second = 1/(double)preferences_.size();
        }
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
    return preferences_.rbegin()->first;
}

void PackageSender::send_package() {
    if (buffer_) {
        IPackageReceiver* rec = receiver_preferences_.choose_receiver();
        rec->receive_package(std::move(buffer_.value()));
        buffer_.reset();
    }
}

void Ramp::deliver_goods(Time t) {
    if (t % di_ == 1){
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
    if (t - (pst_ + pd_ - 1) == 0){ // if work finished
        push_package(std::move(q_->pop()));
        pst_ = 0;
    }
}