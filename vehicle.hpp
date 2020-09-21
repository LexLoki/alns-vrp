#ifndef cvrpveh_hpp
#define cvrpveh_hpp

#include <list> 
#include <iostream>

/** Represents a route with load/cost information,
 * 
 */
class Vehicle{
    float cap; //capacity
public:
    std::list<int> *route;
    int count;
    int load;
    float cost;

    Vehicle(int cap);
    Vehicle(const Vehicle &veh);

    void setRoute(std::list<int> *r, float **dist, float *loads);
    bool empty();

    int removeNode(int index, float **dist, float *load);
    int removeNode(std::list<int>::iterator it, float **dist, float *load);

    int getNode(int index);
    float addNode(std::list<int>::iterator it, int nd, float **dist, float *load);

    bool canFit(float load);


    /*would improve
    list<int>::iterator begin(); //begin+1
    list<int>::iterator end(); //end-1 !?
    */
};

#endif