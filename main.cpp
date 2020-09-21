#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include "vrp.hpp"
#include "cvrp.hpp"
#include "alns.hpp"
#include "commandline.h"

using namespace std;

//#include "removals.cpp"
//#include "repairs.cpp"

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

Solution *baseSolution;

Solution* removal_random(Solution &sol, int q);
Solution* removal_worst(Solution &sol, int q);
Solution* removal_related(Solution &sol, int q);
Solution* insertion_greedy(Solution &sol, int q);

void runALNS(CVRP *instance, Params *params){
    ALNS *fwork = new ALNS(params);
    fwork->addDestroy(&removal_random);
    fwork->addDestroy(&removal_worst);
    fwork->addDestroy(&removal_related);
    fwork->addRepair(&insertion_greedy);
    fwork->run(baseSolution);
}

void readVRP(commandline c, ifstream &str){
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



    //TODO:separate later
    Params params(c.get_path_to_instance(), c.get_seed());
    CVRP *instance = new CVRP(name, dist, dem, dim, cap, dep);

    params.startTime = clock();
    params.timeLimit = c.get_cpu_time() * CLOCKS_PER_SEC;
    
    //instance.print();
    list<list<int>*> *routes = CVRP::getPetal(pos, dim, dep, cap, dem);

    baseSolution = new Solution(instance, *routes, cap);


    runALNS(instance, &params);

    //Freeing positions CHECK LATER
    //for(i=0;i<dim;delete[] pos[i++]);
    //delete[] pos;
}

void petal(CVRP inst){
    
}

int main(int argc, char *argv[])
{
	commandline c(argc, argv);
	if (c.is_valid())
	{
		// Read the instance and calculate distance matrix
        //Params params(c.get_path_to_instance(), c.get_seed());
        ifstream file(c.get_path_to_instance());
        srand(c.get_seed());
        readVRP(c,file);
    }
    return 0;
}

int mainOld() {

    ifstream file("Vrp-Set-X/X/X-n101-k25.vrp");
    string content;

    cout << get_working_path() << endl;

    //readVRP(c,file);

    file.close();
    return 0;
}