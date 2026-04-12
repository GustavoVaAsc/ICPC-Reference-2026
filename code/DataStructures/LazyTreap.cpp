// Lazy Implicit Treap (range add, range sum, range reverse)
struct LazyTreap {
    static int nextPriority() {
        static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        static uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
        return dist(rng);
    }

    struct Node {
        int val;
        int prior;
        int sz;
        long long sum;
        long long lazyAdd;
        bool rev;
        Node *l, *r;

        explicit Node(int v)
            : val(v), prior(nextPriority()), sz(1), sum(v), lazyAdd(0), rev(false), l(nullptr), r(nullptr) {}
    };

    using pNode = Node*;
    pNode root = nullptr;

    int sz(pNode t) { return t ? t->sz : 0; }
    long long sum(pNode t) { return t ? t->sum : 0; }

    void applyAdd(pNode t, long long add) {
        if (!t) return;
        t->val += add;
        t->sum += add * sz(t);
        t->lazyAdd += add;
    }

    void applyRev(pNode t) {
        if (!t) return;
        t->rev ^= 1;
        swap(t->l, t->r);
    }

    void push(pNode t) {
        if (!t) return;
        if (t->rev) {
            applyRev(t->l);
            applyRev(t->r);
            t->rev = false;
        }
        if (t->lazyAdd != 0) {
            applyAdd(t->l, t->lazyAdd);
            applyAdd(t->r, t->lazyAdd);
            t->lazyAdd = 0;
        }
    }

    void pull(pNode t) {
        if (!t) return;
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->sum = t->val + sum(t->l) + sum(t->r);
    }

    void split(pNode t, int leftSize, pNode &l, pNode &r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        push(t);
        int curLeft = sz(t->l);
        if (leftSize <= curLeft) {
            split(t->l, leftSize, l, t->l);
            r = t;
        } else {
            split(t->r, leftSize - curLeft - 1, t->r, r);
            l = t;
        }
        pull(t);
    }

    pNode merge(pNode l, pNode r) {
        if (!l || !r) return l ? l : r;
        if (l->prior > r->prior) {
            push(l);
            l->r = merge(l->r, r);
            pull(l);
            return l;
        }
        push(r);
        r->l = merge(l, r->l);
        pull(r);
        return r;
    }

    void insert(int pos, int val) {
        pNode L, R;
        split(root, pos, L, R);
        root = merge(merge(L, new Node(val)), R);
    }

    void rangeAdd(int l, int r, long long add) {
        pNode A, B, C;
        split(root, r + 1, B, C);
        split(B, l, A, B);
        applyAdd(B, add);
        root = merge(merge(A, B), C);
    }

    void rangeReverse(int l, int r) {
        pNode A, B, C;
        split(root, r + 1, B, C);
        split(B, l, A, B);
        applyRev(B);
        root = merge(merge(A, B), C);
    }

    long long rangeSum(int l, int r) {
        pNode A, B, C;
        split(root, r + 1, B, C);
        split(B, l, A, B);
        long long ans = sum(B);
        root = merge(merge(A, B), C);
        return ans;
    }
};

// Example of use:
// LazyTreap lt;
// lt.insert(0, 1); lt.insert(1, 2); lt.insert(2, 3); // [1,2,3]
// lt.rangeAdd(0, 1, 5); // [6,7,3]
// lt.rangeReverse(0, 2); // [3,7,6]
// long long s = lt.rangeSum(0, 2); // 16
