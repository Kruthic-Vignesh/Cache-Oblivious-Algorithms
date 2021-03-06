#ifndef pull_h
#define pull_h

#include "classes.h"
#include "PQ_func.h"

void priority_q::reg_pull(const ll lno, vector<T> &a)
{
    ll ind = level[lno].fir;
    ll min_sz = level[lno].min_sz;
    // cout<<min_sz<<endl;
    // cout<<"DBF\n";
    // for(ll x:level[lno].down_bf[ind].st)
    // {
    //     cout<<x<<' ';
    // }
    // cout<<endl;
    desc_sort((level[lno].down_bf[ind].st));
    // take away least min_sz elements & put to a
    while(a.size() < min_sz)
    {
        a.push_back(level[lno].down_bf[ind].st.back());
        level[lno].down_bf[ind].st.pop_back();
        level[lno].cnt--;
        //cout<<"yo mama so fat! ";
        // cout<<endl;
        // cout<<a.size()<<' '<<min_sz<<endl;
    }
    //cout<<"Henlo worldo"<<endl;
    // leave remaining in the buffer
    if(level[lno].down_bf[ind].st.size() == 0)
    {
        level[lno].fir = level[lno].down_bf[ind].next;
        level[lno].down_bf[ind].pivot = INT_MIN;
        level[lno].down_bf[ind].next = -1;
        level[lno].down_bf_cnt--;
        if(level[lno].mex > ind) level[lno].mex = ind;  // updating mex

        //cout<<"Hello world"<<endl;
        // refilling of down buffers
        if(level[lno].fir == -1 || !level[lno].down_bf_cnt)
        {
            vector<T> b,c;
            ll max_el = INT_MAX;
            pull_to_fill(lno,b,max_el);

            //cout<<"Pulled to fill!"<<endl;
            ll count = 0;   
            for(ll i=ll(b.size())-1; i>=0 && count < level[lno].up_sz && b[i]>max_el; i--, count++)      //refilling upbuffer
            {
                level[lno].up_bf.push_back(b[i]);
                b.pop_back();
            }
            //cout<<"Filled up_bf!"<<endl;
            refill_downbf(lno,b,0);
        }
    }
}

void priority_q::pull_to_fill(const ll lno, vector<T> &b, ll &max_el)
{   
    level[lno].down_bf_cnt = 0;
    level[lno].cnt = 0;
    level[lno].fir = -1;
    level[lno].mex = 0;

    pull(lno+1, b);                     // Pull from next level

    if(b.size())
        max_el = *max_element(b.begin(),b.end());

    ll u_sz = level[lno].up_bf.size();
    for(T tt : level[lno].up_bf)        //Take elements from up_bf
    {
        b.push_back(tt);
    }
    level[lno].up_bf.clear();
    asc_sort(b);                        //sort b and refill the first U elements into the up_bf;
}

ll priority_q::pull_from_above(const ll lno, vector<T> &a, vector<T> &b, ll &max_el)
{
    ll ind = level[lno].fir;

    if(ind != -1)
    {
        for(T tt : level[lno].down_bf[ind].st)      //Take all elements from down_bf
            a.push_back(tt);
        level[lno].down_bf[ind].st.clear();
        level[lno].down_bf[ind].pivot = INT_MIN;
        level[lno].down_bf[ind].next = -1;
    }
        
    level[lno].down_bf_cnt = 0;
    level[lno].cnt = 0;
    level[lno].fir = -1;
    level[lno].mex = 0;

    pull(lno+1, b);                     // Pull from next level

    if(b.size())
        max_el = *max_element(b.begin(),b.end());

    ll u_sz = level[lno].up_bf.size();
    for(T tt : level[lno].up_bf)        //Take elements from up_bf
    {
        b.push_back(tt);
    }
    level[lno].up_bf.clear();
asc_sort(b);                        //sort b and refill the first U elements into the up_bf;

    ll how_many_pulled = 0;
    for(ll i=0; a.size() < level[lno].min_sz && i < b.size(); i++) //taking least [X]-Y keys and putting into a
    {
        a.push_back(b[i]);
        how_many_pulled++;
    }
    return how_many_pulled;
}

