#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    double preference = pg_();// TODO sum to 1
    preferences_.emplace(r, preference);
    for (auto it = preferences_.begin(); it != preferences_.end(); it++){
        it->second /= (1 + preference);
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double diff = preferences_.at(r);
    preferences_.erase(r);
    for (auto it = preferences_.begin(); it != preferences_.end(); it++){
        it->second /= (1 - diff);
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double prob = pg_();

    double cdf = 0;
    for (auto it = preferences_.begin(); it != preferences_.end(); it++){
        cdf += it->second;
        if (prob <= cdf){
            return it->first;
        }
    }
}

void PackageSender::send_package() {
    Package p;
    if (buffer_){
        p = buffer_.value();
    } else{
        p
    }
    receiver_preferences_.choose_receiver()->receive_package();
}

void Ramp::deliver_goods(Time t) {
    if (t % di_ == 0){
        send_package();
        push_package(); //TODO ???
    }
}

void Worker::do_work(Time t) {
    do something idk
}