#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

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

struct BusesForStopResponse {
  string reply;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  os << r.reply;
  return os;
}

struct StopsForBusResponse {
  string reply;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  os << r.reply;
  return os;
}

struct AllBusesResponse {
  string reply;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  os << r.reply;
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const auto& stop : buses_to_stops[bus]) {
    	stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
    	return {"No stop"};
    }
    BusesForStopResponse result;
    for (const auto& bus : stops_to_buses.at(stop)) {
    	result.reply += (bus + ' ');
    }
    return result;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
	  if (buses_to_stops.count(bus) == 0) {
		  return {"No bus"};
	  }
	  StopsForBusResponse result;
	  for (const auto& stop : buses_to_stops.at(bus)) {
		  result.reply += "Stop " + stop + ": ";
		  if (stops_to_buses.at(stop).size() == 1) {
			  result.reply += "no interchange";
		  } else {
			  for (const auto& other_bus : stops_to_buses.at(stop)) {
				  if (bus != other_bus) {
					  result.reply += (other_bus + ' ');
				  }
			  }
		  }
		  result.reply += '\n';
	  }
	  return result;
  }

  AllBusesResponse GetAllBuses() const {
	  if (buses_to_stops.empty()) {
		  return {"No buses"};
	  }
	  AllBusesResponse result;
	  for (const auto& bus_item : buses_to_stops) {
		  result.reply += "Bus " + bus_item.first + ": ";
		  for (const auto& stop : bus_item.second) {
			  result.reply += (stop + ' ');
		  }
		  result.reply += '\n';
	  }
	  return result;
  }
private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
