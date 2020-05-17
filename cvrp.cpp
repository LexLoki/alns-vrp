#include "cvrp.hpp"
#include <iostream>

using namespace std;

CVRP::CVRP(string name, float **dist, float *dems, int dimension, int capacity) : 
    VRP(name, dist, dems, dimension), C(capacity){}

void CVRP::print(){
    VRP::print();
    cout << "Capacity: " << C << endl;
}