//
// Created by José Hilario on 19 Feb 2020.
//

#include <torch/torch.h>
#include "Config.h"
#include "models/BaselineStdMNIST.h"
#include "Dataset.h"

using namespace std;

namespace ConfigHelpers {
    map<std::string, Model> models {
        { "baseline_std_mnist", Model::BaselineStdMnist },
        { "baseline_adv_mnist", Model::BaselineAdvMnist }

    };
    map<std::string, Optimizer> optimizers {
            { "adam", Optimizer::Adam },
            { "sgd", Optimizer::SGD }
    };
    map<std::string, Loss> losses {
            { "nll", Loss::NLL },
            { "mse", Loss::MSE }
    };
    map<std::string, Dataset> datasets {
            { "mnist", Dataset::MNIST },
            { "fashion_mnist", Dataset::FashionMNIST }
    };
}

Loader::Loader(string filename, string device_id) : file{filename}, device{device_id} {
    ifstream in;
    try {
        in.open(filename);
    } catch (invalid_argument e) {
        cerr << "Invalid path for file." << endl;
    } catch (exception e) {
        cerr << "Wrong data: " << e.what() << endl;
    }
    in >> *this;
}

class FoldBase {
public:

};

//template<typename Head, typename... Tail>
//class Fold {
//public:
//    Fold(Head h, Tail... t) {
//        this.data = transforms(h, t...);
//    }
//    auto load() {
//        return torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
//                move(CustomDataset("dataset_path")), stoi("dict.at(train_batch_size)"));
//    }
//};


//tuple<
//        shared_ptr<AgentBase>,
//        pair<CustomDataset, CustomDataset>,
//        torch::data::transforms::Normalize<>, torch::data::transforms::Stack<>> Loader::process() {
//tuple<shared_ptr<AgentBase>, shared_ptr<CustomDataset>, shared_ptr<CustomDataset>> Loader::process() {

std::shared_ptr<AgentBase> Loader::get_agent() {
    using namespace ConfigHelpers;
    namespace data = torch::data;
    namespace opt = torch::optim;
    namespace nn = torch::nn;

    std::shared_ptr<NeuralNetworkBase> model;
    switch (models.at(dict.at("model_name"))) {
        case Model::BaselineStdMnist:
            model = std::make_shared<BaselineStdMNISTImpl>(BaselineStdMNISTImpl());
        case Model::BaselineAdvMnist:
            // TODO
            break;
    }

    double lr = std::stod(dict.at("learning_rate"));
    std::shared_ptr<opt::Optimizer> optimizer {nullptr};
    switch (optimizers.at(dict.at("optimizer"))) {
        case Optimizer::Adam:
            optimizer = std::make_shared<opt::Adam>(opt::Adam(model->parameters(), opt::AdamOptions(lr)));
        case Optimizer::SGD:
            optimizer = std::make_shared<opt::SGD>(opt::SGD(model->parameters(), opt::SGDOptions(lr)));
    }

    std::shared_ptr<AgentBase> agent {nullptr};
    switch (losses.at(dict.at("criterion"))) {
        case Loss::MSE:
            agent = std::make_shared<Agent<nn::MSELoss>>(Agent<nn::MSELoss>(model, optimizer, nn::MSELoss(), device));
        case Loss::NLL:
            agent = std::make_shared<Agent<nn::NLLLoss>>(Agent<nn::NLLLoss>(model, optimizer, nn::NLLLoss(), device));
    }
    return agent;
}

//template <typename... ARGS>
//class TransformsWrapper {
//    TransformsWrapper(tuple<ARGS...> transforms) {
//
//    }
//
//    ARGS...
//};

pair<shared_ptr<DatasetWrapper>, shared_ptr<DatasetWrapper>> Loader::get_dataset() {
    using namespace ConfigHelpers;
    namespace data = torch::data;
    namespace opt = torch::optim;
    namespace nn = torch::nn;

    string dataset_path {dict.at("dataset_path")};
    switch (datasets.at(dict.at("dataset"))) {
        case Dataset::MNIST: {
            auto transforms{DatasetTransforms()};
            transforms.normalize = std::make_shared<data::transforms::Normalize<>>(data::transforms::Normalize<>(0.1307, 0.3081));
            transforms.stack = std::make_shared<data::transforms::Stack<>>(data::transforms::Stack<>());
            auto train_dataset = make_shared<DatasetWrapper>(DatasetWrapper(
                    CustomDataset(dataset_path),
                    transforms,
                    std::stoi(dict.at("train_batch_size")),
                    std::stoi(dict.at("n_epochs"))));

            auto test_dataset = make_shared<DatasetWrapper>(DatasetWrapper(
                    CustomDataset(dataset_path, CustomDataset::Mode::kTest),
                    transforms,
                    std::stoi(dict.at("test_batch_size"))));

            return make_pair(move(train_dataset), move(test_dataset));
        }
        case Dataset::FashionMNIST:
            // TODO
            break;
    }
}

tuple<
    shared_ptr<AgentBase>,
    shared_ptr<DatasetWrapper>,
    shared_ptr<DatasetWrapper>> Loader::process() {
    auto dataset = get_dataset();
    return make_tuple(get_agent(), dataset.first, dataset.second);
}

class KeyValuePair : public string {};
istream& operator>>(istream& is, KeyValuePair& line) {
    getline(is, line, '=');
    return is;
}

istream& operator>>(istream& is, Loader& cfg) {
    string line;
    while(getline(is, line)) {
        istringstream iss{line};
        vector<string> pair{istream_iterator<KeyValuePair>(iss),
                            istream_iterator<KeyValuePair>()};
        cfg.dict[pair[0]] = pair[1];
    }
    return is;
}