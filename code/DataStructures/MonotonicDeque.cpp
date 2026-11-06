// Sliding window min/max with monotonic deque, O(n). Window of size k.
#include <bits/stdc++.h>
using namespace std;
vector<int> slidingMin(const vector<int> &a, int k) { // for max: flip comparison
	deque<int> dq; vector<int> res;
	for (int i = 0; i < (int)a.size(); i++) {
		while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
		dq.push_back(i);
		if (dq.front() <= i - k) dq.pop_front();
		if (i >= k - 1) res.push_back(a[dq.front()]);
	}
	return res;
}
