//https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/E

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

    T get(int pos) {
        return _get(0, 0, _size, pos);
    }

    void add(int pos, T val) {
        T curr_val = get(pos);
        update(pos, val + curr_val);
    }

private:
    T _get(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            return tree[v];
        } else {
            int tm = (tl + tr) / 2;

            if (pos <= tm) {
                return _get(v * 2 + 1, tl, tm, pos);
            } else {
                return _get(v * 2 + 2, tm + 1, tr, pos);
            }
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
    vector<long long> data(n, 0);

    SegmentTree<long long> tree(data);

    vector<long long> pref = data;
    for (int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }

    for (int i = 0; i < m; i++) {
        int q_type;
        cin >> q_type;

        if (q_type == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            tree.add(l, v);
            if (r < n) {
                tree.add(r, -v);
            }
        } else {
            int pos;
            cin >> pos;
            cout << tree.sum(0, pos) - pref[pos] << "\n";
        }
    }


    return 0;
}
