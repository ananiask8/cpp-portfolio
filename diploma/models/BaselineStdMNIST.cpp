//
// Created by José Hilario on 19 Feb 2020.
//

#include "BaselineStdMNIST.h"
using namespace torch;

BaselineStdMNIST::BaselineStdMNIST() : avg_pool{nn::AdaptiveAvgPool2d(1)}, log_soft{nn::LogSoftmax(1)} {
    hidden_layers = register_module("hidden_layers", nn::ModuleList());
    hidden_layers->push_back(nn::Sequential(
            nn::Conv2d(nn::Conv2dOptions(1, 32, {5})
                               .stride(1).padding(0)),
            nn::BatchNorm(32),
            nn::Sigmoid(),
            nn::MaxPool2d(nn::MaxPool2dOptions(3).stride(3))
        )
    );
    hidden_layers->push_back(nn::Sequential(
            nn::Conv2d(nn::Conv2dOptions(32, 10, {5})
                               .stride(1).padding(0)),
            nn::BatchNorm(10),
            nn::Sigmoid(),
            nn::MaxPool2d(nn::MaxPool2dOptions(2).stride(2))
        )
    );
}

Tensor BaselineStdMNIST::forward(const Tensor& x) {
    
}