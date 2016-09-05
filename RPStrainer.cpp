/*
Trains "one sided"
This makes it an inefficient training algorithm.
*/

#include "RPStrainer.h"

int main(){
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
    //seed rng
    uint64_t seed = time(NULL) ^ (intptr_t)&printf;
    pcg32_srandom(seed , 1);
    
    int iter;
    cout << "Please enter number of iterations\n";
    cin >> iter;
    cout <<"\n";
    train(iter);
    vector<float> result = getAverageStrategy();
    cout << "\n" << "Strategy: ";
    for(int i = 0; i < result.size(); i++){
        cout<< (int) (result[i]*100) << " ";
    }
    cin >> iter; //to see results
    return 0;
}


//get current MS by regret-matching
vector<float> getStrategy(vector<float>& strat, vector<float>& regSum,
                            vector<float>& stratSum){
    float normalizingSum = 0;
    for(int i = 0; i < NUM_ACTIONS; i++){
        strat[i] = (regSum[i] > 0) ? regSum[i] : 0;
        normalizingSum += strat[i];
    }
    for(int i = 0; i < NUM_ACTIONS; i++){
        if(normalizingSum >0){
        strat[i] /= normalizingSum;
        }
        else{
            strat[i] = 1.0 / NUM_ACTIONS;
        }
        stratSum[i] += strat[i];
    }
    return strat;
}


//main loop
void train(int iterations){
    vector<float> actionUtility(NUM_ACTIONS);
    for(int i = 0; i < iterations; i++){
        cout<<"Iteration "<< i <<"\n";
        
        //get strategies and actions for both players
        strategy = getStrategy(strategy, regretSum, strategySum);
        cout <<"Strategy: ";
        for(int i = 0; i < strategy.size(); i++){
            cout<< (int) (strategy[i]*100) << " ";
            }
            
        oppStrategy = getStrategy(oppStrategy, oppRegretSum, oppStrategySum);
        cout <<"\nOppStrategy: ";
        for(int i = 0; i < oppStrategy.size(); i++){
            cout<< (int) (oppStrategy[i]*100) << " ";
            }
            
        int myAction = getAction(strategy);
        cout<<"\nAction is:  " << myAction;
        int oppAction = getAction(oppStrategy);
        cout<<"\noppAction is:  " << oppAction;
        
        //gameplay outcome
        actionUtility[oppAction] = 0;
        actionUtility[oppAction == NUM_ACTIONS-1 ? 0 : oppAction+1] = 1;
        actionUtility[oppAction == 0 ? NUM_ACTIONS-1 : oppAction-1] = -1;
        
        //compute regret and add it to cumulRegret
        for(int i = 0; i < NUM_ACTIONS; i++){
            regretSum[i] += actionUtility[i] - actionUtility[myAction];
            oppRegretSum[i] += actionUtility[i] - actionUtility[oppAction];
            }
        cout<<"\n\n\n";
    }
}

//get final result
vector<float> getAverageStrategy(){
    vector<float> avgStrat(NUM_ACTIONS);
    float normalizingSum = 0;
    for(int i = 0; i < NUM_ACTIONS; i++){
        normalizingSum += strategySum[i];
    }
    for(int i = 0; i < NUM_ACTIONS; i++){
        if(normalizingSum > 0){
            avgStrat[i] = strategySum[i] / normalizingSum;
        }
        else{
            cout<<"Failed training output\n";
            avgStrat[i] = 1.0 / NUM_ACTIONS;
        }
    }
    cout <<"StrategySum: ";
    for(int i = 0; i < strategySum.size(); i++){
        cout<< (int) (strategySum[i]*100) << " ";
        }
    return avgStrat;
}