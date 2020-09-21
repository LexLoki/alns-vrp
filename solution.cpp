#include "solution.hpp"
#include <iostream>
#include <list> 
#include <cmath>

using namespace std;

Solution::Solution(){}

Solution::Solution(const Solution &sol){
    this->veh_total = sol.veh_total;
    this->veh_cap = sol.veh_cap;
    this->veh_used = sol.veh_used;
    this->nodes_count = sol.nodes_count;
    this->cost = sol.cost;
    instance = sol.instance;
    vehicles = new Vehicle*[veh_total];
    for(int i=0;i<veh_used;i++)
    {
        vehicles[i] = new Vehicle(*sol.vehicles[i]);
    }
    for(auto it = sol.nodes_bank.begin(); it != sol.nodes_bank.end(); it++){
        nodes_bank.push_back(*it);
    }
}

Solution::Solution(CVRP *instance, list<list<int> *>& routes, int cap) : veh_cap(cap) {
    this->instance = instance;
    veh_total = veh_cap;
    veh_used = routes.size(); //verify
    vehicles = new Vehicle*[veh_cap];
    int i=0;
    nodes_count = 0;
    cost = 0;
    Vehicle *v;
    for(auto it = routes.begin(); it != routes.end(); it++){
        v = new Vehicle(cap);
        v->setRoute(*it,instance->dist,instance->dems);
        nodes_count += v->count;
        cost += v->cost;
        vehicles[i++] = v;
    }
    while(i<veh_total){
        vehicles[i++] = new Vehicle(cap);
    }
}

bool Solution::valid(){
    return !nodes_bank.size();
}

/*
void Solution::print(){
    cout << "Cost: " << cost << endl;
}*/

void Solution::removeVehicle(int index){
    cost -= vehicles[index]->cost;
    nodes_count -= vehicles[index]->count;
    vehicles[index] = vehicles[--veh_used];
}

int Solution::removeNode(int index){
    Vehicle *veh;
    int idx;
    float **dist = instance->dist, *load = instance->dems;
    //cout << index << " : " << veh_used << endl;
    for(int i=0;i<veh_used;i++)
    {
        veh = vehicles[i];
        if(index < veh->count)
        {
            if(veh->count == 1){
                idx = veh->getNode(0);
                removeVehicle(i);
            }
            else{
                int prev_cost = veh->cost;
                idx = veh->removeNode(index, dist, load);
                //cout << prev_cost << ", " << veh->cost << endl; 
                this->cost -= prev_cost - veh->cost;
                nodes_count--;
            }
            return idx;
        }
        index -= veh->count;
    }
    return -1; 
}

void Solution::addNode(int vehIndex, std::list<int>::iterator routePos, int node){
    cost += vehicles[vehIndex]->addNode(routePos, node, instance->dist, instance->dems);
    nodes_count++;
}