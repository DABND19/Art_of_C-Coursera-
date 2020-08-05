#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  buses_to_stops[bus] = stops;
  for (const auto& stop : buses_to_stops[bus]) {
    stops_to_buses[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  if (stops_to_buses.count(stop) == 0) {
    return {"No stop"};
  }
  BusesForStopResponse result;
  for (const auto& bus : stops_to_buses.at(stop)) {
    result.reply += (bus + ' ');
  }
  return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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
