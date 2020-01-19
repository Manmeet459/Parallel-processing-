#include<bits/stdc++.h>

using namespace std;

std::vector<long long int > start_time;
std::vector<int> thred;
std::vector<long long int> process_time;
std::vector<int> free_thread;


void swap( int *a, int *b){
    int c=*a;
    *a=*b;  
    *b=c;
}


void shiftdown(int i){
    
    int parent=i;
    int left_Child=2*i+1;
    int right_child=2*i+2;
    
    if( left_Child<process_time.size() ) {
        
        if( process_time[free_thread[left_Child]] < process_time[free_thread[parent]] ){
            parent=left_Child;    
        }
        
        if( process_time[free_thread[left_Child]] == process_time[free_thread[parent]] && free_thread[left_Child]<free_thread[parent] ){
            parent=left_Child;    
        }
        
        
    }
    
    if( right_child<process_time.size() ){
        
        if( process_time[free_thread[right_child]] < process_time[free_thread[parent]] ){
            parent=right_child;   
        }
        
        if( process_time[free_thread[right_child]] == process_time[free_thread[parent]] && free_thread[right_child]<free_thread[parent] ){
            parent=right_child;   
        }
        
    }
    
    if(parent!=i){
        swap(&free_thread[i], &free_thread[parent]);
        shiftdown(parent);
    }
}


void make_heap(){
    int size=process_time.size();
    for(int i=size/2; i>=0; i--){
        shiftdown(i);
    }
}


void make_thread(int arr[], int n, int m){
    
    for(int i=0; i<n; i++){
        
        if(i>=m){
            break;
        }
        
        start_time.push_back(0);
        thred.push_back(i);
        free_thread.push_back(i);
        process_time.push_back(arr[i]);
    }
}

void parllel_process(int arr[], int n, int m ){
    
    make_thread(arr, n, m);
    make_heap();
    
    for(int i=n; i<m; i++){
        
        thred.push_back(free_thread[0]);
        long long int st_time=process_time[free_thread[0]];
        start_time.push_back(st_time);
        
        process_time[free_thread[0]]+=arr[i];

        shiftdown(0);
    }
    
    for(int i=0; i<thred.size(); i++){
        std::cout << thred[i] <<" "<<start_time[i]<< std::endl;
    }

}


int main(){
    
    // n is number of processor available
    // m is number of jobs to done
    // arr[i] is the time required to do ith job 
    int m, n;
    cin>>n; 
    cin>>m; 
    int arr[m];
    for(int i=0; i<m; i++){
        cin>>arr[i];
    }
    
    parllel_process(arr,n,m);    

    return 0;
}


