sort(all(a));

auto compression = [&](int x) {
    return (int)(lower_bound(all(a), x) - a.begin());
};