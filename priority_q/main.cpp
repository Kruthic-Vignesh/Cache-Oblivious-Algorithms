#include "classes.h"
#include "PQ_func.h"
#include "push.h"
#include "pull.h"
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int gr(int r)
{
   uniform_int_distribution<int> uid(0,r-1);
   int val = uid(rng);
   return val+1;
}

int glr(int l, int r)
{
    int dif = r-l+1;
    int x = gr(dif) + l-1;
    return x;
}

int32_t main()
{
    priority_q a;
    // ifstream xxx("t10000.txt");
    // ofstream yyy("TT10000.txt");
    // while(xxx)
    // {
    //     char f;
    //     xxx.get(f);
    //     if(f!=',')
    //         yyy.put(f);
    //     else
    //         yyy.put(' ');
        
    // }
    
    

    // ofstream fout("t2000000.txt");
    // for(ll i=0; i<2000000; i++)
    // {
    //     fout<<glr(1,1000000000)<<' ';
    // }
    // fout.close();

    freopen("t2000000.txt","r",stdin);
    freopen("o2000000.txt","w",stdout);
    vector<ll> v;
    for(int i=0; i<2000000; i++)
    {
        int val;
        cin>>val;
        v.push_back(val);
        a.insert(val);
        //if(v[i]==993)
            //cout<<i<<' ';
    }
    
    cout<<"\n\n\nFINAL TRAVERSAL\n\n\n";
    a.final_traverse(0);
    a.final_traverse(1);
    a.final_traverse(2);  
    a.final_traverse(3);
    a.final_traverse(4);
    a.final_traverse(5);
    a.final_traverse(6);
    a.final_traverse(7);

    //for(ll xxxx:v)
    //    cout<<xxxx<<' ';

}
