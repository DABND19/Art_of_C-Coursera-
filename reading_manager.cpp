#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

const size_t MAX_PAGES_COUNT = 1000;

class ReadingManager {
public:
    ReadingManager() : pages_statistics(MAX_PAGES_COUNT + 1, 0)
    {}
    void Read (int id, int pages) {
        int prev_pages = user_statistics[id];
        user_statistics[id] = pages;
        if (prev_pages != 0) {
            pages_statistics[prev_pages]--;
        }
        pages_statistics[pages]++;
    }

    double Cheer(int id) const {
        if (user_statistics.find(id) == user_statistics.end()) {
            return 0;
        }
        if (user_statistics.at(id) == 0) {
            return 0;
        }
        const size_t users_count = user_statistics.size();
        if (users_count == 1) {
            return 1;
        }
        const int pages = user_statistics.at(id);
        double result = 0;
        for (size_t i = 1; i < pages; i++) {
            result += pages_statistics[i];
        }
        result /= 1.0 * (users_count - 1);
        return result;
    }
private:
    map<int, int> user_statistics;
    vector<int> pages_statistics;
};

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
