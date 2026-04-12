// Implicit Treap (sequence by position)
struct ImplicitTreap {
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
        Node *l, *r;

        explicit Node(int v)
            : val(v), prior(nextPriority()), sz(1), sum(v), l(nullptr), r(nullptr) {}
    };

    using pNode = Node*;
    pNode root = nullptr;

    int sz(pNode t) { return t ? t->sz : 0; }
    long long sum(pNode t) { return t ? t->sum : 0; }

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
            l->r = merge(l->r, r);
            pull(l);
            return l;
        }
        r->l = merge(l, r->l);
        pull(r);
        return r;
    }

    void insert(int pos, int val) { // insert before pos
        pNode L, R;
        split(root, pos, L, R);
        root = merge(merge(L, new Node(val)), R);
    }

    void erase(int pos) {
        pNode A, B, C;
        split(root, pos, A, B);
        split(B, 1, B, C); // B is erased node
        root = merge(A, C);
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
// ImplicitTreap it;
// it.insert(0, 5); it.insert(1, 7); it.insert(1, 3); // [5,3,7]
// long long s = it.rangeSum(0, 2); // 15
