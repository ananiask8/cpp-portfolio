//
// Created by José Hilario on 19 Feb 2020.
//

#ifndef DIPLOMA_BASELINESTDMNIST_H
#define DIPLOMA_BASELINESTDMNIST_H

#include <torch/torch.h>

class BaselineStdMNIST : public torch::nn::Module {
public:
    BaselineStdMNIST();
    torch::Tensor forward(const torch::Tensor&);
private:
    torch::nn::ModuleList hidden_layers;
    torch::nn::AdaptiveAvgPool2d avg_pool;
    torch::nn::LogSoftmax log_soft;
};


#endif //DIPLOMA_BASELINESTDMNIST_H
