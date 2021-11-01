/*    Single Matrix Generator    */

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll NN = 10000;

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

#define cout outputFile[tc]

int main()
{
    string file[5] = {"T1.txt", "T2.txt", "T3.txt", "T4.txt", "T5.txt"};
    ofstream outputFile[5];
    for (ll i=0; i<5; i++) outputFile[i].open(file[i].c_str());

    for(ll tc=0; tc<5; tc++)
    {
        ll t = 1;
        cout<<t<<endl;
        while(t--)
        {
            ll m = gr(NN);
            ll n = gr(NN);
            cout<<m<<' '<<n<<endl;
            for(ll i=0; i<m; i++)
            {
                for(ll j=0; j<n; j++)
                {
                    cout<<gr(1e9)<<' ';
                }
                cout<<endl;
            }
        }
    }
    return 0;
}

