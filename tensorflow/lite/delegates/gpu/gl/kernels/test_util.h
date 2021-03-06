/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_DELEGATES_GPU_GL_KERNELS_TEST_UTIL_H_
#define TENSORFLOW_LITE_DELEGATES_GPU_GL_KERNELS_TEST_UTIL_H_

#include <memory>
#include <vector>

#include "tensorflow/lite/delegates/gpu/common/model.h"
#include "tensorflow/lite/delegates/gpu/common/operations.h"
#include "tensorflow/lite/delegates/gpu/common/status.h"
#include "tensorflow/lite/delegates/gpu/common/tensor.h"
#include "tensorflow/lite/delegates/gpu/gl/compiler_options.h"
#include "tensorflow/lite/delegates/gpu/gl/node_shader.h"
#include "tensorflow/lite/delegates/gpu/gl/runtime_options.h"

namespace tflite {
namespace gpu {
namespace gl {

class SingleOpModel {
 public:
  SingleOpModel() = delete;
  SingleOpModel(Operation&& operation,
                const std::vector<TensorRefFloat32>& inputs,
                const std::vector<TensorRefFloat32>& outputs);

  virtual ~SingleOpModel() = default;

  bool PopulateTensor(int index, std::vector<float>&& data);

  bool Invoke(const NodeShader& shader) {
    return InvokeInternal(CompilationOptions(), RuntimeOptions(), shader).ok();
  }

  const std::vector<float>& GetOutput(int index) const {
    return outputs_[index].data;
  }

 protected:
  GraphFloat32 graph_;
  std::vector<TensorFloat32> inputs_;
  std::vector<TensorFloat32> outputs_;

 private:
  Status InvokeInternal(const CompilationOptions& compile_options,
                        const RuntimeOptions& runtime_options,
                        const NodeShader& shader);
};

}  // namespace gl
}  // namespace gpu
}  // namespace tflite

#endif  // TENSORFLOW_LITE_DELEGATES_GPU_GL_KERNELS_TEST_UTIL_H_
