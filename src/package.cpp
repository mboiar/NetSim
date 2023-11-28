#include "package.hpp"
#include "types.hpp"

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
