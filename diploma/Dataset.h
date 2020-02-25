//
// Created by José Hilario on 24 Feb 2020.
//

#ifndef DIPLOMA_DATASET_H
#define DIPLOMA_DATASET_H

#include <torch/torch.h>

class CustomDataset : public torch::data::Dataset<CustomDataset> {
protected:
    torch::Tensor data, target;
public:
    enum class Mode { kTrain, kTest };
    CustomDataset(const std::string& root, Mode mode = Mode::kTrain) {};

    virtual torch::Tensor read_data(const std::string& root, bool train) = 0;
    virtual torch::Tensor read_target(const std::string& root, bool train) = 0;

    virtual torch::data::Example<> get(size_t index) override;
    virtual torch::optional<size_t> size() const override;
};

class MNIST : public CustomDataset {
    MNIST(const std::string& root, Mode mode = Mode::kTrain)
        : CustomDataset(root, mode) {
        data = read_data(root, mode == Mode::kTrain);
        target = read_target(root, mode == Mode::kTrain);
    };

    virtual torch::Tensor read_data(const std::string&, bool) override;
    virtual torch::Tensor read_target(const std::string&, bool) override;
};

class FashionMNIST : public CustomDataset {

};

#endif //DIPLOMA_DATASET_H
