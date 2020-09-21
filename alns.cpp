#include "alns.hpp"
#include <iostream>
#include <list> 
#include <cmath>
#include <stdlib.h>

using namespace std;

ALNS::ALNS(Params *params) : params(params){}

//maybe use vector
int rwSelection(vector<float> &scores){
    float total = 0;
    for(float x : scores){
        total += x;
    }
    float v = rand()/(float)RAND_MAX * total;
    //cout << v << endl;
    int idx = 0;
    for(float x : scores){
        total -= x;
        if(v >= total) return idx;
        idx++;
    }
    return -1;
}

void resetScore(vector<float> &scores){
    for(auto it = scores.begin(); it != scores.end(); it++){
        *it = 1;
    }
}

void ALNS::runStep(){
    int hyper = 2;
    //Select destroy repair
    //cout << "WTF" << endl;
    int dt_idx = rwSelection(scores_destroy), rp_idx = rwSelection(scores_repair);
    //dt_idx = 0;
    SH f_dt = m_destroy[dt_idx], f_rp = m_repair[rp_idx];
    //cout << "Roulete: " << dt_idx << ", " << rp_idx << endl;
    Solution *destroyed = f_dt(*sol_curr, hyper);
    //cout << "After destroy cost: " << destroyed->cost << endl;
    //cout << "dt: " << destroyed->nodes_count << endl;
    Solution *repaired = f_rp(*destroyed, hyper);
    Solution *s = repaired;
    //cout << "rp: " << repaired->nodes_count << endl;
    //cout << "After repair cost: " << repaired->cost << endl;

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

void ALNS::run(Solution *base){
    //cout << "run" << endl;
    resetScore(scores_repair);
    resetScore(scores_destroy);
    sol_best = base;
    sol_curr = base;
    cost_best = base->cost;
    
    cout << "Start cost: " << sol_best->cost << endl;
    int count = 0;
    int limit = 5000;
    while(count++ < limit && clock() - params->startTime <= params->timeLimit){ //criteria
        this->runStep();
        if(count%100 == 0)
            cout << "Current best: " << sol_best->cost << endl;
    }
    cout << "Best found: " << sol_best->cost << endl;
    //cout << sol_best->nodes_count << endl;
}

void ALNS::addRepair(SH method){
    m_repair.push_back(method);
    scores_repair.push_back(1);
}

void ALNS::addDestroy(SH method){
    m_destroy.push_back(method);
    scores_destroy.push_back(1);
}