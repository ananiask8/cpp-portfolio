//
// Created by José Hilario on 19 Feb 2020.
//

#ifndef DIPLOMA_AGENT_H
#define DIPLOMA_AGENT_H

#include <torch/torch.h>
#include "Dataset.h"

class AgentBase {
public:
    AgentBase(torch::nn::Module mmodel, std::shared_ptr<torch::optim::Optimizer> moptim)
            : model {mmodel}, optim {moptim} {}
    virtual void train(std::shared_ptr<CustomDataset>&) = 0;
    virtual void eval(std::shared_ptr<CustomDataset>&) = 0;
    virtual torch::Tensor loss(const torch::Tensor&, const torch::Tensor&) = 0;
protected:
    torch::nn::Module model;
    std::shared_ptr<torch::optim::Optimizer> optim;
};

template <typename LossType>
class Agent : public AgentBase {
public:
    Agent() {}
    Agent(torch::nn::Module mmodel, std::shared_ptr<torch::optim::Optimizer> moptim, LossType mcriterion)
        : AgentBase(mmodel, moptim), criterion {mcriterion} {}
    virtual void train(std::shared_ptr<CustomDataset>& dataset) override;
    virtual void eval(std::shared_ptr<CustomDataset>& dataset) override;
    virtual torch::Tensor loss(const torch::Tensor&, const torch::Tensor&) override;
private:
    LossType criterion;
};

template<typename DatasetType>
void train(std::shared_ptr<AgentBase> agent, DatasetType& data);

template<typename DatasetType>
void eval(std::shared_ptr<AgentBase> agent, DatasetType& data);
#endif //DIPLOMA_AGENT_H
