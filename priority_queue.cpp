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
	ll fir;
	/*
	up_sz   : max size of up buffer (X^3/2)
	down_sz : max size of down buffer (except first one) (2*X-1)
	down_cnt: max number of downbuffers (X^1/2 + 1)
	*/
	ll up_sz, down_sz, down_cnt;
	ll cnt;
};

class priority_q
{
public:
	vector<lvl> level;
	vector<ll> ins_bf, del_bf;
	void insert(ll val);
	ll del_min();
	void push(ll, vec_ptr);
	void pull(ll, vec_ptr);
};

void priority_q::push(ll lno, vec_ptr a) //level[lno] access, push X elements to level lno
{
//sort(a);
	ll ind = 0;
	for(ll i = level[lno].fir; i != -1; i = level[lno].down_bf[i].next)
	{
		while(ind < a->size() && a->at(ind) < level[lno].down_bf[i].pivot)
		{
			(*(level[lno].down_bf[i].st)).push_back(a->at(ind));
			ind++;
			if((*(level[lno].down_bf[i].st)).size() == level[lno].down_sz+1)
			{
//split();
//if(level[lno].down_bf[i].size() == level[lno].down_bf[i].down_cnt+1)
//{
//push final dbf into upbf
//	if(level[lno].up_bf.size() > level[lno].up_sz)
//     recursive push(X^3/2 elements)
//clear}
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

void priority_q::pull(ll lno, vec_ptr a)	//pull elements from level lno
{
	ll ind = level[lno].fir;
	ll min_sz = (level[lno].down_sz + 1)/2;
	if((*(level[lno].down_bf[ind].st)).size() >= min_sz)
	{
//sort the ind buffer
//take away least min_sz elements & put to a
//leave remaining in the buffer
	}
	else if(level[lno].down_bf.size() > 1)
	{
//pull first buffer fully
//sort second buffer
//take reqd no of elements from second buffer
	}
	else
	{
		for(ll tt : *(level[lno].down_bf[ind].st))
		{
			(*a).push_back(tt);
		}
		(*(level[lno].down_bf[ind].st)).clear();

		//if(lno == last level)
		{
			//take elements from upbuffer
			//sort and take enough to fill downbuffer
			//if not enough, empty full upbuffer to down_bf
			//return
		}
		vec_ptr b;
		pull(lno,b);
		if(level[lno].cnt < min_sz)
		{
			//take all values from this level
			//put into prev level
			//clear this level
			//return
		}
		else
		{
			ll u_sz = level[lno].up_bf.size();
			for(ll tt : level[lno].up_bf)
			{
				(*b).push_back(tt);
			}
			level[lno].up_bf.clear();
//sort(*b);
			ll how_many_removed = 0;
			for(ll i=0; (*a).size() < min_sz; i++)	//taking least [X]-Y keys and putting into a
			{
				(*a).push_back(b->at(i));
				how_many_removed++;
			}

			ll count = 0;
			for(ll i=ll((*b).size())-1; i>=how_many_removed && count < u_sz; i--, count++)		//refilling upbuffer
			{
				level[lno].up_bf.push_back(b->at(i));
				(*b).pop_back();
			}

			if(((*b).size() - how_many_removed) == 0)
				return;

			ll rem = ((*b).size() - how_many_removed) % min_sz;		//No of elements to be put in down_bf[0]
			if(!rem)
				rem = min_sz;
			ll ar_pos = how_many_removed;
			ll curr_bf = 0;
			level[lno].fir = curr_bf;
			for(ll i=0; i<rem; i++)
			{
				(*(level[lno].down_bf[curr_bf].st)).push_back(b->at(ar_pos));
				ar_pos++;
			}

			ll how_many_bfs = ((*b).size()-how_many_removed-rem) / min_sz;
			for(ll i=1; i<=how_many_bfs; i++)
			{
				level[lno].down_bf[curr_bf].next = i;
				curr_bf = i;
				for(ll j=0; j<min_sz; j++)
				{
					(*(level[lno].down_bf[curr_bf].st)).push_back(b->at(ar_pos));
				}
				level[lno].down_bf[curr_bf].next = -1;
			}
		}
	}
}

int main()
{

    return 0;
}
