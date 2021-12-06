#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll>* vec_ptr;
typedef long long datatype;

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
	ll fir, down_bf_cnt;
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
	void desc_sort(vector<ll>&);
	void sort(vector<ll>&);
};

void priority_q::push(ll lno, vec_ptr a) //level[lno] access, push X elements to level lno
{
sort(a);
	ll ind = 0;
	for(ll i = level[lno].fir; i != -1; i = level[lno].down_bf[i].next)
	{
		while(ind < a->size() && a->at(ind) < level[lno].down_bf[i].pivot)
		{
			(*(level[lno].down_bf[i].st)).push_back(a->at(ind));
			ind++;
			if((*(level[lno].down_bf[i].st)).size() == level[lno].down_sz+1)
			{
//split(); inc down_bf_cnt
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

void priority_q::pull(ll lno, vec_ptr a)	//pull elements from level lno
{
	ll ind = level[lno].fir;
	ll min_sz = (level[lno].down_sz + 1)/2;
	if(level[lno].down_bf_cnt > 0 && (*(level[lno].down_bf[ind].st)).size() >= min_sz)
	{
desc_sort((level[lno].down_bf[ind].st));
		//take away least min_sz elements & put to a
		//leave remaining in the buffer
		while((*a).size() < min_sz)
		{
			(*a).push_back( ( *( level[lno].down_bf[ind].st ) ) .back() );
			( *( level[lno].down_bf[ind].st ) ).pop_back();
			level[lno].cnt--;
		}
		if(( *( level[lno].down_bf[ind].st ) ).size() == 0)
		{
			level[lno].fir = level[lno].down_bf[ind].next;
			level[lno].down_bf_cnt--;
		}
	}
	else if(level[lno].down_bf_cnt > 1)
	{
		//pull first buffer fully
		while( (*(level[lno].down_bf[ind].st)).size() > 0)
		{
			(*a).push_back( ( *( level[lno].down_bf[ind].st ) ) .back() );
			( *( level[lno].down_bf[ind].st ) ).pop_back();
			level[lno].cnt--;
		}
		/* Removing the first down_bf from the list */
		level[lno].fir = level[lno].down_bf[ind].next;
		level[lno].down_bf_cnt--;
		ind = level[lno].fir; //ind points to the current first down_bf
	//sort second buffer
desc_sort((level[lno].down_bf[ind].st));
		//take reqd no of elements from second buffer
		while((*a).size() < min_sz)
		{
			(*a).push_back( ( *( level[lno].down_bf[ind].st ) ) .back() );
			( *( level[lno].down_bf[ind].st ) ).pop_back();
			level[lno].cnt--;
		}
		if(( *( level[lno].down_bf[ind].st ) ).size() == 0)
		{
			level[lno].fir = level[lno].down_bf[ind].next;
			level[lno].down_bf_cnt--;
		}
	}
	else
	{
		for(ll tt : *(level[lno].down_bf[ind].st))
		{
			(*a).push_back(tt);
		}
		(*(level[lno].down_bf[ind].st)).clear();
		level[lno].down_bf_cnt = 0;
		level[lno].cnt = 0;
		if(lno == level.size()-1)
		{
			//take elements from upbuffer
			//sort and take enough to fill downbuffer
			//if not enough, empty full upbuffer to down_bf
			//return
		}
		vec_ptr b;
		pull(lno+1, b);
		/*if(level[lno].cnt < min_sz)
		{
			//take all values from this level
			//put into prev level
			//clear this level
			//return
		}
		else
		{*/
			ll u_sz = level[lno].up_bf.size();
			for(ll tt : level[lno].up_bf)
			{
				(*b).push_back(tt);
			}
			level[lno].up_bf.clear();
//sort b and refill the first U elements into the up_bf;
sort(b);
			ll how_many_pulled = 0;
			for(ll i=0; (*a).size() < min_sz && i < b->size(); i++)	//taking least [X]-Y keys and putting into a
			{
				(*a).push_back(b->at(i));
				how_many_pulled++;
			}

			ll count = 0;
			for(ll i=ll((*b).size())-1; i>=how_many_pulled && count < u_sz; i--, count++)		//refilling upbuffer
			{
				level[lno].up_bf.push_back(b->at(i));
				(*b).pop_back();
			}

			if(((*b).size() - how_many_pulled) == 0)
				return;
			/* Refilling the first down_buffer of lno, size = rem & updating cnt of lno*/
			level[lno].cnt = (*b).size() - how_many_pulled;
			ll rem = ((*b).size() - how_many_pulled) % min_sz;		//No of elements to be put in down_bf[0]
			if(!rem)
				rem = min_sz;
			level[lno].down_bf_cnt++;
			ll ar_pos = how_many_pulled;
			ll curr_bf = 0;
			level[lno].fir = curr_bf;
			for(ll i=0; i<rem; i++)
			{
				(*(level[lno].down_bf[curr_bf].st)).push_back(b->at(ar_pos));
				ar_pos++;
			}
			/* Refilling the remaining down_buffers of lno */
			ll how_many_bfs = ((*b).size()-how_many_pulled-rem) / min_sz;
			level[lno].down_bf_cnt += how_many_bfs; //no of down_bfs = first + how_many_bfs
			for(ll i=1; i<=how_many_bfs; i++)
			{
				level[lno].down_bf[curr_bf].next = i; //next of previous down_bf = i
				curr_bf = i;
				for(ll j=0; j<min_sz; j++)
				{
					(*(level[lno].down_bf[curr_bf].st)).push_back(b->at(ar_pos));
					ar_pos++;
				}
				level[lno].down_bf[curr_bf].next = -1;//next of the new down_bf = -1
			}
		// }
	}
}

int main()
{

    return 0;
}
