#include "alnss.hpp"
#include <iostream>
#include <list> 
#include <cmath>

using namespace std;

ALNS::ALNS() : {}

//maybe use vector
int rwSelection(list<float> &scores){
    auto it;
    float total;
    for(it = scores->begin(); it != scores->end(); ++it){
        total += *it;
    }
    float v = 0;//def random here random(0,total)
    int idx = 0;
    for(it = scores->begin(); it != scores->end(); ++it){
        total -= *it;
        if(v >= total) return idx;
        idx++;
    }
    return -1;
}

void resetScore(list<float> &scores){ for(auto it = scores->begin(); it != scores->end(); *it++ = 1f); }

void ALNS::runStep(){
    //Select destroy repair
    f f_dt = m_destroy[rwSelection(scores_destroy)];
    f f_rp = m_repair[rwSelection(scores_repair)];
    Solution s = f_rp(f_dt(sol_curr));
    if(s->valid()){
        sol_curr = s;
        //update scores ... todo!?
        float score = sol_curr->cost;
        if(cost_best > score){
            sol_best = sol_curr;
            cost_best = score;
        }
    }
}

void ALNS::run(){
    resetScore(scores_repair);
    resetScore(scores_destroy);
    while(0){ //criteria
        this->runStep();
    }
}

void ALNS::addRepair(){

}

void ALNS::addDestroy(){

}