#ifndef PQ_func_h
#define PQ_func_h

#include "classes.h"

using namespace std;

priority_q::priority_q()
{
    this->no_el = 0;
}

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
    this->no_el++;
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
    if(this->no_el > 0) this->no_el--;
    else throw("-1");
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

ll priority_q::size()
{
    return this->no_el;
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

void priority_q::traverse(ll lno)
{
    cout<<"TRAVERSING lvl "<<lno<<endl<<endl;
    if(lno >= level.size()) 
    {
        cout<<endl;
        return;
    }
    cout<<"down_bf\n";
    cout<<"down_bf_size "<<level[lno].down_bf_cnt<<" "<<level[lno].min_sz<<" "<<level[lno].down_cnt<<endl;
    ll i = level[lno].fir;
    if(i == -1) return;
    while(true)
    {
        cout<<"i is "<<i<<", pivot is "<<level[lno].down_bf[i].pivot<<endl;
        for(ll x : level[lno].down_bf[i].st)
            cout<<x<<" ";
        cout<<endl;
        if(level[lno].down_bf[i].next == -1) break;
        i = level[lno].down_bf[i].next;
    }
    cout<<endl<<endl;
    cout<<"up_bf\n";
    for(ll x:level[lno].up_bf)  cout<<x<<' ';
    cout<<endl<<endl;
}

void priority_q::final_traverse(ll lno)
{
    cout<<"TRAVERSING lvl "<<lno<<endl<<endl;
    if(lno >= level.size()) 
    {
        cout<<endl;
        return;
    }
    cout<<"down_bf\n";
    cout<<"down_bf_size "<<level[lno].down_bf_cnt<<" "<<level[lno].min_sz<<" "<<level[lno].down_cnt<<endl;
    ll i = level[lno].fir;
    if(i == -1) return;
    while(true)
    {
        cout<<"i is "<<i<<", pivot is "<<level[lno].down_bf[i].pivot<<endl;
        asc_sort(level[lno].down_bf[i].st);
        for(ll x : level[lno].down_bf[i].st)
            cout<<x<<" ";
        cout<<endl;
        if(level[lno].down_bf[i].next == -1) break;
        i = level[lno].down_bf[i].next;
    }
    cout<<endl<<endl;
    cout<<"up_bf\n";
    asc_sort(level[lno].up_bf);
    for(ll x:level[lno].up_bf)  cout<<x<<' ';
    cout<<endl<<endl;
}

#endif
