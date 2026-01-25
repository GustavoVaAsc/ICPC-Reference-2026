// Standard binary search (iterative)
int binary_search(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Lower bound (first element >= target)
int lower_bound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        arr[mid] < target ? left = mid + 1 
                            : right = mid;
    }
    return left;
}

// Upper bound (first element > target)
int upper_bound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        arr[mid] <= target ? left = mid + 1 
                            : right = mid;
    }
    return left;
}

// Binary search on real numbers (e.g. sqrt)
double sqrt_precision(double n, double eps=1e-6) {
    double left = 0, right = n;
    for (int i = 0; i < 100; ++i) { // or while (right-left > eps)
        double mid = (left + right) / 2;
        if (mid*mid < n) left = mid;
        else right = mid;
    }
    return left;
}

// Binary search on answer space (monotonic condition)
int find_min_valid(vector<int>& nums, int k) {
    auto is_valid = [&](int x) { 
        /* condition check */ 
    };
    
    int left = 0, right = 1e9; // adjust bounds
    while (left < right) {
        int mid = left + (right - left) / 2;
        is_valid(mid) ? right = mid 
                        : left = mid + 1;
    }
    return left;
}

// Binary search using for loop

int binary_search_for_loop(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    for (; left <= right; ) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}