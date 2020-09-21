#ifndef cvrpsol_hpp
#define cvrpsol_hpp

#include "vehicle.hpp"
#include "cvrp.hpp"
#include <iostream>

class Solution{
    //list<Vehicle *> * vehicles;
    int veh_total;
    //
    int veh_cap;
public:

    //reference to instance
    CVRP *instance;

    Vehicle **vehicles;
    float cost;
    int veh_used;
    int nodes_count;

    std::list<int> nodes_bank;

    Solution();
    Solution(const Solution &sol);
    Solution(CVRP *instance, std::list<std::list<int> *>& routes, int cap);
    bool valid();
    void removeVehicle(int index);
    int removeNode(int index);
    void addNode(int vehIndex, std::list<int>::iterator routePos, int node);
};

#endif