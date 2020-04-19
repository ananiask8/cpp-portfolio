//
// Created by José Hilario on 19 Feb 2020.
//

#ifndef DIPLOMA_BASELINESTDMNIST_H
#define DIPLOMA_BASELINESTDMNIST_H

#include <torch/torch.h>
#include "NeuralNetworkBase.h"

struct BaselineStdMNISTImpl : public NeuralNetworkBase {
public:
    BaselineStdMNISTImpl();
    torch::Tensor forward(const torch::Tensor&) override;
private:
    torch::nn::ModuleList hidden_layers;
    torch::nn::AdaptiveAvgPool2d avg_pool;
    torch::nn::LogSoftmax log_soft;
};

TORCH_MODULE(BaselineStdMNIST);

#endif //DIPLOMA_BASELINESTDMNIST_H
