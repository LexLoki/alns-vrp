#ifndef alns_hpp
#define alns_hpp

#include "solution.hpp"
#include "Params.h"

#include <list> 
#include <iostream>
#include <vector>

// Function pointer for repair/removal heuristic
typedef Solution* (*SH)(Solution &, int);

class ALNS{

    Params *params;

    std::vector< SH > m_repair;
    std::vector< SH > m_destroy;
    std::vector<float> scores_repair;
    std::vector<float> scores_destroy;

    Solution *sol_curr;
    Solution *sol_best;

    float cost_best;

public:
    void addRepair(SH method);
    void addDestroy(SH method);
    void run(Solution *base);
    void runStep();
    ALNS(Params *params);
};

#endif