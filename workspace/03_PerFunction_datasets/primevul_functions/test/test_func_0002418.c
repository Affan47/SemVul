Status SliceShape(InferenceContext* c) {
  ShapeHandle input = c->input(0);
  ShapeHandle begin_shape;
  TF_RETURN_IF_ERROR(c->WithRank(c->input(1), 1, &begin_shape));
  ShapeHandle sizes_shape;
  TF_RETURN_IF_ERROR(c->WithRank(c->input(2), 1, &sizes_shape));


  TF_RETURN_IF_ERROR(c->Merge(begin_shape, sizes_shape, &begin_shape));

  DimensionHandle ndims = c->Dim(begin_shape, 0);
  if (c->ValueKnown(ndims)) {
    TF_RETURN_IF_ERROR(c->WithRank(input, c->Value(ndims), &input));
  }


  ShapeHandle begin_value;
  TF_RETURN_IF_ERROR(c->MakeShapeFromShapeTensor(1, &begin_value));


  const Tensor* sizes_value = c->input_tensor(2);

  if (sizes_value != nullptr) {
    TF_RETURN_IF_ERROR(
        c->WithRank(begin_value, sizes_value->NumElements(), &begin_value));
    std::vector<DimensionHandle> dims;


    if (sizes_value->dtype() == DT_INT64) {
      TF_RETURN_IF_ERROR(
          SliceHelper<int64_t>(c, begin_value, sizes_value, &dims));
    } else {
      TF_RETURN_IF_ERROR(
          SliceHelper<int32>(c, begin_value, sizes_value, &dims));
    }
    c->set_output(0, c->MakeShape(dims));
    return Status::OK();
  } else {


    ShapeHandle sizes_value;
    TF_RETURN_IF_ERROR(c->MakeShapeFromShapeTensor(2, &sizes_value));
    if (c->RankKnown(sizes_value)) {
      TF_RETURN_IF_ERROR(
          c->WithRank(begin_value, c->Rank(sizes_value), &begin_value));
      std::vector<DimensionHandle> dims;
      dims.reserve(c->Rank(sizes_value));
      for (int i = 0; i < c->Rank(sizes_value); ++i) {
        dims.emplace_back(c->Dim(sizes_value, i));
      }
      c->set_output(0, c->MakeShape(dims));
      return Status::OK();
    }

    if (c->RankKnown(input)) {
      c->set_output(0, c->UnknownShapeOfRank(c->Rank(input)));
      return Status::OK();
    } else {
      return shape_inference::UnknownShape(c);
    }
  }

  return Status::OK();
}
