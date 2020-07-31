//https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/D

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

class Set {
public:
    Set() {}

    Set(int val) {
        data[val] = 1;
        size = 1;
    }

    void insert(int val) {
        if (data[val] == 0) {
            size++;
        }

        data[val] = 1;
    }

    bool contain(int val) {
        return data[val];
    }

    int size = 0;
    bool data[41] = {};
};

Set make_union(Set lhs, Set rhs) {
    if(lhs.size > rhs.size) {
        for (size_t i = 1; i < 41; i++) {
            if (rhs.contain(i))
                lhs.insert(i);
        }
        return lhs;
    } else {
        for (size_t i = 1; i < 41; i++) {
            if (lhs.contain(i))
                rhs.insert(i);
        }
        return rhs;
    }
}

class SegmentTree {
public:
    SegmentTree(size_t size) : _size(size) {
        tree.resize(size * 4);
    }

    SegmentTree(const vector<int>& data) : _size(data.size()) {
        tree.resize(data.size() * 4);
        build(data, 0, 0, data.size() - 1);
    }

    void update(int idx, int value) {
        _update(0, 0, _size - 1, idx, value);
    }

    int unique(int l, int r) {
        return _unique(0, 0, _size - 1, l, r).size;
    }

private:
    void _update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = Set(new_val);
        } else {
            int tm = (tl + tr) / 2;

            if (pos <= tm) {
                _update(v * 2 + 1, tl, tm, pos, new_val);
            } else {
                _update(v * 2 + 2, tm + 1, tr, pos, new_val);
            }

            tree[v] = make_union(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    Set _unique(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return Set();
        } else if (tl == l && tr == r) {
            return tree[v];
        } else {
            int tm = (tl + tr) / 2;

            return make_union(_unique(v * 2 + 1, tl, tm, l, min(r, tm)), _unique(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r));
        }
    }

    void build(const vector<int>& data, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = Set(data[tl]);
        } else {
            int tm = (tl + tr) / 2;

            build(data, v * 2 + 1, tl, tm);
            build(data, v * 2 + 2, tm + 1, tr);

            tree[v] = make_union(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    vector<Set> tree;
    int _size;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> data(n);
    for (auto& item : data) {
        cin >> item;
    }

    SegmentTree tree(data);

    for (size_t i = 0; i < m; ++i) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << tree.unique(l, r) << "\n";
        } else {
            int x, pos;
            cin >> pos >> x;
            pos--;
            tree.update(pos, x);
        }
    }

    return 0;
}
