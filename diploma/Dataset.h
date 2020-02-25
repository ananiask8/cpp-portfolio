//
// Created by José Hilario on 24 Feb 2020.
//

#ifndef DIPLOMA_DATASET_H
#define DIPLOMA_DATASET_H

#include <torch/torch.h>

class DatasetBase {
public:
    DatasetBase() {}

    virtual torch::data::DataLoaderBase<
            torch::data::datasets::MNIST,
            typename torch::data::datasets::MNIST::BatchType::value_type,
            typename torch::data::datasets::MNIST::BatchRequestType> get_loader() = 0;

};

template <typename Dataset>
class DatasetWrapper : public torch::data::DataLoaderBase<
        Dataset,
        typename Dataset::BatchType::value_type,
        typename Dataset::BatchRequestType>, DatasetBase {
    using DataLoader = torch::data::DataLoaderBase<
            Dataset, typename Dataset::BatchType::value_type, typename Dataset::BatchRequestType>;
public:
    DatasetWrapper(Dataset& data_loader) : loader {data_loader} {}
    DataLoader& get_loader() override { return loader; }
private:
    DataLoader& loader;
};

template <typename D>
std::shared_ptr<DatasetBase> wrap_dataset(D& loader);

#endif //DIPLOMA_DATASET_H
