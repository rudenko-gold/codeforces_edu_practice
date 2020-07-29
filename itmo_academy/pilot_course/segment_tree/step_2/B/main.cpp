//https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <deque>
#include <list>

using namespace std;

template <typename T>
class SegmentTree {
public:
    SegmentTree(size_t size) : _size(size) {
        tree.resize(size * 4);
    }

    SegmentTree(size_t size, T value) : _size(size) {
        tree.resize(size * 4, value);
    }

    SegmentTree(const vector<T>& data) : _size(data.size()) {
        tree.resize(data.size() * 4);
        build(data, 0, 0, data.size() - 1);
    }

    void update(int idx) {
        _update(0, 0, _size - 1, idx);
    }

    int find_kth(int k) {
        return _find_kth(0, 0, _size - 1, k);
    }

private:
    int _find_kth (int v, int tl, int tr, int k) {
        if (k > tree[v]) {
            return -1;
        }

        if (tl == tr) {
            return tl;
        }
        int tm = (tl + tr) / 2;

        if (tree[v * 2 + 1] > k) {
            return _find_kth(v * 2 + 1, tl, tm, k);
        } else {
            return _find_kth(v * 2 + 2, tm + 1, tr, k - tree[v * 2 + 1]);
        }
    }

    void _update(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            if (tree[v] == 0) {
                tree[v] = 1;
            } else {
                tree[v] = 0;
            }
        } else {
            int tm = (tl + tr) / 2;

            if (pos <= tm) {
                _update(v * 2 + 1, tl, tm, pos);
            } else {
                _update(v * 2 + 2, tm + 1, tr, pos);
            }

            tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
        }
    }

    void build(const vector<T>& data, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = data[tl];
        } else {
            int tm = (tl + tr) / 2;

            build(data, v * 2 + 1, tl, tm);
            build(data, v * 2 + 2, tm + 1, tr);

            tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
        }
    }

    vector<T> tree;
    int _size;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> data(n);
    for (auto& item : data) {
        cin >> item;
    }

    SegmentTree<long long> tree(data);

    for (size_t i = 0; i < m; ++i) {
        int op_type;
        cin >> op_type;

        if (op_type == 1) {
            int pos;
            cin >> pos;

            tree.update(pos);
        } else if (op_type == 2) {
            int k;
            cin >> k;

            cout << tree.find_kth(k) << "\n";
        }
    }

    return 0;
}
