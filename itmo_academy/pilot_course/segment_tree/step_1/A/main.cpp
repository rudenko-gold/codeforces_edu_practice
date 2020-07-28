//https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A

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
        build(data, 0, 0, data.size());
    }

    void update(int idx, T value) {
        _update(0, 0, _size, idx, value);
    }

    T sum(int l, int r) {
        return _sum(0, 0, _size, l, r);
    }

private:
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

            tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
        }
    }

    T _sum(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;
        } else if (tl == l && tr == r) {
            return tree[v];
        } else {
            int tm = (tl + tr) / 2;

            return _sum(v * 2 + 1, tl, tm, l, min(r, tm)) + _sum(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
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
            int pos, new_val;
            cin >> pos >> new_val;

            tree.update(pos, new_val);
        } else if (op_type == 2) {
            int l, r;
            cin >> l >> r;

            cout << tree.sum(l, r - 1) << "\n";
        }
    }

    return 0;
}
