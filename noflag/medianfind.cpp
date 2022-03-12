#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll gr(ll r)
{
   uniform_int_distribution<ll> uid(0,r-1);
   ll val = uid(rng);
   return val+1;
}

ll glr(ll l, ll r)
{
    ll dif = r-l+1;
    ll x = gr(dif) + l-1;
    return x;
}

vector<pair<ll, ll>> a;

ll partition(ll l, ll r, pair<ll, ll> k);

pair<ll, ll> kthSmallest(vector<pair<ll, ll>> aa, ll l, ll r, ll k)
{
	ll n = r-l+1;
	ll i = 0;
	vector<pair<ll, ll>> median((n+4)/5); 
	for(; i < n/5; i++)
	{
		vector<pair<ll, ll>> s;
		for(int j = l+i*5; j < l+i*5+5; j++) s.push_back(aa[j]);
		sort(s.begin(), s.end());
		median[i] = s[2];
	}
	if (i*5 < n) 
	{
		vector<pair<ll, ll>> s;
		for(int j = l+i*5; j < l+i*5+n%5; j++) s.push_back(aa[j]);
		sort(s.begin(), s.end());
		median[i] = s[(n%5)/2];
		i++;
	}
	pair<ll, ll> medOfMed;
	if(i == 1) medOfMed = median[i-1];
	else medOfMed = kthSmallest(median, 0, i-1, i/2);

	ll pos = partition(a, l, r, medOfMed);

	if (pos-l == k-1)
		return a[pos];
	if (pos-l > k-1)
		return kthSmallest(a, l, pos-1, k);
	return kthSmallest(a, pos+1, r, k-pos+l-1);
}

void swap(pair<ll, ll> *aa, pair<ll, ll> *bb)
{
	pair<ll, ll> temp = *aa;
	*aa = *bb;
	*bb = temp;
}

ll partition(vector<pair<ll, ll>> &a, ll l, ll r, pair<ll, ll> x)
{
	ll i;
	for(i = l; i < r; i++)
	{
		if(a[i] == x)
			break;
	}
	swap(&a[i], &a[r]);
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

ll median(vector<ll> a)
{
	int n = a.size();
	vector<pair<ll, ll>> b(n);
	for(int i = 0; i < n; i++) b[i] = {a[i], i};
	pair<ll, ll> med = kthSmallest(b, 0, n-1, (n+1)/2);
	return med.first;
}

ll chh(vector<ll> a)
{
	sort(a.begin(), a.end());
	int n = a.size();
	return a[(n-1)/2];
}

// Driver program to test above methods
int main()
{
	int n = 5e5+7;
	vector<ll> a(n);
	for(int i = 0; i < n; i++)
	{
		a[i] = gr(1e9+7);
	}
	// for(int i = 0; i < n; i++) cin>>a[i];
	double time_spent = 0;
	clock_t begin = clock();
	
	ll med1 = median(a);
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	double time_spent2 = 0;
	clock_t begin2 = clock();
	
	ll med2 = chh(a);
	clock_t end2 = clock();
	time_spent2 += (double)(end2 - begin2) / CLOCKS_PER_SEC;
	cout<<med1<<" "<<med2<<endl;
	cout<<time_spent<<endl;
	cout<<time_spent2<<endl;
	// sort(a.begin() , a.end());
	// for(ll x : a) cout<<x<<" ";
	// cout<<endl;
	// fclose(stdin);
	return 0;
}
