#ifndef IMPLEMENTATION_REPORTS_HPP
#define IMPLEMENTATION_REPORTS_HPP

#include <set>

#include "types.hpp"

class SpecificTurnsReportNotifier{
public:
    SpecificTurnsReportNotifier(std::set<Time> turns): turns_(turns){}
    bool should_generate_report(Time t);
private:
    std::set<Time> turns_;
};

class IntervalReportNotifier{
public:
    IntervalReportNotifier(TimeOffset to): to_(to){}
    bool should_generate_report(Time t);
private:
    TimeOffset to_;
};

void generate_structure_report();

void generate_simulation_turn_report();

#endif //IMPLEMENTATION_REPORTS_HPP
