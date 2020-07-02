#include "vehicle.hpp"
#include <iostream>
#include <list> 
#include <cmath>

using namespace std;

Vehicle::Vehicle(int cap) : cap(cap) load(0) {}

void Vehicle::setRoute(list<int> *r){
    //TODO: fill for load
    route = r;
}

bool Vehice::empty(){ return load==0; }

void Vehicle::removeNode(int index)
{
    //todo: relate dist matrix somewhere
    float **dist;
    auto it; //fix this of course
    int place = index;
    for(it = route->begin(); place--; it++);
    int prev = *(it++), mid = *(it++), next = *it;

    //route->remove(index+1); FIX
    
    //cost difference
    cost -= (dist[prev][mid] + dist[mid][next]) - dist[prev][next];

    //TODO: lower load
}