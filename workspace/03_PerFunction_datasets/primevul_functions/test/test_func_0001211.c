bool IsValidConstShapeForMulConvPushDown(
    const string& data_format, const TensorShapeProto& filter_shape,
    const TensorShapeProto& mul_const_input_shape) {


  if (mul_const_input_shape.dim_size() <=
          static_cast<int>(data_format.size()) &&
      TensorShape(mul_const_input_shape).num_elements() == 1) {
    return true;
  }


  if (data_format == "NHWC" || data_format == "NDHWC") {
    TensorShapeProto new_filter_shape;
    if (!ShapeAfterBroadcast(filter_shape, mul_const_input_shape,
                             &new_filter_shape)) {
      return false;
    }
    if (!ShapesSymbolicallyEqual(filter_shape, new_filter_shape)) {
      return false;
    }


    for (int i = 0; i < mul_const_input_shape.dim_size() - 1; ++i) {
      if (mul_const_input_shape.dim(i).size() > 1) return false;
    }
    return true;
  } else if (data_format == "NCHW" || data_format == "NCDHW") {

    return false;
  }
  return false;
}
