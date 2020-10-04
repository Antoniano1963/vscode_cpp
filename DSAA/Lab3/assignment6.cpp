#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(long long a[], long long b[])
{
	if (a[0] != b[0]) return a[0] > b[0];
	if (a[1] != b[1]) return a[1] > b[1];
}
int main() {
	int n;
	cin >> n;
	long long x1, x2;
	long long **array0 = new long long*[n];
	scanf("%ld %ld", &x1, &x2);
	long k, b;
	for (int i = 0; i < n; i++) {
		array0[i] = new long long[2];
		scanf("%ld %ld", &k, &b);
		array0[i][0] = k * x1 + b;
		array0[i][1] = k * x2 + b;
	}
	sort(array0, array0 + n, cmp);
	bool T = true;
    for (int i = 0; i < n - 1; i++)
    {
        if (array0[i][1] < array0[i + 1][1])
        {
            if (array0[i][0] != array0[i + 1][0])
            {
                T = false;
                cout << "YES" << endl;
                break;
            }
        }
    }
	if (T) {
		cout << "NO" << endl;
	}
}