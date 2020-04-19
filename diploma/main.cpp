#include <iostream>
#include "Config.h"
#include "Agent.h"
using namespace std;

int main(int argc, char* argv[]) {
    shared_ptr<AgentBase> agent {nullptr};
    shared_ptr<DatasetWrapper> train_dataset {nullptr};
    shared_ptr<DatasetWrapper> test_dataset {nullptr};
    if (argc > 1) {
        try {
            Loader config{argv[1], argv[2]};
            auto loaded = config.process();
            agent = get<0>(loaded);
            train_dataset = get<1>(loaded);
            test_dataset = get<2>(loaded);
        } catch (invalid_argument e) {
            cerr << "Wrong data!" << endl;
        }
    } else {
        cout << "Please provide the required arguments: " << endl
            << " [FILE] - configuration description file" << endl
            << " [DEVICE] - device to use (cuda:i, cpu)" << endl;
    }

    agent->train(*train_dataset, *test_dataset);

    return 0;
}
