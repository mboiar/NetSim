#ifndef IMPLEMENTATION_SIMULATION_HPP
#define IMPLEMENTATION_SIMULATION_HPP

#include <functional>

#include "factory.hpp"
#include "types.hpp"

/**
 * Simulate a factory network.
 * @param f  simulated factory
 * @param d  number of turns in a simulation
 * @param rf report generation function
 */
void simulate(Factory& f, TimeOffset d, std::function<void(Factory&, Time)> rf);

#endif //IMPLEMENTATION_SIMULATION_HPP