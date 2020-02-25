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

    std::shared_ptr<AgentBase> process();

    template <typename D>
    friend std::pair<
            std::shared_ptr<torch::data::DataLoaderBase<D,typename D::BatchType::value_type, typename D::BatchRequestType>>,
            std::shared_ptr<torch::data::DataLoaderBase<D,typename D::BatchType::value_type, typename D::BatchRequestType>>> load_dataset(Loader&);
    friend std::istream &operator>>(std::istream& in, Loader& cfg);

    using DatasetType = nullptr_t;
private:
    std::string file;
    torch::Device device;
    std::map<std::string, std::string> dict;
};

template <typename D>
std::pair<
std::shared_ptr<torch::data::DataLoaderBase<D,typename D::BatchType::value_type, typename D::BatchRequestType>>,
std::shared_ptr<torch::data::DataLoaderBase<D,typename D::BatchType::value_type, typename D::BatchRequestType>>> load_dataset(Loader&);

#endif //DIPLOMA_CONFIG_H
