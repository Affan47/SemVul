inline SparseTensor SparseTensor::Slice(const SparseTensor& input_tensor,
                                        const gtl::ArraySlice<int64>& start,
                                        const gtl::ArraySlice<int64>& size) {
  TensorShape output_shape(input_tensor.shape());

  const int dims = input_tensor.dims();
  for (int dim = 0; dim < dims; dim++) {


    const int64 input_size = output_shape.dim_size(dim);
    const int64 start_index = start[dim];
    const int64 slice_size = size[dim];
    if (start_index + slice_size < input_size) {

      output_shape.set_dim(dim, slice_size);
    } else if (start_index < input_size) {

      output_shape.set_dim(dim, input_size - start_index);
    } else {

      output_shape.set_dim(dim, 0);
    }
  }

  auto input_indices_t = input_tensor.indices().matrix<int64>();
  auto input_values_t = input_tensor.values().vec<T>();


  int count = 0;
  for (int i = 0; i < input_tensor.indices().dim_size(0); i++) {


    bool hit = true;
    for (int dim = 0; dim < dims; dim++) {
      if (!(start[dim] <= input_indices_t(i, dim) &&
            input_indices_t(i, dim) < start[dim] + size[dim])) {
        hit = false;
        break;
      }
    }
    if (!hit) {
      continue;
    }
    count++;
  }

  Tensor output_values(DataTypeToEnum<T>::v(), TensorShape({count}));
  Tensor output_indices(DT_INT64, TensorShape({count, dims}));

  auto output_values_t = output_values.vec<T>();
  auto output_indices_t = output_indices.matrix<int64>();


  int index = 0;
  for (int i = 0; i < input_tensor.indices().dim_size(0) && index < count;
       i++) {


    bool hit = true;
    for (int dim = 0; dim < dims; dim++) {
      if (!(start[dim] <= input_indices_t(i, dim) &&
            input_indices_t(i, dim) < start[dim] + size[dim])) {
        hit = false;
        break;
      }
    }
    if (!hit) {
      continue;
    }
    output_values_t(index) = input_values_t(i);
    for (int dim = 0; dim < dims; dim++) {
      output_indices_t(index, dim) = input_indices_t(i, dim) - start[dim];
    }
    index++;
  }

  return SparseTensor(output_indices, output_values, output_shape);
}
