#include<bits/stdc++.h>
#include<vector>
using namespace std;
bool debug = false;
float medfive(vector<float> arr){

     int size = arr.size();
        switch(size){
            case 1 : return arr[0];break;
            case 2 : return ((float)arr[0]+(float)arr[1])/2.0 ; break;
            case 3 : return arr[1];break;
            case 4 : return ((float)arr[1]+(float)arr[2])/2.0;break;
            case 5 : return arr[2];break;
            default : cout<<"invalid array size"; return -1;
        }
    
}
float MedofMed(vector<float> arr){
    
    int size = arr.size();
    if(size < 5){
        switch(size){
            case 1 : return arr[0];break;
            case 2 : return ((float)arr[0]+(float)arr[1])/2.0 ;break;
            case 3 : sort(arr.begin(),arr.end()); return arr[1];break;
            case 4 : sort(arr.begin(),arr.end()); return ((float)arr[1]+(float)arr[2])/2.0;break;
            default : cout<<"invalid array size"; return -1;
        }
    }
     vector<float> newarr; 
    //5 element medians 
    int i=0;
    for(i=0;i<size;i+=5){
        vector<float> subarr;
       for(int j=i;j<i+5 && j<size;j++){
          subarr.push_back(arr[j]);
       }
       sort(subarr.begin(),subarr.end());
       float med = medfive(subarr);
       newarr.push_back(med);
       
    }
    if(debug){
         cout<<"The newarr is "; 
         for(int k=0;k<newarr.size();k++){
           cout<<newarr[k]<<" ";}
         cout<<"\n";}
  
    return MedofMed(newarr);
}
float findMedian(vector<int> arr,vector<int> original)
{
   int lessthan=0;
   int morethan=0;
   int equalto=0;
   vector<float> temparr;
   for(int i=0;i<arr.size();i++)
    {
        float x = (float)arr[i];
        temparr.push_back(x);
    }
    float median = MedofMed(temparr);
    if(debug)
    cout<<"The middle median is "<<median<<endl;
    for(int i=0;i<original.size();i++){
        if(original[i]<median)
         lessthan++;
         if(original[i]>median)
         morethan++;
         if(original[i] == median)
         equalto++;
    }

    int rank = lessthan+1;
   if(lessthan==morethan)
    return median;
    else{
        if(original.size()%2 == 1 && equalto>0 && (equalto-1-morethan+lessthan)%2 == 0 && (morethan+equalto-1-lessthan)%2 == 0)
          {
              return median;
          }
        
         else if(original.size()%2 == 0 && equalto>0 && (equalto-morethan+lessthan)%2 == 0 && (morethan+equalto-lessthan)%2 == 0)
          return median;
    }
    if(lessthan > morethan){
        vector<int> LT;
        for(int i=0;i<arr.size();i++){
        if(arr[i]<=median)
         LT.push_back(arr[i]);
    }
      return findMedian(LT,original);
    }
    else if(morethan >lessthan){
        vector<int> MT;
        for(int i=0;i<arr.size();i++){
        if(arr[i]>=median)
         MT.push_back(arr[i]);
    }
       return findMedian(MT,original);
    }
   
}

int main()
{
    vector<int> arr;
    int size;
    cin>>size;
    for(int i=0;i<size;i++)
    {
        int num;
        cin>>num;
        arr.push_back(num);
    }
    if(debug){
        cout<<"Input received is ";
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<" ";
        }
    }
    float median = 0;
    median = findMedian(arr,arr);
    cout<<"The median is "<<median;
  
    return 0;
}
// vector stl - contiguous memory 
//https://stackoverflow.com/questions/849168/are-stdvector-elements-guaranteed-to-be-contiguous