void priority_q::refill_downbf(const ll lno, vector<ll> &b, ll how_many_pulled)
{
    if(b.size() - how_many_pulled == 0)     return;

    /* Refilling the first down_buffer of lno, size = rem & updating cnt of lno*/
    level[lno].cnt = b.size() - how_many_pulled;
    ll rem = level[lno].cnt % level[lno].down_sz;               //No of elements to be put in down_bf[0]
    if(!rem)
        rem = level[lno].down_sz;
    level[lno].down_bf_cnt++;
    ll ar_pos = how_many_pulled;
    ll curr_bf = 0;
    level[lno].fir = curr_bf;
    for(ll i = 0; i < rem; i++)
    {
        level[lno].down_bf[curr_bf].pivot = max(level[lno].down_bf[curr_bf].pivot, b[ar_pos]);
        level[lno].down_bf[curr_bf].st.push_back(b[ar_pos++]);
        // ar_pos++;
    }
    //cout<<"Refilling"<<endl;
    /* Refilling the remaining down_buffers of lno */
    ll how_many_bfs = (level[lno].cnt-rem)/level[lno].down_sz;
    level[lno].down_bf_cnt += how_many_bfs;         //no of down_bfs = first + how_many_bfs
    //cout<<how_many_bfs<<endl;
    for(ll i = 1; i <= how_many_bfs; i++)
    {
        level[lno].down_bf[curr_bf].next = i;       //next of previous down_bf = i
        curr_bf = i;
        for(ll j = 0; j < level[lno].down_sz; j++)
        {
            level[lno].down_bf[curr_bf].pivot = max(level[lno].down_bf[curr_bf].pivot, b[ar_pos]);
            level[lno].down_bf[curr_bf].st.push_back(b[ar_pos++]);
            // ar_pos++;
        }
        level[lno].down_bf[curr_bf].next = -1;      //next of the new down_bf = -1
        //cout<<i<<','<<endl;
    }
    //cout<<"Refilled"<<endl;
}

void priority_q::pull(const ll lno, vector<T> &a) //pull elements from level lno
{
    if(lno >= level.size())     return;

    ll ind = level[lno].fir;
    // cout<<endl<<"Priint a before pulling from level "<<lno<<endl;
    // for(ll x : a)
    // {
    //     cout<<x<<" ";
    // }
    if(/*ind != -1 && */level[lno].down_bf_cnt > 0 && level[lno].down_bf[ind].st.size() >= level[lno].min_sz)
    {
        reg_pull(lno,a);
        // cout<<endl<<"Priint a after pulling from level "<<lno<<endl;
        // for(ll x : a)
        // {
        //     cout<<x<<" ";
        // }
        // cout<<endl;
        return;
    }
    else if(level[lno].down_bf_cnt > 1)
    {
        //pull first buffer fully
//cout<<"second pull"<<endl;
        while(level[lno].down_bf[ind].st.size() > 0)
        {
            a.push_back(level[lno].down_bf[ind].st.back());
            level[lno].down_bf[ind].st.pop_back();
            level[lno].cnt--;
        }
        /* Removing the first down_bf from the list */
        level[lno].fir = level[lno].down_bf[ind].next;
        level[lno].down_bf_cnt--;
        level[lno].down_bf[ind].pivot = INT_MIN;
        level[lno].down_bf[ind].next = -1;
        if(level[lno].mex > ind) level[lno].mex = ind;  // updating mex
       // ind = level[lno].fir;                           ind points to the current first down_bf
        reg_pull(lno,a);
    }
    else
    {
        //cout<<"Went here\n";
        vector<T> b;
        ll max_el = INT_MAX;
        ll how_many_pulled = pull_from_above(lno,a,b,max_el);

        ll count = 0;   
        //cout<<"Came here"<<endl;
        for(ll i=ll(b.size())-1; i >= how_many_pulled && count < level[lno].up_sz && b[i]>max_el; i--, count++)      //refilling upbuffer
        {
            level[lno].up_bf.push_back(b[i]);
            b.pop_back();
        }
        //cout<<"Gonna refill "<<b.size() - how_many_pulled<<endl;
        refill_downbf(lno,b,how_many_pulled);
    }
}


#endif
