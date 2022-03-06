#ifndef PQ_func_h
#define PQ_func_h

#include "classes.h"

using namespace std;

pair<ll,ll> priority_q::last_down_bf(ll lno)
{
    ll i = level[lno].fir, pre = -1;
    cout<<"\nFinding last down_bf\n\n";
    while(level[lno].down_bf[i].next != -1)
    {
        cout<<i<<',';
        pre = i; 
        i = level[lno].down_bf[i].next;
    }
    cout<<endl;
    cout<<"last down_bf is "<<i<<"\n\n";
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
        cout<<"\nInsertion Buffer Full! : ";
        cout<<"Pushing to level 0...\n";
        traverse(0);
        push(0, ins_bf);
        ins_bf.clear();
    }
    else 
    {
        cout<<"Inserted "<<val<<" in ins/del_bf!\n\n";
    }
    p_b();
}

T priority_q::del_min()
{
    cout<<"Entering del_min...\n\n";
    p_b();
    if(del_bf.size())
    {
        desc_sort(del_bf);
        ll rett = del_bf.back();
        del_bf.pop_back();
        return rett;
    }
    
    pull(0,del_bf);
    ll sizzz = del_bf.size();
    cout<<sizzz<<endl;
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
    cout<<"After pulling:\n";
    p_b();
    cout<<"Leaving del_min...\n\n";
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
