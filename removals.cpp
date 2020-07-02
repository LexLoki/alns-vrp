#include "solution.hpp"



Solution removal_random(Solution sol, int q)
{
    q = min(q, sol->veh_used);
    Solution newS = sol //do as copy
    while(q--){
        newS->removeVehicle(random(0,newS->veh_used-1)); //put random
    }
}

Solution removal_worst(Solution sol, int q) //without p factor for now
{
    Solution newS = sol;
    int i;
    float higher;
    int higher_idx;
    q = min(q, sol->veh_used);
    while(q--){
        higher = -1;
        for(i=0;i<newS->veh_used;i++){
            if(newS->vehicles[i]->cost > higher){
                higher_idx = i;
                higher = newS->vehicles[i]->cost;
            }
            newS->removeVehicle(higher_idx);
        }
    }
}