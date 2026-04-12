// Treap (BST by key + heap by priority)
struct Treap {
    static int nextPriority() {
        static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        static uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
        return dist(rng);
    }

    struct Node {
        int key;
        int prior;
        int cnt;
        Node *l, *r;

        explicit Node(int k) : key(k), prior(nextPriority()), cnt(1), l(nullptr), r(nullptr) {}
    };

    using pNode = Node*;
    pNode root = nullptr;

    int cnt(pNode t) { return t ? t->cnt : 0; }

    void pull(pNode t) {
        if (!t) return;
        t->cnt = 1 + cnt(t->l) + cnt(t->r);
    }

    void split(pNode t, int key, pNode &l, pNode &r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (t->key <= key) {
            split(t->r, key, t->r, r);
            l = t;
        } else {
            split(t->l, key, l, t->l);
            r = t;
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

    bool contains(pNode t, int key) {
        while (t) {
            if (t->key == key) return true;
            if (key < t->key) t = t->l;
            else t = t->r;
        }
        return false;
    }

    void insert(int key) {
        if (contains(root, key)) return; // set behavior (no duplicates)
        pNode L, R;
        split(root, key, L, R);
        root = merge(merge(L, new Node(key)), R);
    }

    void erase(int key) {
        pNode A, B, C;
        split(root, key, A, C);
        split(A, key - 1, A, B); // B contains only key (if exists)
        // delete subtree B if needed for memory cleanup
        root = merge(A, C);
    }

    int order_of_key(int key) { // count of elements < key
        pNode t = root;
        int ans = 0;
        while (t) {
            if (key <= t->key) {
                t = t->l;
            } else {
                ans += 1 + cnt(t->l);
                t = t->r;
            }
        }
        return ans;
    }

    int find_by_order(int k) { // 0-indexed kth smallest
        pNode t = root;
        while (t) {
            int left = cnt(t->l);
            if (k < left) t = t->l;
            else if (k == left) return t->key;
            else {
                k -= left + 1;
                t = t->r;
            }
        }
        return -1; // invalid k
    }
};

// Example of use:
// Treap tr;
// tr.insert(10); tr.insert(4); tr.insert(20);
// int x = tr.find_by_order(1); // 10
// int y = tr.order_of_key(15); // 2
