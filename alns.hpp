#ifndef alns_hpp
#define alns_hpp

#include "solution.hpp"

#include <list> 
#include <iostream>


class ALNS{
    //array of methods
    //list<>
    list<f> m_repair;
    list<f> m_destroy;
    list<float> scores_repair;
    list<float> scores_destroy;

    Solution sol_curr;

    Solution sol_best;
    float cost_best;

public:
    void addRepair();
    void addDestroy();
    void run();
    ALNS();
};

#endif