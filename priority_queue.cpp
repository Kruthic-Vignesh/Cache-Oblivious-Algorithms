#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long T;

void desc_sort(vector<T>&);
void asc_sort(vector<T>&);

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

class priority_q
{
public:
    vector<lvl> level;          //Levels numbered from 0 to level.size()-1
    vector<T> ins_bf, del_bf;
    void insert(T val);
    T del_min();
    void push(const ll, vector<T>&);
    void pull(const ll, vector<T>&);
    void split(const ll, const ll);
};

void priority_q::push(const ll lno, vector<T>& a) //level[lno] access, push X elements to level lno
{
/* asc_sort needed! */
    asc_sort(a);

    if(lno >= level.size())
    {
        if(lno == 0)
        {
            lvl new_lvl(c);
        }
        else
        {
            lvl new_lvl(level[lno-1].up_sz);
        }
        level[lno].fir = 0;
        level[lno].mex++;
        level[lno].cnt += a.size();
        level[lno].down_bf_cnt++;
        level[lno].down_bf[0].st = a;
        level[lno].down_bf[0].pivot = a.back();
        level[lno].down_bf[0].next = -1;
        return;
    }

    ll ind = 0;
    for(ll i = level[lno].fir; i != -1; i = level[lno].down_bf[i].next)
    {
        while(ind < a.size() && a[ind] < level[lno].down_bf[i].pivot)
        {
            level[lno].down_bf[i].st.push_back(a[ind]);
            ind++;
            level[lno].cnt++;
            if(level[lno].down_bf[i].st.size() == level[lno].down_sz+1)     //down_bf overflow
            {
                split(lno,i);               //split down_bf[i] into 2 down_bfs
                /*  find median of down_bf[i]
                    ll med = median(level[lno].down_bf[i]);*/   
                
                //    2. 1 quick_sort iteration with pivot = median   
                ll left = 0, right = level[lno].down_bf[i].st.size()-1;
                while(left < right)
                {
                    if(level[lno].down_bf[i].st[left] == med)
                    {
                        while(level[lno].down_br[i].st[right] == med) right--;
                        if(left >= right) break;
                        swap(level[lno].down_bf[i].st[left], level[lno].down_bf[i].st[right]);
                        right--;
                    }
                    left++;
                }
                ll lefti = 0, rightj = right;
                while(lefti < rightj)
                {
                    while(lefti < level[lno].down_bf[i].st.size() && level[lno].down_bf[i].st[lefti] < med) lefti++;
                    while(rightj >= 0 && level[lno].down_bf[i].st[rightj] > med) rightj--;
                    if(lefti > rightj) break;
                    swap(level[lno].down_bf[i].st[lefti], level[lno].down_bf[i].st[rightj]);
                }
                while(right < n)
                {
                    right++;
                    swap(level[lno].down_bf[i].st[lefti], level[lno].down_bf[i].st[right]);
                    lefti++;
                }
                    3. lower half to one buffer, upper half to the other    
                    level[lno].down_bf[i].pivot 
                /*
                    4. Adjust next, pivot & all counts
                    level[lno].down_bf[level[lno].mex].next = level[lno].down_bf[i].next;
                    level[lno].down_bf[i].next = level[lno].mex;
                    update mex
                */
            }
            if(level[lno].down_bf_cnt == level[lno].down_cnt+1)      //too many down buffers
            {                   
                pair<ll,ll> u = level[lno].last_down_bf();  
                ll last_bf = u.second;
                ll prev_bf = u.first;
                for(T x: level[lno].down_bf[last_bf].st)        //transfer last down_bf to up_bf
                {
                    level[lno].up_bf.push_back(x);
                    level[lno].cnt--;
                }
                level[lno].down_bf[last_bf].st.clear();
                level[lno].down_bf_cnt--;
                level[lno].down_bf[prev_bf].next = -1;
            }
        } 
    }
    while(ind < a.size())
    {
        level[lno].up_bf.push_back(a[ind]);
        ind++;
    }
    while(level[lno].up_bf.size() > level[lno].up_sz)
    {
        a.clear();
        while(a.size() < level[lno].up_sz)
        {
            a.push_back(level[lno].up_bf.back());
            level[lno].up_bf.pop_back();
        }
        push(lno+1,a);
    }
}

