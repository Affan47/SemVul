Status TensorSlice::SliceTensorShape(const TensorShape& shape,
                                     TensorShape* result_shape) const {
  result_shape->Clear();

  if (shape.dims() != dims()) {
    return errors::Internal("Mismatching ranks: shape = ", shape.DebugString(),
                            ", slice = ", DebugString());
  }
  for (int d = 0; d < dims(); ++d) {
    if (IsFullAt(d)) {
      result_shape->AddDim(shape.dim_size(d));
    } else {

      if (end(d) <= shape.dim_size(d)) {


        result_shape->AddDim(length(d));
      } else {

        result_shape->Clear();
        return errors::Internal("Extent in dimension ", d,
                                " out of bounds: shape = ", shape.DebugString(),
                                ", slice = ", DebugString());
      }
    }
  }

  return Status::OK();
}
