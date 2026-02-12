Status EinsumShape(shape_inference::InferenceContext* c) {


  string equation;
  TF_RETURN_IF_ERROR(c->GetAttr("equation", &equation));
  gtl::InlinedVector<string, 2> input_labels;
  string output_labels;
  TF_RETURN_IF_ERROR(
      ParseEinsumEquation(equation, &input_labels, &output_labels));

  if (c->num_inputs() == 0 || c->num_inputs() > 2) {
    return errors::InvalidArgument("Expected either 1 or 2 inputs but got: ",
                                   c->num_inputs());
  }
  const int input_labels_size = input_labels.size();
  if (c->num_inputs() != input_labels_size) {
    return errors::InvalidArgument("Expected ", input_labels.size(),
                                   " inputs for equation ", equation,
                                   " but got: ", c->num_inputs());
  }


  absl::flat_hash_map<char, DimensionHandle> label_to_dimension;
  gtl::InlinedVector<ShapeHandle, 2> input_bcast_shapes(c->num_inputs());
  for (int i = 0, end = c->num_inputs(); i < end; ++i) {
    bool has_ellipsis = false;
    TF_RETURN_IF_ERROR(ValidateEinsumEllipsis(input_labels[i], &has_ellipsis));
    ShapeHandle input_shape = c->input(i);


    if (c->RankKnown(input_shape)) {
      if (has_ellipsis) {
        const int num_named_labels =
            static_cast<int>(input_labels[i].size()) - 3;
        TF_RETURN_WITH_CONTEXT_IF_ERROR(
            c->WithRankAtLeast(input_shape, num_named_labels, &input_shape),
            " for ", i, "th input and equation: ", equation);
      } else {
        const int num_named_labels = static_cast<int>(input_labels[i].size());
        TF_RETURN_WITH_CONTEXT_IF_ERROR(
            c->WithRank(input_shape, num_named_labels, &input_shape), " for ",
            i, "th input and equation: ", equation);
      }
    }

    bool seen_ellipsis = false;
    input_bcast_shapes[i] = c->Scalar();


    for (int label_idx = 0, end = input_labels[i].size(); label_idx < end;
         ++label_idx) {
      const char label = input_labels[i][label_idx];


      const int64_t axis_before_ellipsis = label_idx;
      const int64_t axis_after_ellipsis =
          c->RankKnown(input_shape)
              ? label_idx + c->Rank(input_shape) - input_labels[i].size()
              : -1;


      if (label == '.') {
        if (!c->RankKnown(input_shape)) {
          input_bcast_shapes[i] = c->UnknownShape();
        } else {


          TF_RETURN_IF_ERROR(c->Subshape(input_shape, axis_before_ellipsis,
                                         axis_after_ellipsis + 3,
                                         &input_bcast_shapes[i]));
        }
        label_idx += 2;
        seen_ellipsis = true;
        continue;
      }

      int64_t axis = seen_ellipsis ? axis_after_ellipsis : axis_before_ellipsis;
      DimensionHandle new_dim = c->RankKnown(input_shape)
                                    ? c->Dim(input_shape, axis)
                                    : c->UnknownDim();


      if (label_to_dimension.contains(label)) {
        DimensionHandle merged;
        TF_RETURN_IF_ERROR(
            c->Merge(label_to_dimension[label], new_dim, &merged));
        label_to_dimension[label] = merged;
      } else {
        label_to_dimension[label] = new_dim;
      }
    }
  }


  ShapeHandle output_bcast_shape;
  if (input_bcast_shapes.size() == 1) {
    output_bcast_shape = input_bcast_shapes[0];
  } else if (input_bcast_shapes.size() == 2) {
    TF_RETURN_IF_ERROR(BroadcastBinaryOpOutputShapeFnHelper(
        c, input_bcast_shapes[0], input_bcast_shapes[1], true,
        &output_bcast_shape));
  }

  bool output_has_ellipsis = false;
  TF_RETURN_IF_ERROR(
      ValidateEinsumEllipsis(output_labels, &output_has_ellipsis));
  if (output_has_ellipsis) {


    if (!c->RankKnown(output_bcast_shape)) {
      c->set_output(0, c->UnknownShape());
      return Status::OK();
    }
  } else {


    TF_RETURN_WITH_CONTEXT_IF_ERROR(
        c->WithRankAtMost(output_bcast_shape, 0, &output_bcast_shape),
        " for einsum equation '", equation,
        "' without ellipsis (...) in the output subscripts where input(s) have "
        "non-empty broadcasting shape");
    output_bcast_shape = c->Scalar();
  }


  std::vector<DimensionHandle> output_dims;
  for (int label_idx = 0, end = output_labels.size(); label_idx < end;
       ++label_idx) {
    const char label = output_labels[label_idx];

    if (label == '.') {
      for (int k = 0; k < c->Rank(output_bcast_shape); ++k) {
        output_dims.push_back(c->Dim(output_bcast_shape, k));
      }
      label_idx += 2;
      continue;
    }
    auto dimension_it = label_to_dimension.find(label);
    if (dimension_it == label_to_dimension.end()) {
      return errors::InvalidArgument(
          "Einsum output subscripts for equation '", equation, "' has label '",
          label, "' which is not present in the input subscripts");
    }
    output_dims.push_back(dimension_it->second);
  }
  c->set_output(0, c->MakeShape(output_dims));
  return Status::OK();
}
