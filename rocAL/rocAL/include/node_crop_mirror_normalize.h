/*
Copyright (c) 2019 - 2020 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once
#include "node.h"
#include "parameter_factory.h"
#include "parameter_crop_factory.h"
#include "parameter_vx.h"
class CropMirrorNormalizeNode : public Node 
{
public:
    CropMirrorNormalizeNode(const std::vector<Image *> &inputs,
                            const std::vector<Image *> &outputs);
    CropMirrorNormalizeNode() = delete;
    void init(int crop_h, int crop_w, float start_x, float start_y, float mean, float std_dev, IntParam *mirror);
    vx_array return_mirror(){ return _mirror.default_array();  }
    std::shared_ptr<RaliCropParam> return_crop_param() { return _crop_param; }
    vx_array get_src_width() { return _src_roi_width; }
    vx_array get_src_height() { return _src_roi_height; }
protected:
    void create_node() override ;
    void update_node() override;
private:
    std::shared_ptr<RaliCropParam> _crop_param;
    std::vector<vx_float32> _mean_vx, _std_dev_vx;
    vx_array _mean_array, _std_dev_array;
    float _mean; 
    float _std_dev; 
    ParameterVX<int> _mirror;
    constexpr static int   MIRROR_RANGE [2] =  {0, 1};
};