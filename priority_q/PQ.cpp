#include "lvl"
using namespace std;

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

    void make_newlvl(ll);
    void push_to_upbf(ll);
};

void priority_q::insert(T val)
{
    if(del_bf.size() < ins_size)
    {
        del_bf.push_back(val);
        return;
    }
    del_bf.push_back(val);
    asc_sort(del_bf);
    ll push_ins_bf = del_bf.back();
    del_bf.pop_back();
    ins_bf.push_back(push_ins_bf);
    if(ins_bf.size() == ins_size)
    {
        push(0, ins_bf);
        ins_bf.clear();
    }
}

T priority_q::del_min()
{
    if(del_bf.size() == 0)
    {
        pull(0, del_bf);
        while(ins_bf.size() > 0)
        {
            del_bf.push_back(ins_bf.back());
            ins_bf.pop_back();
        }
        if(del_bf.size() == 0) return nul;
    }
    desc_sort(del_bf);
    T ret = del_bf.back();
    del_bf.pop_back();
    asc_sort(del_bf);
    while(del_bf.size() > ins_size)
    {
        ins_bf.push_back(del_bf.back());
        del_bf.pop_back();
    }
    return ret;
}

int main()
{
    return 0;
}
