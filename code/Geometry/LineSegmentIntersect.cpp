\begin{lstlisting}[style=compactcpp]
// BeginCodeSnip{Point Class}
struct Point {
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}

	friend istream &operator>>(istream &in, Point &p) {
		int x, y;
		in >> p.x >> p.y;
		return in;
	}
};
// EndCodeSnip

int sign(long long num) {
	if (num < 0) {
		return -1;
	} else if (num == 0) {
		return 0;
	} else {
		return 1;
	}
}

long long trigonometric_sense(Point p, Point p1, Point p2) {
	return sign(1LL * (p1.x - p.x) * (p2.y - p.y) -
	            1LL * (p2.x - p.x) * (p1.y - p.y));
}

// Check if the rectangles with [P1, P2] and [P3, P4] as diagonals intersect
bool quick_check(Point p1, Point p2, Point p3, Point p4) {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	x1 = min(p1.x, p2.x), x2 = max(p1.x, p2.x);
	y1 = min(p1.y, p2.y), y2 = max(p1.y, p2.y);
	x3 = min(p3.x, p4.x), x4 = max(p3.x, p4.x);
	y3 = min(p3.y, p4.y), y4 = max(p3.y, p4.y);
	return x2 < x3 || x4 < x1 || y2 < y3 || y4 < y1;
}

bool check(Point p1, Point p2, Point p3, Point p4) {
	if (trigonometric_sense(p1, p2, p3) * trigonometric_sense(p1, p2, p4) > 0) {
		return false;
	}
	if (trigonometric_sense(p3, p4, p1) * trigonometric_sense(p3, p4, p2) > 0) {
		return false;
	}
	return true;
}

int main() {
	int test_num;
	cin >> test_num;
	for (int t = 0; t < test_num; t++) {
		Point p1, p2, p3, p4;
		cin >> p1 >> p2 >> p3 >> p4;

		if (quick_check(p1, p2, p3, p4)) {
			cout<<"NO"<<endl;
		} else if (check(p1, p2, p3, p4)) {
			cout<<"YES"<<endl;
		} else {
			cout<<"NO"<<endl;
		}
	}
}