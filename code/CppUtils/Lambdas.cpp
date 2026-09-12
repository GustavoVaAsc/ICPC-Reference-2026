sort(v.begin(), v.end(), [](const Point& a, const Point& b) {
    return a.x < b.x;
});

auto cmp = [](const auto& a, const auto& b) { return a.x < b.x; };
sort(v.begin(), v.end(), cmp);

auto it = lower_bound(v.begin(), v.end(), target, [](const Point& a, const Point& b) {
    return a.x < b.x;
});

partition(v.begin(), v.end(), [](const Point& p) { return p.x < 3; });
int cnt = count_if(v.begin(), v.end(), [](const Point& p) { return p.x == 1; });

auto mn = min_element(v.begin(), v.end(), [](const Point& a, const Point& b) {
    return a.x + a.y < b.x + b.y;
});
auto it2 = find_if(v.begin(), v.end(), [](const Point& p) { return p.x == 3; });

for_each(v.begin(), v.end(), [](const Point& p) {
    cout << p.x << "," << p.y << "\n";
});