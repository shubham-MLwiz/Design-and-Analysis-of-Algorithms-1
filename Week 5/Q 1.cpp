#include <iostream>
#include <map>

using namespace std;

#define N_TARGET_SUMS	9	

map<int, bool> m;

int target_sums[] = {231552,234756,596873,648219,726312,981237,988331,1277361,1283379};

bool sum_exists(int N)
{
	for (map<int, bool>::iterator it = m.begin(); it != m.end(); it++)
		if (m.find(N - (*it).first) != m.end())
			return true;
	return false;
}

int main()
{
	int	n;

	while (cin >> n)
		m[n] = true;
	for (int i = 0; i < N_TARGET_SUMS; i++)
		if (sum_exists(target_sums[i]))
			cout << 1;
		else
			cout << 0;
	cout << endl;
	system("pause");
	return 0;
}
