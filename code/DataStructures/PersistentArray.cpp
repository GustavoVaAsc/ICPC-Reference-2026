vector<pair<int, int>> arr[100001];  // The persistent array

int get_item(int index, int time) {
	// Gets the array item at a given index and time
	auto ub =
	    upper_bound(arr[index].begin(), arr[index].end(), make_pair(time, INT_MAX));
	return prev(ub)->second;
}

void update_item(int index, int value, int time) {
	// Updates the array item at a given index and time
	// Note that this only works if the time is later than all previous
	// update times
	assert(arr[index].back().first < time);
	arr[index].push_back({time, value});
}

void init_arr(int n, int *init) {
	// Initializes the persistent array, given an input array
	for (int i = 0; i < n; i++) arr[i].push_back({0, init[i]});
}