// Date utilities: days since 1970-01-01 (proleptic Gregorian) and day of week. O(1).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll daysFromCivil(ll y, int m, int d) {
	y -= m <= 2;
	ll era = (y >= 0 ? y : y - 399) / 400, yoe = y - era * 400;
	ll doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1, doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
	return era * 146097 + doe - 719468;
}
void civilFromDays(ll z, ll &y, int &m, int &d) {
	z += 719468;
	ll era = (z >= 0 ? z : z - 146096) / 146097, doe = z - era * 146097;
	ll yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365, doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
	ll mp = (5 * doy + 2) / 153;
	d = doy - (153 * mp + 2) / 5 + 1; m = mp < 10 ? mp + 3 : mp - 9;
	y = yoe + era * 400 + (m <= 2);
}
int dayOfWeek(ll y, int m, int d) { return ((daysFromCivil(y, m, d) % 7) + 11) % 7; } // 0 = Sunday
bool leap(ll y) { return y % 4 == 0 && (y % 100 || y % 400 == 0); }
