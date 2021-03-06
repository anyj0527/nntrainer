// SPDX-License-Identifier: Apache-2.0-only
/**
 * Copyright (C) 2020 Parichay Kapoor <pk.kapoor@samsung.com>
 *
 * @file	addition_layer.cpp
 * @date	30 July 2020
 * @see		https://github.com/nnstreamer/nntrainer
 * @author	Parichay Kapoor <pk.kapoor@samsung.com>
 * @bug		No known bugs except for NYI items
 * @brief	This is Addition Layer Class for Neural Network
 *
 */

#include <addition_layer.h>
#include <layer.h>
#include <nntrainer_error.h>
#include <nntrainer_log.h>
#include <parse_util.h>
#include <util_func.h>

namespace nntrainer {

int AdditionLayer::initialize() {
  int status = ML_ERROR_NONE;
  if (num_inputs == 0) {
    ml_loge("Error: number of inputs are not initialized");
    return ML_ERROR_INVALID_PARAMETER;
  }

  if (input_dim.getDataLen() == 1) {
    ml_logw("Warning: the length of previous layer dimension is one");
  }

  /** input dimension indicates the dimension for all the inputs to follow */
  output_dim = input_dim;

  return status;
}

sharedConstTensor AdditionLayer::forwarding(sharedConstTensor in) {
  hidden = Tensor(in->batch(), output_dim.channel(), output_dim.height(),
                  output_dim.width());
  hidden.setZero();

  for (unsigned int idx = 0; idx < num_inputs; ++idx) {
    if (input_dim != in.get()[idx].getDim())
      throw std::runtime_error("Error: addition layer requires same "
                               "shape from all input layers");
    hidden.add_i(in.get()[idx]);
  }

  return MAKE_SHARED_TENSOR(hidden);
}

sharedConstTensor AdditionLayer::backwarding(sharedConstTensor derivative,
                                             int iteration) {
  sharedTensor ret = std::shared_ptr<Tensor>(new Tensor[num_inputs],
                                             std::default_delete<Tensor[]>());

  for (unsigned int idx = 0; idx < num_inputs; ++idx) {
    Tensor &t = ret.get()[idx];
    t = *derivative;
  }

  return ret;
}

void AdditionLayer::setProperty(const PropertyType type,
                                const std::string &value) {
  int status = ML_ERROR_NONE;

  switch (type) {
  case PropertyType::num_inputs: {
    if (!value.empty()) {
      status = setUint(num_inputs, value);
      throw_status(status);
      if (num_inputs < 1)
        throw std::invalid_argument("Minimum number of inputs must be 1");
    }
  } break;
  default:
    Layer::setProperty(type, value);
    break;
  }
}

void AdditionLayer::copy(std::shared_ptr<Layer> l) {
  std::shared_ptr<AdditionLayer> from =
    std::static_pointer_cast<AdditionLayer>(l);
  this->input.copy(from->input);
  this->hidden.copy(from->hidden);
  this->input_dim = from->input_dim;
  this->output_dim = from->output_dim;
}

} /* namespace nntrainer */
