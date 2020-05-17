#ifndef cvrp_hpp
#define cvrp_hpp

#include "vrp.hpp"

class CVRP : public VRP{
    int C; //vehicle capacity
public:
    CVRP(std::string name, float **dist, float *dems, int dimension, int capacity);
    void print();
};

#endif