#ifndef classes_h
#define classes_h

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long long T;
const T nul = NULL;
const ll c = 5; 

void asc_sort(vector<ll>& a)
{
    sort(a.begin(), a.end());
    return;
}

void desc_sort(vector<ll>& a)
{
    sort(a.rbegin(), a.rend());
    return;
}

ostream& operator<<(ostream& os, const vector<ll>& dt)
{
    for(ll x : dt) cout<<x<<" ";
    cout<<endl;
    return os;
}

ll median(vector<ll> a)
{
    asc_sort(a);
    int u = a.size();
    u = (u-1)/2;
    return a[u];
}

class bf
{
public:
    vector<T> st;
    ll next;
    T pivot;
    bf()
    {
        next = -1;
        pivot = INT_MIN;
    }
};

// make new_lvl function
class lvl
{
public:
    vector<T> up_bf;
    vector<bf> down_bf;
    ll fir, down_bf_cnt, mex;
    /*
    fir         : index of the first down buffer
    down_bf_cnt : number of non-empty down_bfs
    up_sz       : max size of up buffer (X^3/2)
    min_sz      : min size of down buffer (X)
    down_sz     : max size of down buffer (except first one) (2*X-1)
    down_cnt    : max number of downbuffers (X^1/2 + 1)
    cnt         : total number of elements in the down buffers
    */
    const ll up_sz, min_sz, down_sz, down_cnt;
    ll cnt;
    lvl(const ll x) : up_sz (pow(x,1.5)), min_sz(x), down_sz (2*x - 1), down_cnt(ceil(pow(x,0.5))+1)
    {
        fir = -1;
        down_bf_cnt = 0;
        mex = 0;
        bf empty_buf;
        for(int i = 0; i <= down_cnt; i++) down_bf.push_back(empty_buf);
// cout<<"done"<<endl;
//Add later
    }
}; 

class priority_q
{
public:
    vector<lvl> level;          //Levels numbered from 0 to level.size()-1
    vector<T> ins_bf, del_bf;   //insert and delete buffers
    const ll ins_size = 5;                //maximum size of insert and delete buffers
// implement priority_q size
    void insert(T val);         
    T del_min();
    void push(const ll, vector<T>&);
    void pull(const ll, vector<T>&);
    void split(const ll, const ll);
    void traverse(ll lno)
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
    void final_traverse(ll lno)
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

    void make_newlvl(ll,vector<T>&);
    void push_to_upbf(ll);
    pair<ll,ll> last_down_bf(ll);
    void quicksort(ll lno, ll, ll);
    void reg_pull(const ll lno, vector<T> &a);
    ll pull_from_above(const ll lno, vector<T> &a, vector<T> &b, ll&);
    void pull_to_fill(const ll lno, vector<T> &b, ll&);
    void refill_downbf(const ll, vector<ll> &, ll);
    void p_b();
};

#endif