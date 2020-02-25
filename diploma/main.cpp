#include <iostream>
#include "Config.h"
#include "Agent.h"
using namespace std;

int main(int argc, char* argv[]) {
    shared_ptr<AgentBase> agent {nullptr};
    if (argc > 1) {
        try {
            Loader config{argv[1], argv[2]};
            agent = config.process();
            auto datasets = load_dataset<torch::data::datasets::MNIST>(config);
        } catch (invalid_argument e) {
            cerr << "Wrong input!" << endl;
        }
    } else {
        cout << "Please provide the required arguments: " << endl
            << " [FILE] - configuration description file" << endl
            << " [DEVICE] - device to use (cuda:i, cpu)" << endl;
    }

    agent->train(train_dataset);
    agent->eval(test_dataset);

    return 0;
}
