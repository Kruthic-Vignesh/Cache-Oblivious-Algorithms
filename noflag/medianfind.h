#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll partition(vector<ll> a, ll l, ll r, ll k);

ll findMedian(ll a[], ll n)
{
	sort(a.begin(), a.end());
	return a[n/2]; // Return middle element
}

// Returns k'th smallest element in a[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN a[] ARE DISTINCT
ll kthSmallest(ll a[], ll l, ll r, ll k)
{
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		ll n = r-l+1; // Number of elements in a[l..r]

		// Divide a[] in groups of size 5, calculate median
		// of every group and store it in median[] array.
		ll i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
		for (i=0; i<n/5; i++)
			median[i] = findMedian(a+l+i*5, 5);
		if (i*5 < n) //For last group with less than 5 elements
		{
			median[i] = findMedian(a+l+i*5, n%5);
			i++;
		}

		// Find median of all medians using recursive call.
		// If median[] has only one element, then no need
		// of recursive call
		ll medOfMed = (i == 1)? median[i-1]:
								kthSmallest(median, 0, i-1, i/2);

		// Partition the array around a random element and
		// get position of pivot element in sorted array
		ll pos = partition(a, l, r, medOfMed);

		// If position is same as k
		if (pos-l == k-1)
			return a[pos];
		if (pos-l > k-1) // If position is more, recur for left
			return kthSmallest(a, l, pos-1, k);

		// Else recur for right subarray
		return kthSmallest(a, pos+1, r, k-pos+l-1);
	}

	// If k is more than number of elements in array
	return INT_MAX;
}

void swap(ll *a, ll *b)
{
	ll temp = *a;
	*a = *b;
	*b = temp;
}

// It searches for x in a[l..r], and partitions the array
// around x.
ll partition(ll a[], ll l, ll r, ll x)
{
	// Search for x in a[l..r] and move it to end
	ll i;
	for(ll i=l; i<r; i++)
	{
		if(a[i] == x)
			break;
	}
	swap(&a[i], &a[r]);

	// Standard partition algorithm
	i = l;
	for (ll j = l; j <= r - 1; j++)
	{
		if (a[j] <= x)
		{
			swap(&a[i], &a[j]);
			i++;
		}
	}
	swap(&a[i], &a[r]);
	return i;
}

// Driver program to test above methods
int main()
{
	ll a[] = {12, 3, 5, 7, 4, 19, 26};
	ll n = sizeof(a)/sizeof(a[0]), k = 3;
	cout << "K'th smallest element is "
		<< kthSmallest(a, 0, n-1, k);
	return 0;
}
