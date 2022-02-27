#ifndef push_h
#define push_h

#include "classes.h"
#include "PQ_func.h"

void priority_q::push_to_upbf(ll lno)
{
    pair<ll,ll> u = last_down_bf(lno);  
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

void priority_q::make_newlvl(ll lno, vector<T> &a)
{
    if(lno == 0)
    {
        level.push_back(lvl(c));
    }
    else
    {
        level.push_back(lvl(level[lno-1].up_sz));
    }
// level[lno].mex++;
// level[lno].cnt += a.size();
// level[lno].down_bf_cnt++;
// level[lno].down_bf[0].st = a;
// level[lno].down_bf[0].pivot = a.back();
// level[lno].down_bf[0].next = -1;
    return;
}

void priority_q::quicksort(ll lno, ll i, ll med)
{
    ll left = 0, right = level[lno].down_bf[i].st.size()-1;
    while(left < right)
    {
        if(level[lno].down_bf[i].st[left] == med)
        {
            while(level[lno].down_bf[i].st[right] == med) right--;
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

    cout<<"\nQuickSorted with median = "<<med<<endl;
    for(ll x : level[lno].down_bf[i].st)
        cout<<x<<' ';
    cout<<endl<<endl;
}

void priority_q::push(const ll lno, vector<T>& a) //level[lno] access, push X elements to level lno
{
    cout << "Push function at level "<<lno<<endl;
/* asc_sort needed! */
asc_sort(a);
/*for(ll x :a) cout<<x<<" ";
cout<<endl;*/
    if(lno >= level.size()) 
    {
        make_newlvl(lno,a);
        level[lno].fir = 0;
        level[lno].mex++;
        level[lno].cnt += a.size();
        level[lno].down_bf_cnt++;
        level[lno].down_bf[0].st = a;
        level[lno].down_bf[0].pivot = a.back();
        level[lno].down_bf[0].next = -1;
// cout<<"YES"<<endl;
        return;
    }
    ll ind = 0, i =level[lno].fir;
    for(; ; i = level[lno].down_bf[i].next)
    {
        cout<<"\ngoing thru down_bf "<<i<<"\n";
        while(ind < a.size() && a[ind] < level[lno].down_bf[i].pivot)
        {
            level[lno].down_bf[i].st.push_back(a[ind]);
            ind++;
            level[lno].cnt++;
            if(level[lno].down_bf[i].st.size() == level[lno].down_sz+1)     //down_bf overflow
            {
                cout<<"\n\nOVERFLOWW BRUH!\n\n";
                cout<<"\n\nfinding median...\n";
                ll med;
med = median(level[lno].down_bf[i].st);  
                //split(lno,i);               //split down_bf[i] into 2 down_bfs
                /*  find median of down_bf[i]*/ 
                // @Shashwathy
                //    2. 1 quick_sort iteration with pivot = median   
                quicksort(lno,i,med);
                //    3. lower half to one buffer, upper half to the other    
                //   level[lno].down_bf[i].pivot 
                
                /*  4. Adjust next, pivot & all counts */
//check with adi
                {
                    
                    level[lno].down_bf[level[lno].mex].pivot = level[lno].down_bf[i].pivot;
                    cout<<"\nNew bf's pivot is = "<<level[lno].down_bf[level[lno].mex].pivot<<endl;
                    while(level[lno].down_bf[level[lno].mex].st.size() < level[lno].min_sz)
                    {
                        level[lno].down_bf[level[lno].mex].st.push_back(level[lno].down_bf[i].st.back());
                        level[lno].down_bf[i].st.pop_back();
                        level[lno].down_bf[i].pivot = level[lno].down_bf[i].st.back();
                    }
                    level[lno].down_bf[level[lno].mex].next = level[lno].down_bf[i].next;
                    level[lno].down_bf[i].next = level[lno].mex;
                    i = level[lno].mex;
                    level[lno].down_bf_cnt++;
                //    update mex
                    cout<<endl<<"yo mama split"<<endl;
                    cout<<"old mama = "<<i<<", new mama = "<<level[lno].mex;
                    level[lno].mex = level[lno].down_bf.size();
                    for(int j=0; j<level[lno].down_bf.size(); j++)
                    {
                        if(level[lno].down_bf[j].st.size()==0)
                        {
                            level[lno].mex = j;
                            break;
                        }
                    }
                    cout<<", new mex = "<<level[lno].mex<<endl<<endl;
                }
                
            }
            if(level[lno].down_bf_cnt == level[lno].down_cnt+1)      //too many down buffers                
                push_to_upbf(lno);
        } 
        if(level[lno].down_bf[i].next == -1)
            break; 
    }

    while(ind < a.size())
    {
        level[lno].down_bf[i].st.push_back(a[ind]);
        level[lno].down_bf[i].pivot = max(level[lno].down_bf[i].pivot,a[ind]);
        ind++;
        if(level[lno].down_bf[i].st.size() > level[lno].down_sz)
        {
            cout<<"\n\nOVERFLOWW BROO!\n\n";
            if(level[lno].down_bf[i].st.size() > level[lno].down_sz)     //down_bf overflow
            {
                cout<<"\n\nfinding median...\n";
                ll med;
med = median(level[lno].down_bf[i].st);  
                //split(lno,i);               //split down_bf[i] into 2 down_bfs
                /*  find median of down_bf[i]*/ 
                // @Shashwathy
                //    2. 1 quick_sort iteration with pivot = median   
                quicksort(lno,i,med);
                //    3. lower half to one buffer, upper half to the other    
                //   level[lno].down_bf[i].pivot 
                
                /*  4. Adjust next, pivot & all counts */
//check with adi
                {
                    
                    level[lno].down_bf[level[lno].mex].pivot = level[lno].down_bf[i].pivot;
                    cout<<"\nNew bf's pivot is = "<<level[lno].down_bf[level[lno].mex].pivot<<endl;
                    while(level[lno].down_bf[level[lno].mex].st.size() < level[lno].min_sz)
                    {
                        level[lno].down_bf[level[lno].mex].st.push_back(level[lno].down_bf[i].st.back());
                        level[lno].down_bf[i].st.pop_back();
                        level[lno].down_bf[i].pivot = level[lno].down_bf[i].st.back();
                    }
                    level[lno].down_bf[level[lno].mex].next = level[lno].down_bf[i].next;
                    level[lno].down_bf[i].next = level[lno].mex;
                    i = level[lno].mex;
                    level[lno].down_bf_cnt++;
                //    update mex
                    cout<<endl<<"yo mama split"<<endl;
                //    cout<<"old mama = "<<i<<", new mama = "<<level[lno].mex;
                    level[lno].mex = level[lno].down_bf.size();
                    cout<<"size = "<<level[lno].mex;
                    for(int j=0; j<level[lno].down_bf.size(); j++)
                    {
                        if(level[lno].down_bf[j].st.size()==0)
                        {
                            level[lno].mex = j;
                            break;
                        }
                    }
                    cout<<", new mex = "<<level[lno].mex<<endl<<endl;
                }
                
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

#endif
