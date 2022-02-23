#include "classes.h"
#include "PQ_func.h"
#include "push.h"
#include "pull.h"

int main()
{
    priority_q a;
    for(int i = 1; i <= 20; i++) 
    {
        //cout<<"\nInserting "<<i<<"...\n";
        a.insert(i);
        //a.traverse(0);
    }
cout<<"yes"<<endl;
    for(int i = 1; i <= 10; i++)
    {
        cout<<endl<<a.del_min()<<" s"<<endl;
        // a.traverse(0);
    }

    for(int i = 30; i <= 37; i++) 
    {
        cout<<"\nInserting "<<i<<"...\n";
        a.insert(i);
        a.traverse(0);
        cout<<"\ndel_bf "<<i<<"...\n";
    for(ll x: a.del_bf)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    }

    for(int i = 1; i <= 17; i++)
    {
        cout<<a.del_min()<<" s"<<endl;
    }
    cout<<endl;
    // for(int i = 1; i <= 4; i++) cout<<"s "<<a.del_min()<<" ";
    // cout<<endl;
    /*for(int i = 30; i >= 20; i--)
    {
        a.insert(i);
    }
    for(int i = 1; i <= 17; i++) a.del_min();*/
    return 0;
}
