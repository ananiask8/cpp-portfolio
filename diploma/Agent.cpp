//
// Created by José Hilario on 19 Feb 2020.
//

#include "Agent.h"

using namespace torch;

template<typename Self, typename TransformType, typename... Tail>
auto transforms(Self self, TransformType transform, Tail... tail) {
    return transforms(self.map(*transform), tail...);
}

template<typename Self, typename TransformType>
auto transforms(Self self, TransformType transform) {
    return self.map(*transform);
}

template <typename T>
void Agent<T>::train(DatasetWrapper& training_dwrapper, DatasetWrapper& validation_dwrapper) {
    int kLogInterval = 100;
    long dataset_size = *training_dwrapper.dataset.size();
    auto dataset = transforms(
            training_dwrapper.dataset,
            training_dwrapper.transforms.normalize,
            training_dwrapper.transforms.stack);
    auto dataloader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
            std::move(dataset),
            data::DataLoaderOptions().batch_size(training_dwrapper.batch_size).workers(4));

    model->train();
    for (long epoch = 0; epoch < training_dwrapper.epochs; ++epoch) {
        auto batch_idx = 0;
        for (auto& batch : *dataloader) {
            auto data = batch.data.to(device), targets = batch.target.to(device);
            optim->zero_grad();
            auto output = model->forward(data);
            auto loss = criterion(output, targets);
            loss.backward();
            optim->step();
            if (++batch_idx % kLogInterval == 0) {
                std::printf(
                        "\rTrain Epoch: %ld [%5lld/%5ld] Loss: %.4f \n",
                        epoch,
                        batch_idx * batch.data.size(0),
                        dataset_size,
                        loss.item().toDouble());
            }
        }
        eval(validation_dwrapper);
    }
}

template <typename T>
Tensor Agent<T>::loss(const Tensor& y, const Tensor& target) {
    return criterion(y, target);
}

template <typename T>
Tensor Agent<T>::acc(const Tensor& y, const Tensor& target) {
    return y.eq(target).to(kDouble).mean();
}

template <typename T>
void Agent<T>::eval(DatasetWrapper& dataset_wrapper) {
    auto dataset = transforms(
            dataset_wrapper.dataset,
            dataset_wrapper.transforms.normalize,
            dataset_wrapper.transforms.stack);
    auto dataloader = data::make_data_loader<data::samplers::SequentialSampler>(
            std::move(dataset),
            data::DataLoaderOptions().batch_size(dataset_wrapper.batch_size).workers(4));

    model->eval();
    std::vector<Tensor> loss_list {}, acc_list{};
    for (auto& batch : *dataloader) {
        auto data = batch.data.to(device), targets = batch.target.to(device);
        optim->zero_grad();
        auto output = model->forward(data);
        auto loss = criterion(output, targets);
        loss_list.push_back(loss);
        acc_list.push_back(acc(output.argmax(1), targets));
        loss.backward();
        optim->step();
    }

    std::printf(
            "\rValidation: Accuracy: %.4f, Loss: %.4f \n",
            torch::stack(TensorList(acc_list)).mean().item().toDouble(),
            torch::stack(TensorList(loss_list)).mean().item().toDouble());
}

template class Agent<nn::MSELoss>;

template class Agent<nn::NLLLoss>;
