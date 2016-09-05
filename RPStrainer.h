#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "pcg_basic.h"

using std::vector;
using std::cin; 
using std::cout;

int ROCK = 0;
int PAPER = 1;
int SCISSORS = 2;
int NUM_ACTIONS = 3;
vector<float> regretSum(NUM_ACTIONS);
vector<float> oppRegretSum(NUM_ACTIONS);
vector<float> strategySum(NUM_ACTIONS);
vector<float> strategy(NUM_ACTIONS);
vector<float> oppStrategy(NUM_ACTIONS);
vector<float> oppStrategySum(NUM_ACTIONS);

//next float in rng
inline float NextFloat()
	{
		return (float) ldexp(pcg32_random(), -32);
	}

//get current MS by regret-matching
vector<float> getStrategy(vector<float>& strat, vector<float>& regSum,
                            vector<float>& stratSum);

//get random action from MS distribution
inline int getAction(vector<float> strategy){
    float r = NextFloat();
    cout<< "\nRNG: " << (int)(r*100);
    int i = 0;
    float cumulProbability = 0;
    while(i < NUM_ACTIONS - 1){
        cumulProbability += strategy[i];
        if(r < cumulProbability){break;}
        i++;
    }
    return i;
}

//train
void train(int iterations);

//get final result
vector<float> getAverageStrategy();