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

ll a[N][N],b[N][N];

void transpose(ll rs, ll re, ll cs, ll ce)
{
    ll mm = re-rs+1, nn = ce-cs+1;
    if(mm==1 && nn==1)
    {
        b[cs][rs] = a[rs][cs];
        return;
    }

    if(mm>=nn)
    {
        ll mid=(rs+re)/2;
        transpose(rs, mid, cs, ce);
        transpose(mid+1, re, cs, ce);
    }
    else
    {
        ll mid=(cs+ce)/2;
        transpose(rs, re, cs, mid);
        transpose(rs, re, mid+1, ce);
    }
}

void solv()
{
    ll m,n;
    m = N - getRand(10);
    n = N - getRand(10);

    for(ll i=0; i<m; i++)
    {
        for(ll j=0; j<n; j++)
        {
            a[i][j] = getRand(1e4);
//            cout<<a[i][j]<<' ';
        }
//        cout<<endl;
    }

    transpose(0,m-1,0,n-1);
//    for(ll i=0; i<n; i++)
//    {
//        for(ll j=0; j<m; j++)
//        {
//            cout<<b[i][j]<<' ';
//        }
//        cout<<endl;
//    }
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
