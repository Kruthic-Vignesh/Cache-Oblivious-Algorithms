#include<iostream>
#include<vector>
#include<algorithm>

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
    down_sz     : max size of down buffer (except first one) (2*X-1)
    down_cnt    : max number of downbuffers (X^1/2 + 1)
    cnt         : total number of elements in the down buffers
    */
    const ll up_sz, down_sz, down_cnt;
    ll cnt;
    lvl(const ll x) : up_sz (pow(x,1.5)), down_sz (2*x - 1), down_cnt(ceil(1 + pow(x,0.5)))
    {
        fir = -1;
        down_bf_cnt = 0;
        mex = 0;

        //Add later
    }
    pair<ll,ll> last_down_bf();
};

pair<ll,ll> lvl::last_down_bf()
{
    ll i = level[lno].fir, pre = -1;
    while(level[lno].down_bf[i].next != -1)
    {
        pre = i; 
        i = level[lno].down_bf[i].next;
    }
    return {pre,i};
}
