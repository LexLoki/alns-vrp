#include "cvrp.hpp"
#include <iostream>
#include <bits/stdc++.h> 
#include <math>

using namespace std;

CVRP::CVRP(string name, float **dist, float *dems, int dimension, int capacity, int depot) : 
    VRP(name, dist, dems, dimension), C(capacity), dep(depot){}

void CVRP::print(){
    VRP::print();
    cout << "Capacity: " << C << endl;
    cout << "Depot: " << dep << endl;
}

static void CVRP::getPetal(float **pos, int n, int dep, int cap, int *dems){
    int i,j;
    float *angles = new float[n]; //{w/e, angles ...}
    int *index = new int[n-1];    //{1,2,3,4,...,n-1} (0 out)
    float depx = pos[dep][0], depy = pos[dep][1];
    j=0;
    for(i=0;i<n;i++){
        if(i != dep){
            angles[i] = atan2f(pos[i][0] - depx, pos[i][1] - depy);
            index[j++] = i;
        }
    }
    sort(index,index+n-1,[&](int i,int j){return angles[A[i]]<angles[A[j]];});
    //now create route with indexes
}