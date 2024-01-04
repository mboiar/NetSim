#include <string>
#include <iostream>
#include <sstream>
#include "reports.hpp"

void generate_structure_report(const Factory& factory, std::ostream& os){
    // RAMPS ----------------
    os << "\n== LOADING RAMPS ==\n\n";

    std::vector<ElementID> ramps_id;

    for (auto i = factory.ramp_cbegin(); i != factory.ramp_cend(); i++)
        ramps_id.push_back((*i).get_id());

    std::sort(ramps_id.begin(), ramps_id.end());

    for(unsigned int ramp_i : ramps_id){
        auto i = factory.find_ramp_by_id(ramp_i);

        os << "LOADING RAMP #" << i->get_id() << "\n";
        os << "  Delivery interval: " << i->get_delivery_interval() << "\n";
        os << "  Receivers:\n";

        std::vector<ElementID> receivers_workers;

        for(auto receiver_preference : (*i).receiver_preferences_)
            receivers_workers.push_back(receiver_preference.first->get_id());

        std::sort(receivers_workers.begin(), receivers_workers.end());

        for(auto receiver_worker : receivers_workers)
            os << "    worker #" << receiver_worker << "\n";

        os << "\n";
    }

    ramps_id.clear();

    // WORKERS ----------------

    os << "\n== WORKERS ==\n\n";

    std::vector<ElementID> workers_id;

    for (auto i = factory.worker_cbegin(); i != factory.worker_cend(); i++)
        workers_id.push_back((*i).get_id());

    std::sort(workers_id.begin(), workers_id.end());

    for(unsigned int worker_i : workers_id){
        auto i = factory.find_worker_by_id(worker_i);

        std::string queue_type = (*i).get_queue()->get_queue_type() == PackageQueueType::FIFO ? "FIFO" : "LIFO";

        os << "WORKER #" << (*i).get_id() << "\n";
        os << "  Processing time: " << (*i).get_processing_duration() << "\n";
        os << "  Queue type: " << queue_type << "\n";
        os << "  Receivers:\n";

        std::vector<ElementID> receivers_workers;
        std::vector<ElementID> receivers_storehouses;

        for(auto receiver_preference : (*i).receiver_preferences_){
            ReceiverType type = receiver_preference.first->get_receiver_type();

            if(type == ReceiverType::Worker)
                receivers_workers.push_back(receiver_preference.first->get_id());
            else
                receivers_storehouses.push_back(receiver_preference.first->get_id());
        }

        std::sort(receivers_workers.begin(), receivers_workers.end());
        std::sort(receivers_storehouses.begin(), receivers_storehouses.end());

        for(auto receiver_storehouse : receivers_storehouses)
            os << "    storehouse #" << receiver_storehouse << "\n";

        for(auto receiver_worker : receivers_workers)
            os << "    worker #" << receiver_worker << "\n";

        os << "\n";
    }

    workers_id.clear();

    // STOREHOUSES ---------------

    os << "\n== STOREHOUSES ==\n";

    std::vector<ElementID> storehouses_id;

    for (auto i = factory.storehouse_cbegin(); i != factory.storehouse_cend(); i++)
        storehouses_id.push_back((*i).get_id());

    std::sort(storehouses_id.begin(), storehouses_id.end());

    for(unsigned int storehouse_i : storehouses_id){
        auto i = factory.find_storehouse_by_id(storehouse_i);
        os << "\n" << "STOREHOUSE #" << (*i).get_id() << "\n";
    }
    os << "\n";

    storehouses_id.clear();
}

void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time t){
    os << "=== [ Turn: " << t <<" ] ===\n";

    os << "\n== WORKERS ==\n";
    for(auto i = factory.worker_cbegin(); i != factory.worker_cend(); i++){
        os << "\nWORKER #" << (*i).get_id() << "\n";

        // PBuffer - D
        if(!(*i).get_processing_buffer().has_value())
            os << "  PBuffer: (empty)\n";
        else
            os << "  PBuffer: #" << (*i).get_processing_buffer()->get_id() << " (pt = " << (*i).get_package_processing_start_time() << ")\n";

        // Queue - U
        if((*i).get_queue()->cbegin() == (*i).get_queue()->cend())
            os << "  Queue: (empty)\n";
        else{
            os << "  Queue: #" << (*i).get_queue()->cbegin()->get_id();
            for(auto queue_i = ++((*i).get_queue()->cbegin()); queue_i != (*i).get_queue()->end(); queue_i++){
                os << ", #" << queue_i->get_id();
            }
            os << "\n";
        }

        // SBuffer - P
        if(!(*i).get_sending_buffer().has_value())
            os << "  SBuffer: (empty)\n";
        else
            os << "  SBuffer: #" << (*i).get_sending_buffer()->get_id() << "\n";
    }

    // Storehouse - A
    os << "\n\n== STOREHOUSES ==\n\n";
    for(auto i = factory.storehouse_cbegin(); i != factory.storehouse_cend(); i++){
        os << "STOREHOUSE #" << (*i).get_id() << "\n";

        if((*i).cbegin() == (*i).cend())
            os << "  Stock: (empty)\n\n";
        else{
            os << "  Stock: #" << (*i).cbegin()->get_id();
            for(auto stock_i = ++((*i).cbegin()); stock_i != (*i).cend(); stock_i++){
                os << ", #" << stock_i->get_id();
            }
            os << "\n\n";
        }
    }
}