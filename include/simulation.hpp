#ifndef IMPLEMENTATION_SIMULATION_HPP
#define IMPLEMENTATION_SIMULATION_HPP

#include <functional>

#include "factory.hpp"
#include "types.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void(Factory&, Time)>);

#endif //IMPLEMENTATION_SIMULATION_HPP
