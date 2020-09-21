#include "cvrp.hpp"
#include <iostream>
#include <list> 
#include <cmath>

using namespace std;

CVRP::CVRP(string name, float **dist, float *dems, int dimension, int capacity, int depot) : 
    VRP(name, dist, dems, dimension), C(capacity), dep(depot){
        this->dist = dist;
        this->dems = dems;
    }

void CVRP::print(){
    VRP::print();
    cout << "Capacity: " << C << endl;
    cout << "Depot: " << dep << endl;
}

list<list<int> *> * CVRP::getPetal(float **pos, int n, int dep, int cap, float *dems){
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
    angles[dep] = 0;
    //indexes in ascending angle order relative to depot
    sort(index,index+n-1,[&angles](int i,int j){return angles[i]<angles[j];});

    //now create route with indexes
    list<list<int> *> *routes = new list<list<int> *>();
    list<int> *route = new list<int>(); route->push_back(dep);
    int idx;
    float rem = cap;
    for(i=0;i<n-1;i++){
        idx = index[i];
        if(dems[idx]>rem){
            route->push_back(dep); rem = cap;
            routes->push_back(route);
            route = new list<int>();
            route->push_back(dep);
        }
        route->push_back(idx);
        rem -= dems[idx];
    }
    if(route->size()>1){
        route->push_back(dep);
        routes->push_back(route);
    }
    else{
        delete route;
    }
    return routes;
    //lets clear
    /*
    i=1;
    for(auto it = routes->begin(); it != routes->end(); ++it){
        route = *it;
        cout << "Route " << i++ << ":" << endl;
        for(auto it2 = route->begin(); it2 != route->end(); ++it2){
            cout << " (" << *it2 << ", " << angles[*it2] << ")";
        }
        cout << endl;
        delete route;
    }
    delete routes;
    //return routes
    */
}