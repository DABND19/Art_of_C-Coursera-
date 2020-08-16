#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
#include "profile.h"

using namespace std;

const int ROOM_COUNT = 1000;
const int CLIENT_COUNT = 1'000'000'000;

const long int SECONDS_IN_DAY = 60 * 60 * 24;

struct Booking {
  long int time;
  string hotel_name;
  int client_id;
  int room_count;
};

class BookingManager {
public:
  BookingManager() {}
  void Book(long int time, const string& hotel_name,
            int client_id, int room_count) {
    current_time = max(current_time, time);

    ClearOldBookings();

    Booking new_booking = {time, hotel_name, client_id, room_count};
    bookings.push(new_booking);
    current_room_count[hotel_name] += room_count;
    current_clients[hotel_name][client_id]++;
  }
  //Число различных клиентов, бронировавших номера в отеле
  //за последние сутки. Текущим временем считать время последнего
  //бронирования. Причем current - 86400 < time <= current.
  int Clients(const string& hotel_name) const {
    if (current_clients.count(hotel_name) == 0) {
      return 0;
    }
    return current_clients.at(hotel_name).size();
  }
  //Количество номеров, забронированных в отеле за последние сутки
  int Rooms(const string& hotel_name) const {
    if (current_room_count.count(hotel_name) == 0) {
      return 0;
    }
    return current_room_count.at(hotel_name);
  }
private:
  long int current_time = 0;
  queue<Booking> bookings;
  map<string, int> current_room_count;
  map<string, map<int, int>> current_clients;

  bool IsActual(const Booking& booking) {
    return booking.time > current_time - SECONDS_IN_DAY &&
           booking.time <= current_time;
  }

  void ClearOldBookings() {
    Booking front = bookings.front();
    while (!bookings.empty() && !IsActual(front)) {
      current_room_count[front.hotel_name] -= front.room_count;
      current_clients[front.hotel_name][front.client_id]--;
      if (current_clients[front.hotel_name][front.client_id] == 0) {
        current_clients[front.hotel_name].erase(front.client_id);
      }
      bookings.pop();
      front = bookings.front();
    }
  }
};

int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BookingManager manager;

  int query_count;
  cin >> query_count;

  while (query_count > 0) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      long int time;
      string hotel_name;
      int client_id;
      int room_count;
      cin >> time >> hotel_name >> client_id >> room_count;
      {
        LOG_DURATION(query_type)
        manager.Book(time, hotel_name, client_id, room_count);
      }
    }
    else if (query_type == "CLIENTS") {
      string hotel_name;
      cin >> hotel_name;
      {
        LOG_DURATION(query_type)
        cout << manager.Clients(hotel_name) << endl;
      }
    }
    else if (query_type == "ROOMS") {
      string hotel_name;
      cin >> hotel_name;
      {
        LOG_DURATION(query_type)
        cout << manager.Rooms(hotel_name) << endl;
      }
    } else {
      continue;
    }
    query_count--;
  }

  return 0;
}
