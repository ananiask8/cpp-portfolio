//
// Created by José Hilario on 24 Feb 2020.
//

#ifndef DIPLOMA_DATASET_H
#define DIPLOMA_DATASET_H

#include <torch/torch.h>

class CustomDataset : public torch::data::Dataset<CustomDataset> {
public:
    enum class Mode { kTrain, kTest };
    CustomDataset(const std::string& root, Mode mode = Mode::kTrain) {};

//    virtual torch::Tensor read_data(const std::string& root, bool train) = 0;
//    virtual torch::Tensor read_target(const std::string& root, bool train) = 0;

    torch::data::Example<> get(size_t index) override {}
    torch::optional<size_t> size() const override {}
    virtual bool is_train() const noexcept {}
    virtual const torch::Tensor& data() const {}
    virtual const torch::Tensor& targets() const {}
};

class MNIST : public CustomDataset {
public:
    MNIST(const std::string& root, Mode mode = Mode::kTrain);

    torch::data::Example<> get(size_t index) override;
    torch::optional<size_t> size() const override;
    bool is_train() const noexcept override;
    const torch::Tensor& data() const override;
    const torch::Tensor& targets() const override;
private:
//    torch::Tensor read_data(const std::string&, bool) override;
//    torch::Tensor read_target(const std::string&, bool) override;
    torch::Tensor images_, targets_;

};

//class FashionMNIST : public CustomDataset {
    //// TODO ////
//};

#endif //DIPLOMA_DATASET_H
