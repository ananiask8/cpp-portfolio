//
// Created by José Hilario on 24 Feb 2020.
//

#ifndef DIPLOMA_DATASET_H
#define DIPLOMA_DATASET_H

#include <torch/torch.h>

class CustomDataset : public torch::data::Dataset<CustomDataset> {
public:
    enum class Mode { kTrain, kTest };

    CustomDataset(const std::string& root, Mode mode = Mode::kTrain);
    torch::data::Example<> get(size_t index) override;
    torch::optional<size_t> size() const override;
    bool is_train() const noexcept;
    const torch::Tensor& data() const;
    const torch::Tensor& targets() const;
private:
//    torch::Tensor read_data(const std::string&, bool) override;
//    torch::Tensor read_target(const std::string&, bool) override;
    torch::Tensor images_, targets_;

};

//class FashionMNIST : public CustomDataset {
    //// TODO ////
//};

struct DatasetTransforms {
    std::shared_ptr<torch::data::transforms::Normalize<>> normalize = nullptr;
    std::shared_ptr<torch::data::transforms::Stack<>> stack = nullptr;
};

class DatasetWrapper {
public:
    DatasetWrapper(CustomDataset dataset, DatasetTransforms transforms, int batch_size, long epochs = 0);

    CustomDataset dataset;
    DatasetTransforms transforms;
    int batch_size;
    long epochs;
};

#endif //DIPLOMA_DATASET_H
