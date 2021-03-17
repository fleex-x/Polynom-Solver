#include <bits/stdc++.h>

using namespace std;

const double INF = 1e18, EPS = 1e-4;

double get_value(vector <double> & p, double x) {
	double res = 0, q = 1;
	for (auto k : p) {
		res += q * k;
		q *= x;
	}
	return res;
}

void add_root(vector <double> & ans, vector <double> & p, double l, double r, bool kek) {
	if (fabs(get_value(p, l)) < EPS) {
		if (ans.size() == 0 || fabs(ans.back() - l) > EPS) {
			ans.push_back(l);
		}
		return;
	}
	if (fabs(get_value(p, r)) < EPS) {
		if (ans.size() == 0 || fabs(ans.back() - r) > EPS) {
			ans.push_back(r);
		}
		return;
	}
	if (get_value(p, l) < 0.0 && get_value(p, r) < 0.0) {
		return;
	}
	if (get_value(p, l) > 0.0 && get_value(p, r) > 0.0) {
		return;
	}
	if (kek) {
		for (int i = 0; i < 80; ++i) {
			double mid = (r + l) / 2.0;
			if (get_value(p, mid) < 0) {
				l = mid;
			} else {
				r = mid;
			}
		}
	} else {
		for (int i = 0; i < 80; ++i) {
			double mid = (r + l) / 2.0;
			if (get_value(p, mid) > 0) {
				l = mid;
			} else {
				r = mid;
			}
		}
	}
	if (ans.size() == 0 || fabs(ans.back() - l) > EPS) {
		ans.push_back(l);
	}
}

vector <double> get_roots(vector <double> p) {
	if (p.size() == 2) {
		vector <double> ans = {-p[0] / p[1]};
		return ans;
	}
	vector <double> fluxion(p.size() - 1);
	for (int i = 1; i < p.size(); ++i) {
		fluxion[i - 1] = p[i] * double(i);
	}
	vector <double> roots_of_fluxion = get_roots(fluxion);
	vector <double> ans;

	if (roots_of_fluxion.size() > 0) {
		double x1 = -INF, x2 = roots_of_fluxion[0];

		if (get_value(fluxion, (x1 + x2) / 2.0) > 0) {
			add_root(ans, p, x1, x2, 1);
		} else {
			add_root(ans, p, x1, x2, 0);
		}

		for (int i = 1; i < roots_of_fluxion.size(); ++i) {
			double x1 = roots_of_fluxion[i - 1], x2 = roots_of_fluxion[i];
			if (get_value(fluxion, (x1 + x2) / 2.0) > 0) {
				add_root(ans, p, x1, x2, 1);
			} else {
				add_root(ans, p, x1, x2, 0);
			}
		}

		x1 = roots_of_fluxion.back();
		x2 = INF;

		if (get_value(fluxion, (x1 + x2) / 2.0) > 0) {
			add_root(ans, p, x1, x2, 1);
		} else {
			add_root(ans, p, x1, x2, 0);
		}

	} else {
		double x1 = -INF, x2 = INF;

		if (get_value(fluxion, (x1 + x2) / 2.0) > 0) {
			add_root(ans, p, x1, x2, 1);
		} else {
			add_root(ans, p, x1, x2, 0);
		}
	}

	return ans;
}


void solve() {
	int n;
	cin >> n;
	if (n == 0) {
		cout << "YA NE BUDU ETO RESHAT";
		return;
	}
	vector <double> p(n + 1);
	bool is_zero = true;
	for (int i = 0; i < n + 1; ++i) {
		cin >> p[i];
		if (i != n && p[i] != 0.0) {
			is_zero = false;
		}
	}
	if (is_zero) {
		cout << "YA NE BUDU ETO RESHAT";
		return;
	}
	reverse(p.begin(), p.end());
	vector <double> ans;
	ans = get_roots(p);
	for (auto x : ans) {
		cout << x << endl;
	}
}

signed main () {
	freopen ("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cout.precision(6);
	solve();
	return 0;
}