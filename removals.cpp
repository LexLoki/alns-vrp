#include "solution.hpp"

using namespace std;

Solution *removal_random(Solution &sol, int q)
{
    //cout << "hi1_1" << endl;
    Solution *nSol = new Solution(sol);
    q = min(q, nSol->nodes_count);
    //cout << q << " " << nSol->nodes_count << endl;
    int r;
    int removed;
    while(q--){
        r = rand()%nSol->nodes_count;
        removed = nSol->removeNode(r);
        nSol->nodes_bank.push_back(removed);
    }
    return nSol;
}

// Returns how much cost node at IT brings to the solution
float costDiff(list<int>::iterator it, float **dist)
{
    int idPrev = *prev(it), idCurr = *it, idNext = (*it+1);
    return dist[idPrev][idCurr] + dist[idCurr][idNext] - dist[idPrev][idNext];
}

Solution *removal_worst(Solution &sol, int q) //without p factor for now
{
    //cout << "hi2_1" << endl;
    Solution *nSol = new Solution(sol);
    int i, higher_idx;
    list<int>::iterator it, higher_it;
    float higher;
    q = min(q, nSol->veh_used);
    Vehicle *veh;
    int idx;
    list<int> *route;
    float cost;
    float **dist = nSol->instance->dist;
    float *dems = nSol->instance->dems;
    while(q--){
        higher = -100000;
        for(i=0;i<nSol->veh_used;i++){
            veh = nSol->vehicles[i];
            route = veh->route;
            for(it = next(route->begin()); it != prev(route->end()); it++ ){
                cost = costDiff(it, dist);
                if(cost > higher){
                    higher = cost;
                    higher_it = it;
                    higher_idx = i;
                }
            }
        }
        nSol->nodes_count--;
        nSol->nodes_bank.push_back(*higher_it);
        nSol->vehicles[higher_idx]->removeNode(higher_it, dist, dems);
        /*
        for(i=0;i<newS->veh_used;i++){
            if(newS->vehicles[i]->cost > higher){
                higher_idx = i;
                higher = newS->vehicles[i]->cost;
            }
            newS->removeVehicle(higher_idx);
        }*/
    }
    return nSol;
}

//relatedness
//note: relatedness defined for RPDPTW consider distance zero for terminal
//  since we are using cvrp, this will simplify the formula
//  relatedness becomes pure distance between nodes
float relatedness(float **dists, int i, int j)
{
    return dists[i][j];
}

Solution *removal_related(Solution &sol, int q)
{
    //cout << "hi3_1" << endl;
    Solution *nSol = new Solution(sol);
    //cout << "hi3_2" << endl;

    //rand()%sol
    int idx = rand()%nSol->nodes_count;
    //removeNode(idx);

    //nSol->nodes_bank.push_back();

    while(--q){
        
    }
    return nSol;
}