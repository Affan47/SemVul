bool MaybeTensorValueToShape(InferenceContext* ic, const Tensor& tensor,
                               ShapeHandle* tensors_as_shapes) {


    if (IsIntegerVector(tensor)) {
      bool has_values_smaller_than_minus_1 = false;
      std::vector<DimensionHandle> dims;
      for (int i = 0; i < tensor.NumElements(); i++) {
        int64_t value = tensor.dtype() == DT_INT32 ? tensor.flat<int32>()(i)
                                                   : tensor.flat<int64_t>()(i);
        has_values_smaller_than_minus_1 |= (value < -1);

        dims.push_back(value < 0 ? ic->MakeDim(kUnknownDimFromConst)
                                 : ic->MakeDim(value));
      }

      if (!has_values_smaller_than_minus_1) {
        *tensors_as_shapes = ic->MakeShape(dims);
        return true;
      }
    } else if (IsIntegerScalar(tensor)) {

      int64_t value = tensor.dtype() == DT_INT32 ? tensor.flat<int32>()(0)
                                                 : tensor.flat<int64_t>()(0);
      if (value == -1) {


        *tensors_as_shapes = ic->UnknownShape();
        return true;
      } else if (value >= 0) {


        *tensors_as_shapes = ic->MakeShape({ic->MakeDim(value)});
        return true;
      }
    }
    return false;
  }
