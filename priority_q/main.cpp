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
    for(int i=0; i<40; i++)
        a.insert(glr(1,200));
    
    a.traverse(0);
    a.traverse(1);
    a.traverse(2);
}
