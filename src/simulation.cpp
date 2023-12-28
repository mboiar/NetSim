#include <system_error>

#include "simulation.hpp"
#include "reports.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void(Factory&, Time)> rf){
    if (!f.is_consistent()){
        throw std::logic_error("Inconsistent graph");
    }

    Time sim_time = 0;

    while(sim_time < d){
        sim_time++;
        // Stage I: Delivery
        f.do_deliveries(sim_time);

        // Stage II: Transport
        f.do_package_passing();

        // Stage III: Processing
        f.do_work(sim_time);

        // Stage IV: Reporting
        rf(f, sim_time);
    }
}