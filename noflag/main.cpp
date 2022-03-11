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

priority_q a;
priority_queue<ll, vector<ll>, greater<ll>> v; 

int32_t main()
{
    int N = 500;
    ll cc = 0, vv = 0;
    bool ch = true;
    ifstream fin("input02.txt");
    ofstream fout("outtie02.txt");
    int val;
    while(fin>>val)
    {
        if(val%3 == 0 && v.size() > 0)
        {
            ll v1 = v.top(); v.pop();
            ll v2 = a.del_min();
            int u1 = v.size();
            int u2 = a.size();
            fout<<"DELETION "<<v1<<" "<<v2<<" "<<u1<<" "<<u2<<endl;
            if(v1 != v2 || u1 != u2) ch = false;
            if(!ch)
            {
                cout<<"fayo"<<endl;
                exit(0);
            }
        }
        else
        {
            v.push(val);
            a.insert(val);
        }
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
        int u1 = v.size();
        int u2 = a.size();
        fout<<v1<<" "<<v2<<" "<<u1<<" "<<u2<<endl;
        if(v1 != v2 || u1 != u2) 
        {
            ch = false;
            cout<<"fayl"<<endl;
        }

        if(!ch)
        {
            fout<<"You are wrong!\n";
            exit(0);
        }
    }
    cout<<"\nSUCCESS\n";
    fclose(stdout);
}
