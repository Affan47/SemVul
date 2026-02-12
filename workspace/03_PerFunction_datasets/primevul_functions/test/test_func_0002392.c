Status ShapeFromDimensions(DimensionHandle batch_dim,
                           gtl::ArraySlice<DimensionHandle> spatial_dims,
                           DimensionHandle filter_dim, TensorFormat format,
                           absl::optional<DimensionHandle> vect_size,
                           InferenceContext* context, ShapeHandle* shape) {
  const int32_t rank =
      GetTensorDimsFromSpatialDims(spatial_dims.size(), format);
  std::vector<DimensionHandle> out_dims(rank);


  out_dims[tensorflow::GetTensorBatchDimIndex(rank, format)] = batch_dim;

  for (int spatial_dim_index = 0, end = spatial_dims.size();
       spatial_dim_index < end; ++spatial_dim_index) {
    out_dims[tensorflow::GetTensorSpatialDimIndex(
        rank, format, spatial_dim_index)] = spatial_dims[spatial_dim_index];
  }

  if (format == tensorflow::FORMAT_NCHW_VECT_C) {


    CHECK(vect_size.has_value());
    TF_RETURN_IF_ERROR(context->Divide(
        filter_dim, *vect_size, true,
        &out_dims[tensorflow::GetTensorFeatureDimIndex(rank, format)]));
    out_dims[GetTensorInnerFeatureDimIndex(rank, format)] = *vect_size;
  } else {
    out_dims[tensorflow::GetTensorFeatureDimIndex(rank, format)] = filter_dim;
  }

  *shape = context->MakeShape(out_dims);
  return tensorflow::Status::OK();
}
