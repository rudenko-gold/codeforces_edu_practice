//https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A

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

    void update(int idx, T value) {
        _update(0, 0, _size - 1, idx, value);
    }

    T max_segment() {
        return tree[0].ans;
    }

private:
    void _update(int v, int tl, int tr, int pos, T new_val) {
        if (tl == tr) {
            tree[v] = make_segment(new_val);
        } else {
            int tm = (tl + tr) / 2;

            if (pos <= tm) {
                _update(v * 2 + 1, tl, tm, pos, new_val);
            } else {
                _update(v * 2 + 2, tm + 1, tr, pos, new_val);
            }

            tree[v] = combine(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    void build(const vector<T>& data, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = make_segment(data[tl]);
        } else {
            int tm = (tl + tr) / 2;

            build(data, v * 2 + 1, tl, tm);
            build(data, v * 2 + 2, tm + 1, tr);

            tree[v] = combine(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    struct Segment {
        long long sum, ans, pref, suff;
    };

    Segment make_segment(T val) {
        Segment res;

        res.sum = val;
        if (val < 0) {
            val = 0;
        }

        res.ans = res.pref = res.suff = val;

        return res;
    }

    Segment combine(Segment lhs, Segment rhs) {
        Segment res;

        res.sum = lhs.sum + rhs.sum;
        res.pref = max(lhs.pref, lhs.sum + rhs.pref);
        res.suff = max(rhs.suff, rhs.sum + lhs.suff);
        res.ans = max(max(lhs.ans, rhs.ans), lhs.suff + rhs.pref);

        return res;
    }

    vector<Segment> tree;
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
    cout << tree.max_segment() << "\n";
    for (size_t i = 0; i < m; ++i) {
        int pos, new_val;
        cin >> pos >> new_val;

        tree.update(pos, new_val);
        cout << tree.max_segment() << "\n";
    }

    return 0;
}
