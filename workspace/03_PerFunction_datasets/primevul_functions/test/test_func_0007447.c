bool should_run_in_pool(BundleReader* reader) const {
    TensorShape restored_full_shape;


    if (!reader->LookupTensorShape(tensor_name, &restored_full_shape).ok()) {
      return false;
    }

    return restored_full_shape.num_elements() > kLargeShapeThreshold;
  }
