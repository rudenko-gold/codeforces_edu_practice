//https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

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

    void update(int idx, T new_val) {
        _update(0, 0, _size - 1, idx, new_val);
    }

    int find_above(int x) {
        return _find_above(0, 0, _size - 1, x);
    }
private:
    int _find_above(int v, int tl, int tr, int x) {
        if (tl == tr) {
            if (tree[v] >= x) {
                return tl;
            } else {
                return -1;
            }
        }
        int tm = (tl + tr) / 2;

        if (tree[v * 2 + 1] >= x) {
            return _find_above(v * 2 + 1, tl, tm, x);
        } else {
            return _find_above(v * 2 + 2, tm + 1, tr, x);
        }
    }

    void _update(int v, int tl, int tr, int pos, T new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;

            if (pos <= tm) {
                _update(v * 2 + 1, tl, tm, pos, new_val);
            } else {
                _update(v * 2 + 2, tm + 1, tr, pos, new_val);
            }

            tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    void build(const vector<T>& data, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = data[tl];
        } else {
            int tm = (tl + tr) / 2;

            build(data, v * 2 + 1, tl, tm);
            build(data, v * 2 + 2, tm + 1, tr);

            tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
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
            int pos, new_val;
            cin >> pos >> new_val;

            tree.update(pos, new_val);
        } else if (op_type == 2) {
            int x;
            cin >> x;

            cout << tree.find_above(x) << "\n";
        }
    }

    return 0;
}
