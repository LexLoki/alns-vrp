#ifndef vrp_hpp
#define vrp_hpp
#include <iostream>

class VRP{
    int N, M;           /// Number of vertices and vehicles
    float **dist;       /// Matrix of distances
    float *dems;        /// Array of demands
    std::string name;   /// Name of instance
public:
    VRP(std::string name, float **dist, float *dems, int dimension);
    ~VRP();
    void print();
};

#endif /* vrp.hpp */