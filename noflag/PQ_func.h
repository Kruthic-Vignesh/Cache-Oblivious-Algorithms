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
    del_bf.push_back(val);
    asc_sort(del_bf);
    ll push_ins_bf = del_bf.back();
    del_bf.pop_back();
    ins_bf.push_back(push_ins_bf);
    if(ins_bf.size() >= ins_size)
    {
        push(0, ins_bf);
        ins_bf.clear();
    }   
}

T priority_q::del_min()
{
    if(del_bf.size())
    {
        desc_sort(del_bf);
        ll rett = del_bf.back();
        del_bf.pop_back();
        return rett;
    }
    
    pull(0,del_bf);
    ll sizzz = del_bf.size();
    while(ins_bf.size() > 0)
    {
        del_bf.push_back(ins_bf.back());
        ins_bf.pop_back();
    }
    asc_sort(del_bf);
    while(sizzz>0 && del_bf.size() > sizzz)
    {
        ins_bf.push_back(del_bf.back());
        del_bf.pop_back();
    }

    desc_sort(del_bf);
    ll rett = del_bf.back();
    del_bf.pop_back();
    return rett;
}

void priority_q::p_b()
{
    cout<<"Insertion buffer: ";
    for(ll x : ins_bf)  cout<<x<<' ';
    cout<<endl;
    cout<<"Deletion buffer: ";
    for(ll x : del_bf)  cout<<x<<' ';
    cout<<endl;
    return;
}

#endif