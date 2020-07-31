//https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/B

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

int mod;

struct Matrix2D {
    int a, b;
    int c, d;
};

Matrix2D matrix_prod(Matrix2D lhs, Matrix2D rhs) {
    Matrix2D res;
    res.a = ((lhs.a * rhs.a) % mod + (lhs.b * rhs.c) % mod) % mod;
    res.b = ((lhs.a * rhs.b) % mod + (lhs.b * rhs.d) % mod) % mod;
    res.c = ((lhs.c * rhs.a) % mod + (lhs.d * rhs.c) % mod) % mod;
    res.d = ((lhs.c * rhs.b) % mod + (lhs.d * rhs.d) % mod) % mod;

    return res;
}

istream& operator>>(istream& is, Matrix2D& m) {
    is >> m.a >> m.b >> m.c >> m.d;
    return is;
}

ostream& operator<<(ostream& os, const Matrix2D& m) {
    os << m.a << " " << m.b << "\n" << m.c << " " << m.d << "\n";
    return os;
}

class SegmentTree {
public:
    SegmentTree(size_t size) : _size(size) {
        tree.resize(size * 4);
    }

    SegmentTree(size_t size, Matrix2D value) : _size(size) {
        tree.resize(size * 4, value);
    }

    SegmentTree(const vector<Matrix2D>& data) : _size(data.size()) {
        tree.resize(data.size() * 4);
        build(data, 0, 0, data.size());
    }

    void update(int idx, Matrix2D value) {
        _update(0, 0, _size, idx, value);
    }

    Matrix2D prod(int l, int r) {
        return _prod(0, 0, _size, l, r);
    }

private:
    void _update(int v, int tl, int tr, int pos, Matrix2D new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;

            if (pos <= tm) {
                _update(v * 2 + 1, tl, tm, pos, new_val);
            } else {
                _update(v * 2 + 2, tm + 1, tr, pos, new_val);
            }

            tree[v] = matrix_prod(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    Matrix2D _prod(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return { 1, 0, 0, 1 };
        } else if (tl == l && tr == r) {
            return tree[v];
        } else {
            int tm = (tl + tr) / 2;

            return matrix_prod(_prod(v * 2 + 1, tl, tm, l, min(r, tm)), _prod(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r));
        }
    }

    void build(const vector<Matrix2D>& data, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = data[tl];
        } else {
            int tm = (tl + tr) / 2;

            build(data, v * 2 + 1, tl, tm);
            build(data, v * 2 + 2, tm + 1, tr);

            tree[v] = matrix_prod(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    vector<Matrix2D> tree;
    int _size;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> mod >> n >> m;

    vector<Matrix2D> data(n);
    for (auto& item : data) {
        cin >> item;
    }

    SegmentTree tree(data);

    for (size_t i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        cout << tree.prod(l, r) << "\n";
    }

    return 0;
}
