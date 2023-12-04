#ifndef IMPLEMENTATION_PACKAGE_HPP
#define IMPLEMENTATION_PACKAGE_HPP
#include <vector>
#include <numeric>
#include <ostream>
#include <set>

#include "types.hpp"

class Package{
public:
    Package();

    explicit Package(ElementID);

    Package(Package&&) noexcept = default;

    Package& operator=(Package&&) = default;

    ElementID get_id() const;

    ~Package();

private:
    ElementID id;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //IMPLEMENTATION_PACKAGE_HPP
