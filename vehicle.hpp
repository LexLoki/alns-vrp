#ifndef cvrpveh_hpp
#define cvrpveh_hpp

#include <list> 
#include <iostream>

class Vehicle{
    int cap; //capacity
public:
    list<int> *route;
    int count;
    int load;
    float cost;

    Vehicle(int cap);
    void setRoute(list<int> *r);
    bool empty();
    void removeNode(int index);
};

#endif