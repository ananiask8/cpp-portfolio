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

tuple<shared_ptr<AgentBase>, shared_ptr<CustomDataset>, shared_ptr<CustomDataset>> Loader::process() {
    using namespace ConfigHelpers;
    namespace data = torch::data;
    namespace opt = torch::optim;
    namespace nn = torch::nn;

    nn::Module model;
    switch (models.at(dict.at("model_name"))) {
        case Model::BaselineStdMnist:
            model = BaselineStdMNIST();
        case Model::BaselineAdvMnist:
            // TODO
            break;
    }

    string dataset_path {dict.at("dataset_path")};
    switch (datasets.at(dict.at("dataset"))) {
        case Dataset::MNIST: {
            auto train_dataset = data::datasets::MNIST(dataset_path)
                    .map(data::transforms::Normalize<>(0.1307, 0.3081))
                    .map(data::transforms::Stack<>());
            auto train_loader = data::make_data_loader<data::samplers::SequentialSampler>(
                    std::move(train_dataset), std::stoi(dict.at("train_batch_size")));
            auto test_dataset = data::datasets::MNIST(dataset_path)
                    .map(data::transforms::Normalize<>(0.1307, 0.3081))
                    .map(data::transforms::Stack<>());
            auto test_loader = data::make_data_loader<data::samplers::SequentialSampler>(
                    std::move(test_dataset), std::stoi(dict.at("test_batch_size")));
//            return {*train_loader, *test_loader};
        }
        case Dataset::FashionMNIST:
            // TODO
            break;
    }

    double lr = std::stod(dict.at("lr"));
    std::shared_ptr<opt::Optimizer> optimizer {nullptr};
    switch (optimizers.at(dict.at("optimizer"))) {
        case Optimizer::Adam:
            optimizer = std::make_shared<opt::Adam>(opt::Adam(model.parameters(), opt::AdamOptions(lr)));
        case Optimizer::SGD:
            optimizer = std::make_shared<opt::SGD>(opt::SGD(model.parameters(), opt::SGDOptions(lr)));
    }

    std::shared_ptr<AgentBase> agent {nullptr};
    switch (losses.at(dict.at("criterion"))) {
        case Loss::MSE:
            agent = std::make_shared<Agent<nn::MSELoss>>(Agent<nn::MSELoss>(model, optimizer, nn::MSELoss()));
        case Loss::NLL:
            agent = std::make_shared<Agent<nn::NLLLoss>>(Agent<nn::NLLLoss>(model, optimizer, nn::NLLLoss()));
    }
    return {agent, nullptr, nullptr};
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
        cout << pair << endl;
    }
    return is;
}