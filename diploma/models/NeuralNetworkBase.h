//
// Created by José Hilario on 19 Apr 2020.
//

#ifndef DIPLOMA_NEURALNETWORKBASE_H
#define DIPLOMA_NEURALNETWORKBASE_H

#include <torch/torch.h>

struct NeuralNetworkBase : public torch::nn::Module {
public:
    NeuralNetworkBase() = default;
    virtual torch::Tensor forward(const torch::Tensor&) = 0;
};

#endif //DIPLOMA_NEURALNETWORKBASE_H
