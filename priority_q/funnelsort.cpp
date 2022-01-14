#include<vector>
#include<iostream>
#include<cmath>
#define INF 100000007 
#define ll long long
typedef long long T;
using namespace std;
/*class circ_buffer{
	T *data;
	ll start;
	ll end;
	ll cur_elems;
	ll num_elems;
public:
	circ_buffer(ll _num_elems){
		num_elems = _num_elems;
		data = (T *)malloc(sizeof(T)*num_elems);
		start = 0;
		end = 0;
	}
	void reset(){
		start=0;
		end=0;
		cur_elems=0;
	}
	int is_full(){
		if(cur_elems == num_elems){
			return 1;
		}
		return 0;
	}
	int is_empty(){
		return cur_elems==0;
	}
	void push(T elem){
		if(is_full()){
			start = (start+1)%num_elems;
			end = (end+1)%num_elems;
			*(data+end)=elem;
			return;
		}
		end = (end+1)%num_elems;
		*(data+end)=elem;
		cur_elems++;
	}
	T pop(){
		if(!is_empty()){
			T pop_el = *(data + end);
			if(end==0) end = num_elems-1;
			else (end)--;
			cur_elems--;
			return pop_el;
		}
		return -INF;
	}
	vector<T> to_vector(){
		vector<T> temp;
		ll it = start;
		while(it!=end){
			temp.push_back(*(data+it));
			it++;
		}
		return temp;
	}
	ll ret_size(){
		return cur_elems;
	}
	void print_elems(){
		auto i = start;
		while(i%num_elems!=end){
			cout<<*(data + i%num_elems);
			i++;
		}
	}
};*/
class circ_buffer{
public:
	vector<T> data;
	ll cur_elems;
	ll num_elems;
	void push(T elem){
		data.push_back(elem);
	}
	T pop(){
		if(!is_empty()){
			T temp = data[data.size()-1];
			data.pop_back();
			return temp;
		} 
		return -INF;
	}
	ll ret_size(){
		return data.size();
	}
	void print_elems(){
		for(auto x: data) cout<<x<<" ";
	}
	int is_empty(){
		return data.size()==0;
	}
	void reset(){
		delete(&data);
		data = *(new vector<T>());
	}
	circ_buffer(){
		data = *(new vector<T>());
	}
	circ_buffer(ll s){
		data = *(new vector<T>());
	}
	//T& operator [](int i){return (*data)[i];}
};

class funnel{
	ll k;
	vector<funnel *> left_funnels;
	vector<circ_buffer *> in_buffers;
	funnel * right_funnel;
	vector<circ_buffer *> circ_buffers;
	circ_buffer * out_buffer;
	void create_funnels(){
		cout<<"Create_funnels "<<k<<"\n"; //debug
		ll no_fun = ceil(sqrt(k));
		ll rtk1 = floor(sqrt(k));
		ll rtk2 = k-rtk1 *(no_fun-1);
		ll i=0;
		for(; i<no_fun-1; i++){
			cout<<"loop1\n";
			auto f = new funnel(rtk1);
			for(int j = i*rtk1; j<(i+1)*rtk1; j++){
				f->in_buffers.push_back(in_buffers[j]);
			}
			f->out_buffer = circ_buffers[i];	
			left_funnels.push_back(f);
			cout<<"Loop1 end";
		}
		auto f = new funnel(rtk2);
		for(int j = i*rtk1; j<i*rtk1 + rtk2;j++) f->in_buffers.push_back(in_buffers[j]);
		f->out_buffer = circ_buffers[i];
		left_funnels.push_back(f);
		auto f2 = new funnel(no_fun);
		for(auto x : left_funnels) f2->in_buffers.push_back(x->out_buffer);
		f2->out_buffer = out_buffer;
		right_funnel = f2;
		cout<<"Create funnel end "<<k<<"\n";
		return;
	}
	void create_buffers(){
		cout<<"Create buffer\n";
		ll no_buf = ceil(sqrt(k));
		for(ll i =0; i<no_buf; i++){
			circ_buffers.push_back(new circ_buffer(ceil(2*sqrt(k)*sqrt(k)*sqrt(k))));
		}	
		cout<<"Create buffer end\n";
		return;
	}
public:
	funnel(ll _k){
		cout<<"Const\n";
		k=_k;
		create_buffers();
		if(k>2)
			create_funnels();
	}
	funnel(ll _k, vector<circ_buffer *> in_bufs){
		cout<<"Const2\n";
		init_out_buf();
		k = _k;
		create_buffers();
		init_in_buf(in_bufs);
		if(k>2)
			create_funnels();
	}
	void sort(){
		cout<<"sort funcn inner cout-----------"<<k<<"--------\n"; //debug
		if(k==2){
			ll x=0,y=0;
			if(!in_buffers[0]->is_empty() && !in_buffers[1]->is_empty())x = in_buffers[0]->pop(), y = in_buffers[1]->pop();		
			while(!in_buffers[0]->is_empty() && !in_buffers[1]->is_empty()){	
				cout<<"base sort loop1\n";
				if(x>y) {
					out_buffer->push(x); x = in_buffers[0]->pop(); 
				}else{
					out_buffer->push(y); y = in_buffers[1]->pop();
				}
				cout<<"Base sort loop1 end\n";
			}
			/*if(x!=-INF && y!= -INF){
				if(x>y) out_buffer->push(x), out_buffer->push(y);
				else out_buffer->push(y), out_buffer->push(x);
				x= -INF, y= -INF;
			}*/
			if(x!=-INF) out_buffer->push(x);
			if(y!=-INF) out_buffer->push(y);
			for(int i =0; i<2; i++){
				while(!(in_buffers[i]->is_empty())){
					cout<<"base sort loop1\n";
					out_buffer->push(in_buffers[i]->pop());
					cout<<"base sort loop2\n";
				}
			}
			/*while(x<in_buffers[0]->ret_size() && y <in_buffers[1]->ret_size()){
				if((*(in_buffers[0]))[x]< (*(in_buffers[1]))[y]) out_buffer->push((*(in_buffers[0]))[x]), x++;
				else out_buffer->push((*(in_buffers[1]))[y]), y++;
			}
			while(x<in_buffers[0]->ret_size()) out_buffer->push((*(in_buffers[0]))[x]), x++;
			while(y<in_buffers[1]->ret_size()) out_buffer->push((*(in_buffers[1]))[y]), y++;
		*/
		/*	while(x!=(in_buffers[0]->ret_size())&&y!=(in_buffers[1]->ret_size())){
				if(in_buffers[0]->data[x]<in_buffers[1]->data[y]) out_buffer->push(in_buffers[0]->data[x]), x++;
				else if(in_buffers[0]->data[x]>=in_buffers[1]->data[y]) out_buffer->push(in_buffers[1]->data[y]), y++;
			}
			while(x!=(in_buffers[0]->ret_size()))out_buffer->push(in_buffers[0]->data[x]), x++;
		       	while(y!=(in_buffers[1]->ret_size()))out_buffer->push(in_buffers[1]->data[y]), y++;*/
		}
		else{
			bool c = true;
			while(c){
				cout<<"k!=2 while loop\n";
				int i =0;
				for(auto x: in_buffers){
					if(!x->is_empty()){
						c=true; 
						left_funnels[i]->sort();	
						break;
					}else{c=false;}
				}
				for(ll i =0; i<ceil(sqrt(k)); i++){
					cout<<"i: "<<i<<endl;
					left_funnels[i]->sort();
					cout<<"-----------loop print elems--------------\n";
					left_funnels[i]->out_buffer->print_elems();
					cout<<"------------------------------------------\n";
				}
				right_funnel->sort();
			}
		}
		cout<<"sort funcn inner cout end -----------"<<k<<"------------\n"; //debug
	}
	/*void init_in_buf(vector<vector<T>> &in_bufs){
		for(auto x : in_bufs) in_buffers.push_back(&x);
	}*/
	void init_in_buf(vector<circ_buffer *> in_bufs){
		for(auto x : in_bufs) in_buffers.push_back(x);
	}
	void print_out_buf(){
		while(!out_buffer->is_empty())
			cout<<out_buffer->pop()<<" ";
	}
	void init_out_buf(){
	// use only for first funnel ?
		out_buffer = new circ_buffer(k*k*k);
	}
	void debug(){
		for(auto x: in_buffers) x->print_elems();
		cout<<"\n#############################\n";
		for(auto x: left_funnels) for(auto y: x-> in_buffers) y->print_elems();
	}
	
};
int main_test_buff(){
	auto c = new circ_buffer(9);
	c->push(1);
	c->push(2);
	c->push(3);
	c->push(4);
	cout<<c->ret_size()<<endl;
	cout<<c->pop()<<endl;
	cout<<c->ret_size()<<endl;
	cout<<c->pop()<<endl;
	cout<<c->pop()<<endl;
	cout<<c->pop()<<endl;
	cout<<c->is_empty()<<endl;
	return 0;

}

