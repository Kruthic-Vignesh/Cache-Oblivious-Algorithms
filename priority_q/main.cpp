#include "classes.h"
#include "PQ_func.h"
#include "push.h"
#include "pull.h"
#include <bits/stdc++.h>
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
    int N = 500;
    priority_queue<ll, vector<ll>, greater<ll>> v; 

    ll cc = 0, vv = 0;
    bool ch = true;
    freopen("in1.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    ofstream fout("outt1.txt");
    int val;
    for(int i = 0; i < 500; i++)
    {
        // int val = glr(1, 12874943);
        cin>>val;
        // str.push_back(val);
        // cout<<val<<" ";
        if(val%3 == 1 && v.size() > 0)
        {
            ll v1 = v.top(); v.pop();
            ll v2 = a.del_min();
            fout<<"DELETION "<<v1<<" "<<v2<<endl;
            if(v1 != v2) ch = false;
            if(!ch)
            {
                fout<<"You are wrong!\n";
                fout<<i<<endl;
                exit(0);
            }
        }
        else
        {
            fout<<"INSERTION OF VAL! "<<val<<endl;
            v.push(val);
            a.insert(val);
        }

        cout<<" a.ins_bf.size()  " << a.ins_bf.size()<<endl;

        if(a.ins_bf.size()>5)
        {
            cout<<"INS BF OVERFLOW!!!!\n";
            for(ll x:a.ins_bf)
                cout<<x<<' ';
            exit(0);
        }
    }
    while(v.size() > 0)
    {
        ll v1 = v.top(); v.pop();
        ll v2 = a.del_min();
        fout<<"End of the world "<<v1<<" "<<v2<<endl;
        if(v1 != v2) ch = false;

        if(!ch)
        {
            fout<<"You are wrong!\n";
            exit(0);
        }
    }
    // ofstream fout("o4.txt");
    if(ch) cout<<"MY WAIFU IS AKARI"<<endl;
    // fout.close();
    fclose(stdin);
    fclose(stdout);

}
