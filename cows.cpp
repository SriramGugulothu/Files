// C++ code to implement the approach

#include <bits/stdc++.h>
using namespace std;

// Function to check if it is possible
// to position the cow x distance apart
bool ok(vector<int>& v, int x, int c)
{
	int n = v.size();

	// We already place it at the first
	// available slot i.e v[0](Greedy)
	int count = 1;
	int last = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] - v[last] >= x) {
			last = i; //cow placed
			count++;
		}
		if (count >= c) {
			return true;
		}
	}
	return false;
}

// Function to find the maximum possible
// minimum distance between the cows
int aggressive_cows(vector<int>& v, int n, int k)
{
	// Just take l = 1 and high = M (MAX DIFF POSSIBLE)
	// M = last - first element in sorted array
	int l = 0;
	int r = v[n-1] - v[0];
	int ans = -1;

	// Applying Binary search
	while (l<=r) {
		int mid = l + (r - l) / 2;
		if (ok(v, mid, k)) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}

	return ans;
}

// Driver code
int main()
{
	int K = 3;
	vector<int> arr = { 1, 2, 4, 8, 9 };
	int N = arr.size();

	// Function call
	int ans = aggressive_cows(arr, N, K);
	cout << ans << endl;

	return 0;
}

//Code contributed by Balakrishnan R (rbkraj000)
