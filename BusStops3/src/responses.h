#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

struct BusesForStopResponse {
  string reply;
};

struct StopsForBusResponse {
  string reply;
};

struct AllBusesResponse {
  string reply;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);
