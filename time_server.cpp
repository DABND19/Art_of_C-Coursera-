#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stdexcept>

using namespace std;

class TimeServer {
public:
	string GetCurrentTime();
private:
	string last_fetched_time = "00:00:00";
};

string TimeServer::GetCurrentTime() {
	try {
		last_fetched_time = AskTimeServer();

	} catch (const system_error&) { }
	return last_fetched_time;
}
