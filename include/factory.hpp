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
    void remove_by_id(ElementID id);
    NodeCollection<Node>::iterator find_by_id(ElementID id);
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const;
private:
    std::list<Node> nodes_list_;
};

class Factory{
public:
    void add_ramp(Ramp&& ramp);

    bool is_consistent();
    void do_deliveries(Time time);
    void do_package_passing();
    void do_work(Time time);
private:
    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> storehouses_;
    template <class Node>
    void remove_receiver(NodeCollection<Node> collection, ElementID id);
};

// zapis i odczyt

#endif //IMPLEMENTATION_FACTORY_HPP
