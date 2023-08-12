#ifndef HEADER_H_ENVIRONMENTS
#define HEADER_H_ENVIRONMENTS

class BasicEnvironment {
   protected:
    const int maxTime = 200;
    const int maxAction = 400;
    const int minAction = 5;
    const int actionStep = 5;
    const int maxState = 50;
    const double finalReward = -10;

   public:
    // returns the probability of making a sale
    virtual double getEventProbability(const int event, const int action, const int state, const int time) const {
        return 0;
    };

    // returns the rewards in a given state/action
    virtual double getReward(const int event, const int action, const int state) const {
        return 0;
    };

    // updates the next state given a state
    virtual int getNextState(const int event, const int state) const {
        return 0;
    };

    // returns the final reward
    virtual int getFinalReward(const int state) const {
        return 0;
    }

    // returns the maximum time of the environment
    int getMaxTime() const {
        return maxTime;
    }

    // returns the maximum action of the environment
    int getMaxAction() const {
        return maxAction;
    }

    // returns the minimum action of the environment
    int getMinAction() const {
        return minAction;
    }

    // returns the action step of the environment
    int getActionStep() const {
        return actionStep;
    }

    // returns the maximum state of the environment
    int getMaxState() const {
        return maxState;
    }
};

// TicketEnvironment inherits from BasicEnvironment
class TicketEnvironment : public BasicEnvironment {
   public:
    double getEventProbability(const int event, const int action, const int state, const int time) const override {
        if (event != 0 && event != 1) {
            return 0.0;
        }

        double prob = (1 - ((double)action / (double)maxAction)) * (1 + time) / maxTime;
        return event == 0 ? 1 - prob : prob;
    }

    double getReward(const int event, const int action, const int state) const override {
        if (state != 0 && event == 1) {
            return action;
        }

        return 0.0;
    }

    int getNextState(const int event, const int state) const override {
        if (state != 0 && event == 1) {
            return state - 1;
        }

        return state;
    }

    int getFinalReward(const int state) const override {
        return state * finalReward;
    }
};

#endif
