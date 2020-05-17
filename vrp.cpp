#include "vrp.hpp"
#include <iostream>

using namespace std;

VRP::VRP(string name, float **dist, float *dems, int dimension) :
    name(name), N(dimension), M(dimension), dist(dist), dems(dems){}

VRP::~VRP(){
    for(int i=0;i<N; delete[] this->dist[i++]);
    delete[] this->dist;
    delete[] this->dems;
}

void VRP::print(){
    cout << this->N << " " << this->M << endl;
    int i,j;
    short count = 0;
    cout << "Edges" << endl;
    for(i=0;i<N;i++){
        cout << "Vertex: " << i << "; Demand: " << dems[i] << endl;
        count = 0;
        for(j=0;j<N;j++){
            cout << "\t" << dist[i][j];
            if(++count >= 15){
                count = 0;
                cout << endl;
            }
        }
        cout << endl;
    }
}