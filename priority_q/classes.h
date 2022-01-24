#ifndef classes_h
#define classes_h

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long T;
const T nul = NULL;
const ll c = 12; 

class bf
{
public:
    vector<T> st;
    ll next;
    T pivot;
};

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
    lvl(const ll x) : up_sz (pow(x,1.5)), min_sz(x), down_sz (2*x - 1), down_cnt(ceil(1 + pow(x,0.5)))
    {
        fir = -1;
        down_bf_cnt = 0;
        mex = 0;

        //Add later
    }
    pair<ll,ll> last_down_bf();
};

pair<ll,ll> 

class priority_q
{
public:
    vector<lvl> level;          //Levels numbered from 0 to level.size()-1
    vector<T> ins_bf, del_bf;   //insert and delete buffers
    const ll ins_size;                //maximum size of insert and delete buffers
    void insert(T val);         
    T del_min();
    void push(const ll, vector<T>&);
    void pull(const ll, vector<T>&);
    void split(const ll, const ll);

    void make_newlvl(ll,vector<T>&);
    void push_to_upbf(ll);
    pair<ll,ll> last_down_bf(ll);
    void quicksort(ll lno, ll i, ll med);
    void reg_pull(const ll lno, vector<T> &a);
    ll pull_from_above(const ll lno, vector<T> &a, vector<T> &b);
    void refill_downbf(const ll lno, vector<ll> &b, ll);
};

#endif