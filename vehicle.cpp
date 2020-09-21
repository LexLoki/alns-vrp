#include "vehicle.hpp"
#include <iostream>
#include <iterator>
#include <list> 
#include <cmath>

using namespace std;

Vehicle::Vehicle(int cap) : cap(cap), load(0), cost(0), count(0) {
    route = new list<int>();
}

Vehicle::Vehicle(const Vehicle &veh){
    this->cap = veh.cap;
    this->load = veh.load;
    this->count = veh.count;
    this->load = veh.load;
    this->cost = veh.cost;
    this->route = new list<int>();
    for(auto at = veh.route->begin(); at != veh.route->end(); at++){
        this->route->push_back(*at);
    }
}

void Vehicle::setRoute(list<int> *r, float **dist, float *loads){
    route = r;
    load = 0;
    count = 0;
    cost = 0;
    //cout << "route ";
    list<int>::iterator it = r->begin();
    int last = *it, curr;
    for(it = next(it); it != prev(r->end()); it++){
        curr = *it;
        load += loads[curr];
        //cout << curr << " ";
        cost += dist[last][curr];
        count++;
        last = curr;
    }
    cost += dist[last][*it];
    //cout << endl;
}

bool Vehicle::empty(){ return load==0; }

int Vehicle::removeNode(list<int>::iterator it, float **dist, float *load)
{
    //TODO:
    //implicit dist and load
    int pv = *prev(it), mid = *(it), nt = *next(it);
    route->erase(it);
    cost -= (dist[pv][mid] + dist[mid][nt]) - dist[pv][nt];
    count--;
    this->load -= load[mid];
    return mid;
}

int Vehicle::removeNode(int index, float **dist, float *load)
{
    list<int>::iterator it = route->begin();
    advance(it,index+1);
    return this->removeNode(it, dist, load);
    /*
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
    */
    return 0;
}

int Vehicle::getNode(int index){
    return *next(route->begin(),1+index);
}

float Vehicle::addNode(list<int>::iterator it, int nd, float **dist, float *load){
    int idPrev = *prev(it), idCurr = *it;
    float diff = dist[idPrev][nd] + dist[nd][idCurr] - dist[idPrev][idCurr];
    cost += diff;
    this->load += load[nd];
    count++;
    route->insert(it, nd);
    return diff;
}

bool Vehicle::canFit(float load){
    return this->load + load <= cap;
}