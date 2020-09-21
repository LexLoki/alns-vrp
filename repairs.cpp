#include "solution.hpp"

using namespace std;

// Returns how much cost increases by adding ND to IT position of route
float costUp(list<int>::iterator it, int nd, float **dist)
{
    int idPrev = *prev(it), idCurr = *it;
    return dist[idPrev][nd] + dist[nd][idCurr] - dist[idPrev][idCurr];
}

Solution *insertion_greedy(Solution &sol, int q)
{
    Solution *nSol = new Solution(sol);
    //copy
    int nd,i;
    Vehicle *veh;
    float cost, higher;
    int higher_idx;
    list<int>::iterator it, higher_it;
    float **dist = nSol->instance->dist;
    float *loads = nSol->instance->dems;
    list<int> unfeasible;
    //cout << "insertion: " << nSol->nodes_bank.size() << endl;
    for(auto bank_it = nSol->nodes_bank.begin(); bank_it!=nSol->nodes_bank.end(); bank_it++){
        nd = *bank_it;
        //Find best greedy position at some route
        higher = 100000000;
        higher_idx = -1;
        //cout<<"inserting: " << nd << " l "<< loads[nd] << endl;
        for(i=0;i<nSol->veh_used;i++){
            veh = nSol->vehicles[i];
            //if route can take the demand
            //cout << veh->load << " ";
            if(veh->canFit(loads[nd])){
                //cout << "X";
                //Find best position in route
                for(it = next(veh->route->begin()); it != veh->route->end(); it++ ){
                    cost = costUp(it, nd, dist);
                    //cout << " up" << cost; 
                    if(cost < higher){
                        //cout << " got: " << cost << endl;
                        higher = cost;
                        higher_it = it;
                        higher_idx = i;
                    }
                }
            }
            //cout << endl;
        }
        if(higher_idx>=0)
            nSol->addNode(higher_idx, higher_it, nd);
        else{
            unfeasible.push_back(nd);
        }
    }
    nSol->nodes_bank = unfeasible;
    //empty list
    return nSol;
}