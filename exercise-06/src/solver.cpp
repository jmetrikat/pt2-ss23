#include "solver.h"

#include "actionchoice.h"

// returns the expected reward for taking action "action" in a state "state" at time "time"
double Solver::computeExpectedRewardForAction(const int action, const int state, const int time, const double* const futureValues) {
    double expectedReward = 0.0;

    for (int event = 0; event <= 1; event++) {
        expectedReward += env.getEventProbability(event, action, state, time) * (env.getReward(event, action, state) + futureValues[env.getNextState(event, state)]);
    }

    return expectedReward;
}

// returns the action (and reward) that maximizes the expected reward in a state "state" at time "time"
ActionChoice Solver::computeExpectedRewardForTimeAndState(const int state, const int time, const double* const futureValues) {
    ActionChoice bestActionChoice(env.getMinAction(), env.getFinalReward(env.getMaxState()));

    for (int action = env.getMinAction(); action <= env.getMaxAction(); action += env.getActionStep()) {
        double expectedReward = computeExpectedRewardForAction(action, state, time, futureValues);

        if (expectedReward >= bestActionChoice.maxReward) {
            bestActionChoice.action = action;
            bestActionChoice.maxReward = expectedReward;
        }
    }

    return bestActionChoice;
}

// returns the final rewards for all states
double* Solver::computeFinalRewards(void) {
    double* finalRewards = new double[env.getMaxState() + 1];

    for (int state = 0; state <= env.getMaxState(); state++) {
        finalRewards[state] = env.getFinalReward(state);
    }

    return finalRewards;
}

// computes the optimal policy by dynamic programming
int* Solver::computePolicy(void) {
    double* futureValues = computeFinalRewards();
    double* currentValues = new double[env.getMaxState() + 1];
    int* policy = new int[(env.getMaxTime() + 1) * (env.getMaxState() + 1)];

    for (int time = env.getMaxTime(); time >= 0; time--) {
        for (int state = 0; state <= env.getMaxState(); state++) {
            ActionChoice bestActionChoice = computeExpectedRewardForTimeAndState(state, time, futureValues);
            policy[time * (env.getMaxState() + 1) + state] = bestActionChoice.action;
            currentValues[state] = bestActionChoice.maxReward;
        }
        auto* tmp = futureValues;
        futureValues = currentValues;
        currentValues = tmp;
    }

    delete[] futureValues;
    delete[] currentValues;
    return policy;
}
