//
// Created by José Hilario on 19 Feb 2020.
//

#ifndef DIPLOMA_AGENT_H
#define DIPLOMA_AGENT_H

#include <torch/torch.h>
#include "Dataset.h"

class AgentBase {
public:
    AgentBase() {}
//    virtual void train(std::shared_ptr<DatasetBase>&) = 0;
//    virtual void eval(std::shared_ptr<DatasetBase>&) = 0;
    virtual auto get_criterion() = 0;
private:
    torch::nn::Module model;
    std::shared_ptr<torch::optim::Optimizer> optim;
};

template <typename LossType>
class Agent : public AgentBase {
public:
    Agent() {}
    Agent(torch::nn::Module mmodel, std::shared_ptr<torch::optim::Optimizer> moptim, LossType mcriterion)
        : model {mmodel}, optim {moptim}, criterion {mcriterion} {}

    template<typename DatasetType>
    friend void train(DatasetType& data);

    template<typename DatasetType>
    friend void eval(DatasetType& data);
private:
    LossType criterion;
};

template<typename DatasetType>
void train(std::shared_ptr<AgentBase> agent, DatasetType& data);

template<typename DatasetType>
void eval(std::shared_ptr<AgentBase> agent, DatasetType& data);
#endif //DIPLOMA_AGENT_H
