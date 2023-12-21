#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
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

// IO

ParsedLineData parse_line(std::string line){
    ParsedLineData out;
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(line);
    char delimiter = ' ';
    char id_delimiter = '=';
    std::getline(token_stream, token, delimiter);
    if(token == "LOADING_RAMP"){
        out.type = RAMP;
    }
    if(token == "WORKER"){
        out.type = WORKER;
    }
    if(token == "STOREHOUSE"){
        out.type = STOREHOUSE;
    }
    if(token == "LINK"){
        out.type = LINK;
    }

    while (std::getline(token_stream, token, delimiter)) {
        std::string key = token.substr(0, token.find(id_delimiter));
        std::string id = token.substr(token.find(id_delimiter), token.size()-1);
        out.map.insert(std::make_pair(key,id));
    }
    return out;
}

Factory load_factory_structure(std::istream& is){

    Factory factory;
    std::string line;

    while (std::getline(is, line)){
        if(line[0] == ';' || line.empty()){
            continue;
        }
        ParsedLineData elem = parse_line(line);

        if(elem.type == RAMP){
            ElementID id = (unsigned)std::stoi((*elem.map.find("ramp-id")).second);
            TimeOffset di = std::stoi((*elem.map.find("delivery-interval")).second);
            factory.add_ramp(Ramp(id,di));
        }

        if(elem.type == WORKER){
            ElementID id = (unsigned)std::stoi((*elem.map.find("worker-id")).second);
            TimeOffset pt = std::stoi((*elem.map.find("processing-time")).second);
            std::string unt_pt = (*elem.map.find("queue-type")).second;
            PackageQueueType typeQueue;

            typeQueue = (*elem.map.find("queue-type")).second == "LIFO" ? PackageQueueType::LIFO : PackageQueueType::FIFO;

            std::unique_ptr<PackageQueue> q = std::make_unique<PackageQueue>(PackageQueue(typeQueue));
            std::unique_ptr<IPackageQueue> qr = std::move(q);

            factory.add_worker(Worker(id, pt, std::move(qr)));
        }

        if(elem.type == STOREHOUSE){
            ElementID id = (unsigned)std::stoi((*elem.map.find("storehouse-id")).second);
            factory.add_storehouse(Storehouse(id));
        }

        if(elem.type == LINK){

        }

    }
    return factory;
}

//void save_factory_structure(Factory& factory, std::ostream& os){
//    os << "; == LOADING RAMPS" << std::endl;
//    os.put(os.widen('\n'));
//}