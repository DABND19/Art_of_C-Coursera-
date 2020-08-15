#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
    set<string> dict;
public:
    int Learn(const vector<string>& words) {
        size_t prev_words_num = dict.size();
        for (const auto& item : words) {
            dict.insert(item);
        }
        return dict.size() - prev_words_num;
    }

    vector<string> KnownWords() {
        return {dict.begin(), dict.end()};
    }
};