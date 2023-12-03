#ifndef IMPLEMENTATION_REPORTS_HPP
#define IMPLEMENTATION_REPORTS_HPP

#include <set>

#include "types.hpp"

/**
 * Notifies about reports at specific turns.
 */
class SpecificTurnsReportNotifier{
public:
    SpecificTurnsReportNotifier(std::set<Time> turns): turns_(turns){}
    bool should_generate_report(Time t) { return turns_.find(t) != turns_.end(); };
private:
    std::set<Time> turns_;
};


/**
 * Notifies about reports every n turns.
 */
class IntervalReportNotifier{
public:
    IntervalReportNotifier(TimeOffset to): to_(to){}
    bool should_generate_report(Time t) { return t % to_ == 0; };
private:
    TimeOffset to_;
};

void generate_structure_report();

void generate_simulation_turn_report();

#endif //IMPLEMENTATION_REPORTS_HPP