int main_test_sort(){
	cout<<"Main\n";
	vector<circ_buffer *> test;
	cout<<"Creating circ buffers\n";
	auto c1 = new circ_buffer(9);
	auto c2 = new circ_buffer(9);
	auto c3 = new circ_buffer(9);
	auto c4 = new circ_buffer(9);
	cout<<"Pushing elements\n";
/*	c1->push(2);
	c1->push(5);
	c1->push(11);
	c1->push(24);
	c1->push(27);
	c1->push(30);
	c1->push(58);
	c1->push(101);
	c1->push(91);
	c2->push(3);
	c2->push(10);
	c2->push(17);
	c2->push(21);
	c2->push(25);
	c2->push(33);
	c2->push(52);
	c2->push(1221);
	c2->push(97);
	c3->push(45);
	c3->push(63);
	c3->push(85);
	c3->push(81);
	c3->push(15);
	c3->push(156);
	c3->push(58);
	c3->push(29);
	c3->push(901);
	c4->push(45);
	c4->push(63);
	c4->push(85);
	c4->push(81);
	c4->push(15);
	c4->push(156);
	c4->push(58);
	c4->push(29);
	c4->push(901);
*/
	c1->push(1);
	c1->push(2);
	c1->push(3);
	c1->push(4);
	c1->push(5);
	c1->push(6);
	c1->push(7);
	c1->push(8);
	c1->push(9);
	c2->push(10);
	c2->push(11);
	c2->push(12);
	c2->push(13);
	c2->push(14);
	c2->push(15);
	c2->push(16);
	c2->push(17);
	c2->push(18);
	c3->push(19);
	c3->push(20);
	c3->push(21);
	c3->push(22);
	c3->push(23);
	c3->push(24);
	c3->push(25);
	c3->push(26);
	c3->push(27);
	c4->push(28);
	c4->push(29);
	c4->push(30);
	c4->push(31);
	c4->push(32);
	c4->push(33);
	c4->push(34);
	c4->push(35);
	c4->push(36);
	
	test.push_back(c1);
	test.push_back(c2);
	test.push_back(c3);
	test.push_back(c4);
	cout<<"Main:- Creating funnel\n";
	auto f = new funnel(4, test);
	cout<<"Debug\n";
	f->debug();
	cout<<"Calling sort\n";
	f->sort();
	cout<<"Calling print\n";
	f->print_out_buf();
	cout<<"NoErrors!\n";
}

int main(){
	main_test_sort();
	return 0;
}


