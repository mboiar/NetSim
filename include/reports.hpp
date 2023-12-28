#ifndef IMPLEMENTATION_REPORTS_HPP
#define IMPLEMENTATION_REPORTS_HPP
#include "factory.hpp"

class SpecificTurnsReportNotifier{};

class IntervalReportNotifier{};

void generate_structure_report(const Factory& factory, std::ostream& os);

void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time t);

#endif //IMPLEMENTATION_REPORTS_HPP
