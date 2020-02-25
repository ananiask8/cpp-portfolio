//
// Created by José Hilario on 24 Feb 2020.
//

#include "Dataset.h"

template <typename D>
std::shared_ptr<DatasetBase> wrap_dataset(D& loader) { return DatasetWrapper<D> {loader}; }
