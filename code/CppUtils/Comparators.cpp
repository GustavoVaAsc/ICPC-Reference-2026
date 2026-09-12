bool operator<(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

struct CompareX {
    bool operator()(const Point& a, const Point& b) const {
        return a.x < b.x;
    }
};

struct Descending {
    bool operator()(const int& a, const int& b) const { return a > b; }
};
