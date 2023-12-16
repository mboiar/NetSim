#ifndef IMPLEMENTATION_FACTORY_HPP
#define IMPLEMENTATION_FACTORY_HPP

#include <vector>

#include "types.hpp"
#include "nodes.hpp"

template <class Node>
class NodeCollection{
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    iterator begin() { return nodes_list_.begin(); }
    iterator end() { return nodes_list_.end(); }
    const_iterator cbegin() const { return nodes_list_.cbegin(); }
    const_iterator cend() const { return nodes_list_.cend(); }

    void add(Node&& node) { nodes_list_.push_back(std::move(node)); };
    void remove_by_id(ElementID id) { nodes_list_.erase(find_by_id(id)); }
    NodeCollection<Node>::iterator find_by_id(ElementID id) {return std::find_if(nodes_list_.begin(), nodes_list_.end(), [id](Node& el) { return el.get_id() == id; });}
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const {return std::find_if(nodes_list_.cbegin(), nodes_list_.cend(), [id] (const Node& el) { return el.get_id() == id; });}
private:
    std::list<Node> nodes_list_;
};

class Factory{
public:
    void add_ramp(Ramp&& ramp) { ramps_.add(std::move(ramp)); }
    void remove_ramp(ElementID id) { remove_receiver(ramps_, id); }
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return ramps_.find_by_id(id); }
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramps_.find_by_id(id); }
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramps_.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramps_.cend();}

    void add_worker(Worker&& worker) { workers_.add(std::move(worker)); }
    void remove_worker(ElementID id) { remove_receiver(workers_, id); }
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return workers_.find_by_id(id); }
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return workers_.find_by_id(id); }
    NodeCollection<Worker>::const_iterator worker_cbegin() const {return workers_.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return workers_.cend();}

    void add_storehouse(Storehouse&& storehouse) { storehouses_.add(std::move(storehouse)); }
    void remove_storehouse(ElementID id) { remove_receiver(storehouses_, id); }
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouses_.find_by_id(id); }
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouses_.find_by_id(id); }
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const { return storehouses_.cbegin(); }
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const { return storehouses_.cend(); }

    bool is_consistent();
    void do_deliveries(Time time);
    void do_package_passing();
    void do_work(Time time);

private:
    enum class NodeColor {
        UNVISITED,
        VISITED,
        VERIFIED
    };
    bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);
    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> storehouses_;
    template <class Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id) { collection.remove_by_id(id); }
};

// zapis i odczyt

#endif //IMPLEMENTATION_FACTORY_HPP
