// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <vector>

#include "paddle/fluid/framework/details/execution_strategy.h"
#include "paddle/fluid/framework/ir/graph.h"
#include "paddle/fluid/framework/parallel_executor.h"
#include "paddle/fluid/framework/scope.h"

#include "paddle/fluid/jit/function/base_function.h"
#include "paddle/fluid/jit/function_schema.h"
#include "paddle/fluid/jit/function_utils.h"

namespace paddle {
namespace jit {

using ExecutionStrategy = framework::details::ExecutionStrategy;
using ParallelExecutor = framework::ParallelExecutor;
using Graph = framework::ir::Graph;

class PEFunction : public BaseFunction {
 public:
  PEFunction(const std::shared_ptr<FunctionInfo> &info,
             const Name2VariableMap &params_dict,
             const phi::Place &place);

  ~PEFunction() noexcept {}

  void CreateGraphAndPE();

  std::vector<Tensor> operator()(const std::vector<Tensor> &inputs);

  std::vector<DenseTensor> operator()(const std::vector<DenseTensor> &inputs);

  const std::shared_ptr<FunctionInfo> &Info() const;

 private:
  std::shared_ptr<FunctionInfo> info_;
  framework::Scope scope_;
  phi::Place place_;
  std::shared_ptr<ParallelExecutor> inner_pe_;
  std::shared_ptr<Graph> graph_;
};

}  // namespace jit
}  // namespace paddle
