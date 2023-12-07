#include "package.hpp"

std::set<ElementID> Package::assigned_IDs {0};
std::set<ElementID> Package::freed_IDs;

Package::Package(){
    ElementID new_id;

    if(!freed_IDs.empty()){
        new_id = *freed_IDs.begin();
        freed_IDs.erase(new_id);
    }
    else{
        new_id = *std::prev(assigned_IDs.end()) + 1;
    }

    assigned_IDs.insert(new_id);
    id = new_id;
}

Package::Package(ElementID el_id) {
    id = el_id;
    assigned_IDs.insert(el_id);
}

ElementID Package::get_id() const {
    return id;
}

Package::~Package() {
    assigned_IDs.erase(id);
    freed_IDs.insert(id);
}


