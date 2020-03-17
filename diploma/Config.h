//
// Created by José Hilario on 19 Feb 2020.
//

#ifndef DIPLOMA_CONFIG_H
#define DIPLOMA_CONFIG_H

#include <string>
#include <unordered_map>
#include <torch/torch.h>
#include "utils.h"
#include "Agent.h"
#include "Dataset.h"

namespace ConfigHelpers {
    enum class Model { BaselineStdMnist, BaselineAdvMnist };
    enum class Optimizer { Adam, SGD };
    enum class Loss { NLL, MSE };
    enum class Dataset { MNIST, FashionMNIST };
}

class Loader {
public:
    Loader() : file{"01.cfg"}, device{"cpu"} {}
    Loader(std::string filename, std::string device_id);

//    std::tuple<std::shared_ptr<AgentBase>, std::shared_ptr<CustomDataset>, std::shared_ptr<CustomDataset>> process();
//    std::tuple<
//    std::shared_ptr<AgentBase>,
//    torch::data::StatelessDataLoader<CustomDataset, torch::data::samplers::SequentialSampler>,
//    torch::data::StatelessDataLoader<CustomDataset, torch::data::samplers::SequentialSampler>> process();
    auto process();
    friend std::istream &operator>>(std::istream& in, Loader& cfg);
private:
    auto get_agent();
    auto get_dataset();

    std::string file;
    torch::Device device;
    std::map<std::string, std::string> dict;
};

#endif //DIPLOMA_CONFIG_H
