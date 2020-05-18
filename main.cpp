#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "vrp.hpp"
#include "cvrp.hpp"

using namespace std;

std::string get_working_path() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        return std::string(cwd);
    else
        return std::string("");
}

float dist(float *p1, float *p2){
    float dx = p1[0]-p2[0], dy = p1[1] - p2[1];
    return sqrt(dx*dx+dy*dy);
}

float **coordToDist(float **pos, int n){
    int i,j;
    float **d = new float*[n];
    for(i=0;i<n;i++){
        d[i] = new float[n];
        d[i][i] = -1;
        for(j=0;j<i;j++){
            d[i][j] = d[j][i] = dist(pos[i],pos[j]);
        }
    }
    return d;
}

void readVRP(ifstream &str){
    int max = 100;
    string line;
    string name, comment, type;
    int dim, cap, dep, i;
    str.ignore(max,':'); str >> name;
    str.ignore(max,':'); str >> comment;
    str.ignore(max,':'); str >> type;
    str.ignore(max,':'); str >> dim;
    str.ignore(max,':'); str.ignore(max,':'); str >> cap;

    //Read coordinates
    str >> line;
    float **pos = new float*[dim];
    for(i=0;i<dim;i++){
        pos[i] = new float[2];
        str >> line >> pos[i][0] >> pos[i][1];
        //cout << pos[i][0] << ", " << pos[i][1] << endl;
    }
    float **dist = coordToDist(pos, dim);
    for(i=0;i<dim;delete[] pos[i++]);
    delete[] pos;

    //Read demands
    str >> line;
    float *dem = new float[dim];
    for(i=0;i<dim;i++){
        str >> line >> dem[i];
    }
    //Read depot
    str >> line;
    str >> dep;
    dep -= 1;

    CVRP instance(name, dist, dem, dim, cap, dep);
    
    instance.print();
}

void petal(CVRP inst){
    
}

int main() {

    ifstream file("Vrp-Set-X/X/X-n101-k25.vrp");
    string content;

    cout << get_working_path() << endl;

    readVRP(file);

    file.close();
    return 0;
}