#include <bits/stdc++.h>
using namespace std;
typedef int long long;
class MRUCache {
public:
    int capacity;
    unordered_map<int, pair<int, list<int>::iterator>> cache;
    list<int> mruList;
    MRUCache(int cap) : capacity(cap) {}
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            update(key);
            return cache[key].first;
        }
        return -1;
    }
    void set(int key, int value) {
        if (cache.size() >= capacity) {
            remove();
        }
        cache[key] = {value, mruList.insert(mruList.begin(), key)};
    }
private:
    void update(int key) {
        mruList.erase(cache[key].second);
        cache[key].second = mruList.insert(mruList.begin(), key);
    }
    void remove() {
        int mruKey = mruList.back();
        mruList.pop_back();
        cache.erase(mruKey);
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int cap, Q;
        cin >> cap >> Q;
        MRUCache cache(cap);
        vector<int> output;
        for (int i = 0; i < Q; ++i) {
            char queryType;
            cin >> queryType;
            if (queryType == 'S') {
                int key, value;
                cin >> key >> value;
                cache.set(key, value);
            } else if (queryType == 'G') {
                int key;
                cin >> key;
                output.push_back(cache.get(key));
            }
        }
        for (int val : output) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}