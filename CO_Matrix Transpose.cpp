/* PC-01 - Cache Algorithms */

#include <iostream>

using namespace std;

typedef long long ll;
const ll N = 1001;

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
    ll m, n;
    cin>>m>>n;

    for(ll i=0; i<m; i++)
    {
        for(ll j=0; j<n; j++)
        {
            cin>>a[i][j];
        }
    }

    transpose(0,m-1,0,n-1);
    return;
}

int main()
{
    freopen("input.txt", "r", stdin);
   
    ll tc=1;
    cin>>tc;

    for(ll lv=1;lv<=tc;lv++)
    {
        solv();
    }
   
    fclose(stdin);
    return 0;
}
