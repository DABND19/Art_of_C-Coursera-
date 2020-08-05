#include "query.h"

istream& operator >> (istream& is, Query& q) {
  q.stops.clear();
  q.stop.erase();
  string command;
  is >> command;
  if (command == "NEW_BUS") {
    size_t stop_count;
    q.type = QueryType::NewBus;
    is >> q.bus >> stop_count;
    for (size_t i = 0; i < stop_count; i++) {
      is >> q.stop;
      q.stops.push_back(q.stop);
    }
  }
  else if (command == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  }
  else if (command == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  }
  else if (command == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  else {
    throw runtime_error("Bad command");
  }
  return is;
}


