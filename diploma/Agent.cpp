//
// Created by José Hilario on 19 Feb 2020.
//

#include "Agent.h"

template <typename T>
void Agent<T>::train(std::shared_ptr<DatasetBase>& data) {
    model.train();
    size_t batch_idx = 0;
    for (auto& batch : data->get_loader()) {
        std::cout << batch.data << std::endl;
//        auto data = batch.data.to(device), targets = batch.target.to(device);
//        optimizer.zero_grad();
//        auto output = model.forward(data);
//        auto loss = torch::nll_loss(output, targets);
//        AT_ASSERT(!std::isnan(loss.template item<float>()));
//        loss.backward();
//        optimizer.step();
//
//        if (batch_idx++ % kLogInterval == 0) {
//            std::printf(
//                    "\rTrain Epoch: %ld [%5ld/%5ld] Loss: %.4f",
//                    epoch,
//                    batch_idx * batch.data.size(0),
//                    dataset_size,
//                    loss.template item<float>());
//        }
    }
}

template <typename T>
void Agent<T>::eval(std::shared_ptr<DatasetBase>&data) {

}