//
// Created by José Hilario on 19 Feb 2020.
//

#ifndef DIPLOMA_UTILS_H
#define DIPLOMA_UTILS_H

#include <torch/torch.h>

// define a better type to generalize this. Or, how to leverage the loss function modules?
typedef torch::Tensor (*LossFunction) (const torch::Tensor&, const torch::Tensor&, long long);


#endif //DIPLOMA_UTILS_H
