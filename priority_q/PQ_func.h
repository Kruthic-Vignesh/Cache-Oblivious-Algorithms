#ifndef PQ_func_h
#define PQ_func_h

#include "classes.h"

using namespace std;

pair<ll,ll> priority_q::last_down_bf(ll lno)
{
    ll i = level[lno].fir, pre = -1;
    while(level[lno].down_bf[i].next != -1)
    {
        pre = i; 
        i = level[lno].down_bf[i].next;
    }
    return {pre,i};
}

void priority_q::insert(T val)
{
    if(del_bf.size() < ins_size)
    {
        del_bf.push_back(val);
        return;
    }
    del_bf.push_back(val);
asc_sort(del_bf);
    ll push_ins_bf = del_bf.back();
    del_bf.pop_back();
    ins_bf.push_back(push_ins_bf);
    if(ins_bf.size() == ins_size)
    {
        cout<<"\nOutputting INS BF: ";
        for(ll x : ins_bf) cout<<x<<' ';
        cout<<endl;
        push(0, ins_bf);
        ins_bf.clear();
    }
    else 
    {
        cout<<"Insertion done in ins_bf!\n\n";
    }
}

T priority_q::del_min()
{
cout<<endl<<"ins_bf"<<endl;
for(ll x : ins_bf)
    cout<<x<<" ";
cout<<endl;
    if(del_bf.size() == 0) return nul;
    ll rett = del_bf.back();
    del_bf.pop_back();
    if(del_bf.size() == 0)
    {
        pull(0, del_bf);
        while(ins_bf.size() > 0)
        {
            del_bf.push_back(ins_bf.back());
            ins_bf.pop_back();
        }
    }
    // T ret = del_bf.back();
    // del_bf.pop_back();
asc_sort(del_bf);
    while(del_bf.size() > ins_size)
    {
        ins_bf.push_back(del_bf.back());
        del_bf.pop_back();
    }
cout<<"del_bf"<<endl;
for(ll x : del_bf)
    cout<<x<<" ";
cout<<endl;
    return rett;
}


#endif
