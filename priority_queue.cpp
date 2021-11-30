#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll>* vec_ptr;

const ll c = 12;

class bf
{
public:
	vec_ptr st;
	ll next, pivot;
};

class lvl
{
public:
	vector<ll> up_bf;
	vector<bf> down_bf;
	vec_ptr fir;
	/*
	up_sz   : max size of up buffer (X^3/2)
	down_sz : max size of down buffer (except first one) (2*X-1)
	down_cnt: max number of downbuffers (X^1/2 + 1)
	*/
	ll up_sz, down_sz, down_cnt;
};

class priority_queue
{
public:
	vector<lvl> level;
	vector<ll> ins_bf, del_bf;
	void insert(ll val);
	ll del_min();
	void push(ll, vec_ptr);
	void pull(ll, vec_ptr);
};

void priority_queue::push(ll lno, vec_ptr a) //level[lno] access
{
//sort(a);
	ll ind = 0;
	vec_ptr tr = fir;
	for(ll i = 0; i < level[lno].down_bf.size(); i++)
	{
		while(ind < a->size() && a->at(ind) < level[lno].down_bf[i].pivot)
		{
			(*(level[lno].down_bf[i].st)).push_back(a->at(ind));
			ind++;
			if(*(level[lno].down_bf[i].st).size() == level[lno].down_bf[i].down_sz+1)
			{
//split();
//if(level[lno].down_bf[i].size() == level[lno].down_bf[i].down_cnt+1)
//{
//push final dbf into upbf
//	if(level[lno].up_bf.size() > level[lno].up_sz)
//     recursive push(X^3/2 elements)
//} 
			}
		}
	}
	if(ind != a->size())
	{
		while(ind < a->size())
		{
			level[lno].up_bf.push_back(a->at(ind));
			ind++;
		}
//	if(level[lno].up_bf.size() > level[lno].up_sz)
//     recursive push(X^3/2 elements)
	}
}

void priority_queue::pull(ll lno, vec_ptr a)
{
	ll nxt = lno+1;

}

int main()
{
    
    return 0;
}