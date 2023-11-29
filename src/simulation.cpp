#include <system_error>

#include "simulation.hpp"
#include "reports.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void(Factory&, Time)>){
    // TODO check graph
    if (false){
        throw std::logic_error("Niespójna sieć");
    }

    // Stage I: Delivery

    // Stage II: Transport

    // Stage III: Processing

    // Stage IV: Reporting

}
