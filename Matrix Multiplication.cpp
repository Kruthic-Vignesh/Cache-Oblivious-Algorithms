/* PC-01 - Cache Algorithms */

#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll N = 1001;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll getRand(ll r)
{
   uniform_int_distribution<ll> uid(0,r-1);
   return uid(rng);
}

ll a[N][N],b[N][N],c[N][N];

void multiply(ll ars, ll are, ll acs,ll ace, ll brs, ll bre, ll bcs, ll bce)
{
    ll mm=are-ars+1, nn=ace-acs+1, pp=bce-bcs+1;

    if(mm==1 && nn==1 && pp==1)
    {
        c[ars][bcs]+=a[ars][acs]*b[brs][bcs];
        return;
    }

    if(mm>=nn && mm>=pp)
    {
        ll mid=(ars+are)/2;
        multiply(ars, mid, acs, ace, brs, bre, bcs, bce);
        multiply(mid+1, are, acs, ace, brs, bre, bcs, bce);
    }
    else if(pp>=nn && pp>=mm)
    {
        ll mid=(bcs+bce)/2;
        multiply(ars, are, acs, ace, brs, bre, bcs, mid);
        multiply(ars, are, acs, ace, brs, bre, mid+1, bce);
    }
    else
    {
        ll midb=(brs+bre)/2, mida=(acs+ace)/2;
        multiply(ars, are, acs, mida, brs, midb, bcs, bce);
        multiply(ars, are, mida+1, ace, midb+1, bre, bcs, bce);
    }
}

void solv()
{
    ll m,n,p;
    m = N - getRand(10);
    n = N - getRand(10);
    p = N - getRand(10);
    for(ll i=0; i<m; i++)
    {
        for(ll j=0; j<n; j++)
        {
            a[i][j] = getRand(1e4);
        }
    }
    for(ll i=0; i<n; i++)
    {
        for(ll j=0; j<p; j++)
        {
            b[i][j] = getRand(1e4);
        }
    }
    for(ll i=0; i<m; i++)
    {
        for(ll j=0; j<p; j++)
        {
            c[i][j] = 0;
        }
    }

    multiply(0,m-1,0,n-1,0,n-1,0,p-1);
    return;
}

int main()
{
    ll tc=1;
    cin>>tc;

    double time_spent = 0;
    clock_t begin = clock();

    for(ll lv=1;lv<=tc;lv++)
    {
        solv();
    }

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<time_spent<<endl;
    return 0;
}
