/* PC-01 Cache Oblivious Algorithms */

#include <iostream>

using namespace std;

#define endl "\n"

typedef long long ll;

const ll N = 1001;

ll a[N][N],b[N][N],c[N][N];

void sol()
{
    ll m, n, p;    //size of first matrix : m x n, size of second matrix : n x p;
    cin>>m>>n>>p;
    for(ll i = 0; i < m; i++)
    {
        for(ll j = 0; j < n; j++)
        {
            cin>>a[i][j];
        }
    }
    for(ll i = 0; i < n; i++)
    {
        for(ll j = 0; j < p; j++)
        {
            cin>>b[i][j];
        }
    }
    for(ll i = 0; i < m; i++)
    {
        for(ll j = 0; j < p; j++) 
        {
            c[i][j] = 0;
            for(ll k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    ll t;
    cin>>t;
    for(ll i = 0; i < t; i++) 
        sol();

    fclose(stdin);
    return 0;
}
