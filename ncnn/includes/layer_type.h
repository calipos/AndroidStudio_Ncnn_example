// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef NCNN_LAYER_TYPE_H
#define NCNN_LAYER_TYPE_H

namespace ncnn {

namespace LayerType {
enum
{
    AbsVal = 0,
    ArgMax = 1,
    BatchNorm = 2,
    Bias = 3,
    BNLL = 4,
    Concat = 5,
    Convolution = 6,
    Crop = 7,
    Deconvolution = 8,
    Dropout = 9,
    Eltwise = 10,
    ELU = 11,
    Embed = 12,
    Exp = 13,
    Flatten = 14,
    InnerProduct = 15,
    Input = 16,
    Log = 17,
    LRN = 18,
    MemoryData = 19,
    MVN = 20,
    Pooling = 21,
    Power = 22,
    PReLU = 23,
    Proposal = 24,
    Reduction = 25,
    ReLU = 26,
    Reshape = 27,
    ROIPooling = 28,
    Scale = 29,
    Sigmoid = 30,
    Slice = 31,
    Softmax = 32,
    Split = 33,
    SPP = 34,
    TanH = 35,
    Threshold = 36,
    Tile = 37,
    RNN = 38,
    LSTM = 39,
    BinaryOp = 40,
    UnaryOp = 41,
    ConvolutionDepthWise = 42,
    Padding = 43,
    Squeeze = 44,
    ExpandDims = 45,
    Normalize = 46,
    Permute = 47,
    PriorBox = 48,
    DetectionOutput = 49,
    Interp = 50,
    DeconvolutionDepthWise = 51,
    ShuffleChannel = 52,
    InstanceNorm = 53,
    Clip = 54,
    Reorg = 55,
    YoloDetectionOutput = 56,
    Quantize = 57,
    Dequantize = 58,
    CustomBit = (1<<8),
};
} // namespace LayerType

} // namespace ncnn

#endif // NCNN_LAYER_TYPE_H
