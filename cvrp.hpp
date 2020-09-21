#ifndef cvrp_hpp
#define cvrp_hpp

#include "vrp.hpp"
#include <list> 

class CVRP : public VRP{
    int C; //vehicle capacity
    int dep; //depot index
public:

    float **dist, *dems;

    CVRP(std::string name, float **dist, float *dems, int dimension, int capacity, int depot);
    void print();

    static std::list<std::list<int>*> *getPetal(float **pos, int n, int dep, int cap, float *dems);
};

#endif