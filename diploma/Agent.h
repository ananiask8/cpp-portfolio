//
// Created by José Hilario on 19 Feb 2020.
//

#ifndef DIPLOMA_AGENT_H
#define DIPLOMA_AGENT_H

#include <torch/torch.h>

#include <utility>
#include "Dataset.h"
#include "models/NeuralNetworkBase.h"

class AgentBase {
public:
    AgentBase(std::shared_ptr<NeuralNetworkBase> mmodel, std::shared_ptr<torch::optim::Optimizer> moptim, torch::Device mdev)
            : model {std::move(mmodel)}, optim {std::move(moptim)}, device{mdev} {}
    virtual void train(DatasetWrapper&, DatasetWrapper&) = 0;
    virtual void eval(DatasetWrapper&) = 0;
    virtual torch::Tensor acc(const torch::Tensor&, const torch::Tensor&) = 0;
    virtual torch::Tensor loss(const torch::Tensor&, const torch::Tensor&) = 0;
protected:
    std::shared_ptr<NeuralNetworkBase> model;
    std::shared_ptr<torch::optim::Optimizer> optim;
    torch::Device device;
};

template <typename LossType>
class Agent : public AgentBase {
public:
    Agent(
            const std::shared_ptr<NeuralNetworkBase>& mmodel, const std::shared_ptr<torch::optim::Optimizer>& moptim,
            LossType mcriterion, torch::Device mdev) : AgentBase(mmodel, moptim, mdev), criterion {mcriterion} {}
    void train(DatasetWrapper& training_dwrapper, DatasetWrapper& validation_dwrapper) override;
    void eval(DatasetWrapper& dataset) override;
    torch::Tensor acc(const torch::Tensor&, const torch::Tensor&) override;
    torch::Tensor loss(const torch::Tensor&, const torch::Tensor&) override;
private:
    LossType criterion;
};

#endif //DIPLOMA_AGENT_H
