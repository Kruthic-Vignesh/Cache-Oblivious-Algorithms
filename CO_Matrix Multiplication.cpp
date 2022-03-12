/* PC-01 - Cache Algorithms */

#include <iostream>

using namespace std;

typedef long long ll;
const ll N = 1001;

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
    cin>>m>>n>>p;
    for(ll i=0; i<m; i++)
    {
        for(ll j=0; j<n; j++)
        {
            cin>>a[i][j];
        }
    }
    for(ll i=0; i<n; i++)
    {
        for(ll j=0; j<p; j++)
        {
            cin>>b[i][j];
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
   
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
   
    fclose(stdin);
    fclose(stdout);
    return 0;
}
