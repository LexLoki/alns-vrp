#ifndef cvrpsol_hpp
#define cvrpsol_hpp

#include "vehicle.hpp"
#include <list> 
#include <iostream>

class Solution{
    //list<Vehicle *> * vehicles;
    Vehicle **vehicles;
    int veh_total;
    int veh_used;
    float cost;
    int nodes_count;
    //
    int veh_cap;
public:
    Solution(list<list<int> *>& routes, int cap);
    removeVehicle(int index);
    removeNode(int index);
};

#endif