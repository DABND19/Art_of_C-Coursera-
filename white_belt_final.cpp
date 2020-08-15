#include <iostream>
#include <iomanip>
#include <tuple>
#include <set>
#include <map>
#include <stdexcept>

using namespace std;

class Date {
public:
    Date() {}
    Date(int new_year, int new_month, int new_day) {
        year = new_year;
        if (new_month < 1 || new_month > 12) {
            throw out_of_range("Month value is invalid: "
                               + to_string(new_month));
        }
        month = new_month;
        if (new_day < 1 || new_day > 31) {
            throw out_of_range("Day value is invalid: "
                               + to_string(new_day));
        }
        day = new_day;
    }
    Date(const string& date) {
        int new_year, new_month, new_day;
        bool ok = true;
        istringstream date_stream(date);

        ok = ok && (date_stream >> new_year);
        ok = ok && (date_stream.peek() == '-');
        date_stream.ignore(1);

        ok = ok && (date_stream >> new_month);
        ok = ok && (date_stream.peek() == '-');
        date_stream.ignore(1);

        ok = ok && (date_stream >> new_day);
        ok = ok && date_stream.eof();

        if (!ok) {
            throw out_of_range("Wrong date format: " + date);
        }
        *this = Date(new_year, new_month, new_day);
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
private:
    int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
           make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

istream& operator>>(istream& is, Date& d) {
    string date;
    is >> date;
    d = Date(date);
    return is;
}

ostream& operator<<(ostream& os, const Date& d) {
    os << setfill('0');
    os << setw(4) << d.GetYear() << '-';
    os << setw(2) << d.GetMonth() << '-';
    os << setw(2) << d.GetDay();
    return os;
}

class Database {
public:
    Database() {}
    void AddEvent(const Date& date, const string& event) {
        event_list[date].insert(event);
    }
    string DeleteEvent(const Date& date, const string& event) {
        if (event_list[date].find(event) != event_list[date].end()) {
            event_list[date].erase(event);
            return "Deleted successfully";
        } else {
            return "Event not found";
        }
    }
    string DeleteDate(const Date& date) {
        size_t event_num = event_list[date].size();
        event_list[date].clear();
        return "Deleted " + to_string(event_num) + " events";
    }
    set<string> Find(const Date& date) const {
        if (event_list.find(date) != event_list.end()) {
            return event_list.at(date);
        }
        set<string> result;
        return result;

    }
    void Print() const {
        for (const auto& item : event_list) {
            if (item.second.size() != 0) {
                for (const auto& event : item.second) {
                    cout << item.first << " " << event << endl;
                }
            }
        }
    }
private:
    map<Date, set<string>> event_list;
};

ostream& operator<<(ostream& os, const set<string>& event_list) {
    for (const auto& event : event_list) {
        cout << event << endl;
    }
    return os;
}

int main() {
    Database db;
    Date date;
    string event;
    string command;
    while (getline(cin, command)) {
        try {
            string request;
            stringstream cmd(command);
            cmd >> request;
            if (request == "Add") {
                cmd >> date >> event;
                db.AddEvent(date, event);
            }
            else if (request == "Del") {
                cmd >> date;
                if (cmd.peek() == ' ') {
                    cmd >> event;
                    cout << db.DeleteEvent(date, event) << endl;
                } else {
                    cout << db.DeleteDate(date) << endl;
                }
            }
            else if (request == "Find") {
                cmd >> date;
                cout << db.Find(date);
            }
            else if (request == "Print") {
                db.Print();
            } else if (!request.empty()) {
                cout << "Unknown command: " << request << endl;
                return 1;
            }
        } catch (const exception& ex) {
            cout << ex.what() << endl;
            return 1;
        }
    }

    return 0;
}