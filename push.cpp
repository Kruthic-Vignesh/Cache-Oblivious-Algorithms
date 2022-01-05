#include "lvl"
#include "priority_queue"

using namespace std;

void priority_q::push_to_upbf(ll lno)
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

void priority_q::make_newlvl(ll lno)
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

void priority_q::quicksort(ll lno, ll i)
{
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
    while(right < level[lno].down_bf[i].st.size()-1)
    {
        right++;
        swap(level[lno].down_bf[i].st[lefti], level[lno].down_bf[i].st[right]);
        lefti++;
    }
}

void priority_q::push(const ll lno, vector<T>& a) //level[lno] access, push X elements to level lno
{
/* asc_sort needed! */
    asc_sort(a);

    if(lno >= level.size()) make_newlvl(lno);

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
                ll med = median(level[lno].down_bf[i]);  
                //split(lno,i);               //split down_bf[i] into 2 down_bfs
                /*  find median of down_bf[i]*/ 
                // @Shashwathy
                //    2. 1 quick_sort iteration with pivot = median   
                quicksort(lno,i);
                //    3. lower half to one buffer, upper half to the other    
                //   level[lno].down_bf[i].pivot 
                /*
                    4. Adjust next, pivot & all counts
                    level[lno].down_bf[level[lno].mex].next = level[lno].down_bf[i].next;
                    level[lno].down_bf[i].next = level[lno].mex;
                    update mex
                */
            }
            if(level[lno].down_bf_cnt == level[lno].down_cnt+1)      //too many down buffers                
                push_to_upbf(lno);
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