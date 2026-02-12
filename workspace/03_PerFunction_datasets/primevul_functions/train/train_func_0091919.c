bool CreateUpdatedShapeProto(const NodeDef* node, TensorProto* proto) {
    Tensor shape;
    if (!GetTensorFromConstNode(node->name(), &shape)) {
      return false;
    }


    if (shape.dtype() != DT_INT32 || shape.NumElements() != 6) {
      return false;
    }

    const auto& shape_values = shape.flat<int32>();
    if (shape_values(2) != 1 || shape_values(4) != 1) {
      return false;
    }


    Tensor new_shape(DT_INT32, {4});
    new_shape.flat<int32>()(0) = shape_values(0);
    new_shape.flat<int32>()(1) = shape_values(1);
    new_shape.flat<int32>()(2) = shape_values(3);
    new_shape.flat<int32>()(3) = shape_values(5);

    new_shape.AsProtoTensorContent(proto);
    return true;
  }
