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
    if(del_bf.size() < ins_size)
    {
        del_bf.push_back(val);
        cout<<"Inserted "<<val<<" in ins/del_bf!\n\n";
        return;
    }
    del_bf.push_back(val);
asc_sort(del_bf);
    ll push_ins_bf = del_bf.back();
    del_bf.pop_back();
    ins_bf.push_back(push_ins_bf);
    if(ins_bf.size() >= ins_size)
    {
        cout<<"\nInsertion Buffer Full! : ";
        for(ll x : ins_bf) cout<<x<<' ';
        cout<<endl;
        cout<<"Pushing to level 0...\n";
        traverse(0);
        push(0, ins_bf);
        ins_bf.clear();
    }
    else 
    {
        cout<<"Inserted "<<val<<" in ins/del_bf!\n\n";
    }
}

T priority_q::del_min()
{
cout<<endl<<"ins_bf"<<endl;
for(ll x : ins_bf)
    cout<<x<<" ";
cout<<endl;
    if(del_bf.size() == 0) return nul;
desc_sort(del_bf);
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
cout<<endl<<"del_min  ins_bf"<<endl;
for(ll x : ins_bf)
    cout<<x<<" ";
cout<<endl;
cout<<"del_bf"<<endl;
for(ll x : del_bf)
    cout<<x<<" ";
cout<<endl;
    return rett;
}


#endif