void priority_q::pull(const ll lno, vector<T> &a) //pull elements from level lno
{
    if(lno >= level.size())     return;

    ll ind = level[lno].fir;
    ll min_sz = (level[lno].down_sz + 1)/2;
    if(level[lno].down_bf_cnt > 0 && level[lno].down_bf[ind].st.size() >= min_sz)
    {
        desc_sort((level[lno].down_bf[ind].st));
        //take away least min_sz elements & put to a
        while(a.size() < min_sz)
        {
            a.push_back(level[lno].down_bf[ind].st.back());
            level[lno].down_bf[ind].st.pop_back();
            level[lno].cnt--;
        }
        //leave remaining in the buffer
        if(level[lno].down_bf[ind].st.size() == 0)
        {
            level[lno].fir = level[lno].down_bf[ind].next;
            level[lno].down_bf_cnt--;
        }
    }
    else if(level[lno].down_bf_cnt > 1)
    {
        //pull first buffer fully
        while(level[lno].down_bf[ind].st.size() > 0)
        {
            a.push_back(level[lno].down_bf[ind].st.back());
            level[lno].down_bf[ind].st.pop_back();
            level[lno].cnt--;
        }
        /* Removing the first down_bf from the list */
        level[lno].fir = level[lno].down_bf[ind].next;
        level[lno].down_bf_cnt--;
        ind = level[lno].fir;                           //ind points to the current first down_bf
        desc_sort((level[lno].down_bf[ind].st));        //sort second buffer
        //take reqd no of elements from second buffer
        while(a.size() < min_sz)
        {
            a.push_back(level[lno].down_bf[ind].st.back());
            level[lno].down_bf[ind].st.pop_back();
            level[lno].cnt--;
        }
        if(level[lno].down_bf[ind].st.size() == 0)
        {
            level[lno].fir = level[lno].down_bf[ind].next;
            level[lno].down_bf_cnt--;
        }
    }
    else
    {
        for(T tt : level[lno].down_bf[ind].st)      //Take all elements from down_bf
        {
            a.push_back(tt);
        }
        level[lno].down_bf[ind].st.clear();
        level[lno].down_bf_cnt = 0;
        level[lno].cnt = 0;

        vector<T> b;
        pull(lno+1, b);                     // Pull from next level

        ll u_sz = level[lno].up_bf.size();
        for(T tt : level[lno].up_bf)        //Take elements from up_bf
        {
            b.push_back(tt);
        }
        level[lno].up_bf.clear();
        asc_sort(b);                        //sort b and refill the first U elements into the up_bf;

        ll how_many_pulled = 0;
        for(ll i=0; a.size() < min_sz && i < b.size(); i++) //taking least [X]-Y keys and putting into a
        {
            a.push_back(b[i]);
            how_many_pulled++;
        }

        ll count = 0;
        for(ll i=ll(b.size())-1; i>=how_many_pulled && count < u_sz; i--, count++)      //refilling upbuffer
        {
            level[lno].up_bf.push_back(b[i]);
            b.pop_back();
        }

        if(b.size() - how_many_pulled == 0)     return;

        /* Refilling the first down_buffer of lno, size = rem & updating cnt of lno*/
        level[lno].cnt = b.size() - how_many_pulled;
        ll rem = level[lno].cnt % min_sz;               //No of elements to be put in down_bf[0]
        if(!rem)
            rem = min_sz;
        level[lno].down_bf_cnt++;
        ll ar_pos = how_many_pulled;
        ll curr_bf = 0;
        level[lno].fir = curr_bf;
        for(ll i=0; i<rem; i++)
        {
            level[lno].down_bf[curr_bf].st.push_back(b[ar_pos]);
            ar_pos++;
        }
        /* Refilling the remaining down_buffers of lno */
        ll how_many_bfs = (level[lno].cnt-rem)/min_sz;
        level[lno].down_bf_cnt += how_many_bfs;         //no of down_bfs = first + how_many_bfs
        for(ll i=1; i<=how_many_bfs; i++)
        {
            level[lno].down_bf[curr_bf].next = i;       //next of previous down_bf = i
            curr_bf = i;
            for(ll j=0; j<min_sz; j++)
            {
                level[lno].down_bf[curr_bf].st.push_back(b[ar_pos]);
                ar_pos++;
            }
            level[lno].down_bf[curr_bf].next = -1;      //next of the new down_bf = -1
        }
    }
}

int main()
{

    return 0;
}
