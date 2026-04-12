struct Node {
	int val;
	Node *l, *r;

	Node(ll x) : val(x), l(nullptr), r(nullptr) {}
	Node(Node *ll, Node *rr) : val(0), l(ll), r(rr) {}
};

int n, a[100001];     // The initial array and its size
Node *roots[100001];  // The persistent array's roots

Node *build(int l = 0, int r = n - 1) {
	if (l == r) return new Node(a[l]);
	int mid = (l + r) / 2;
	return new Node(build(l, mid), build(mid + 1, r));
}

Node *update(Node *node, int val, int pos, int l = 0, int r = n - 1) {
	if (l == r) return new Node(val);
	int mid = (l + r) / 2;
	if (pos > mid) return new Node(node->l, update(node->r, val, pos, mid + 1, r));
	else return new Node(update(node->l, val, pos, l, mid), node->r);
}

int query(Node *node, int pos, int l = 0, int r = n - 1) {
	if (l == r) return node->val;
	int mid = (l + r) / 2;
	if (pos > mid) return query(node->r, pos, mid + 1, r);
	return query(node->l, pos, l, mid);
}

int get_item(int index, int time) {
	// Gets the array item at a given index and time
	return query(roots[time], index);
}

void update_item(int index, int value, int prev_time, int curr_time) {
	// Updates the array item at a given index and time
	roots[curr_time] = update(roots[prev_time], index, value);
}

void init_arr(int nn, int *init) {
	// Initializes the persistent array, given an input array
	n = nn;
	for (int i = 0; i < n; i++) a[i] = init[i];
	roots[0] = build();
}