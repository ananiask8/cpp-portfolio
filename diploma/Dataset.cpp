//
// Created by José Hilario on 24 Feb 2020.
//

#include "Dataset.h"

using namespace torch;

torch::data::Example<> CustomDataset::get(size_t index) { return {data[index], target[index]}; }
torch::optional<size_t> CustomDataset::size() const { return target.size(0); }
//
//Tensor MNIST::read_data(const std::string& root, bool train) {
//    const auto path = root + (train ? "_train" : "_test");
//
//    // Load images
//    std::ifstream images(path, std::ios::binary);
//    TORCH_CHECK(images, "Error opening images file at ", path);
////     kTrainSize = len(training_data)
////     kTestSize = len(testing_data)
////    const auto count = train ? kTrainSize : kTestSize;
//
//    // Specific to MNIST data
//    // From http://yann.lecun.com/exdb/mnist/
//    expect_int32(images, kImageMagicNumber);
//    expect_int32(images, count);
//    expect_int32(images, kImageRows);
//    expect_int32(images, kImageColumns);
//
//    // This converts images to tensors
//    // Allocate an empty tensor of size of image (count, channels, height, width)
//    auto tensor =
//            torch::empty({count, 1, kImageRows, kImageColumns}, torch::kByte);
//    // Read image and convert to tensor
//    images.read(reinterpret_cast<char *>(tensor.data_ptr()), tensor.numel());
//    // Normalize the image from 0 to 255 to 0 to 1
//    return tensor.to(torch::kFloat32).div_(255);
//}