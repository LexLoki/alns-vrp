#include "solution.hpp"
#include <iostream>
#include <list> 
#include <cmath>

using namespace std;

Solution::Solution(list<list<int> *>& routes, int cap) : veh_cap(cap) {
    veh_used = routes.size(); //verify
    vehicles = new Vehicle*[veh_cap];
    int i=0;
    for(auto it = routes->begin(); it != routes->end(); it++){
        vehicles[i] = new Vehicle(cap);
        vehicles[i]->setRoute(*it);
    }
    while(i<veh_total){
        vehicles[i++] = new Vechile(cap);
    }
}

void Solution::removeVehicle(int index){
    cost -= vehicles[index]->cost;
    nodes_count -= vehicles[index]->count;
    vehicles[index] = vehicles[--veh_used];
}

void Solution::removeNode(int index){
    Vehicle *veh;
    for(int i=0;i<veh_used;i++)
    {
        veh = vehicles[i];
        if(index < veh->count)
        {
            if(veh->count == 1){
                removeVehicle(i);
            }
            else{
                int prev_cost = veh->cost;
                veh->removeNode(index);
                this->cost -= prev_cost - veh->cost;
                nodes_count--;
            }
            nodes--;
            break;
        }
    }
}