::tensorflow::Status MakeSplits(
      const Tensor& indices_in, const OpInputList& params_nested_splits_in,
      SPLITS_TYPE num_params_dense_values,
      std::vector<std::vector<SPLITS_TYPE>>* out_splits,
      std::vector<std::pair<SPLITS_TYPE, SPLITS_TYPE>>* value_slices,
      SPLITS_TYPE* num_values) {
    *num_values = 0;
    value_slices->clear();

    int num_splits = indices_in.dims() - 1 + params_nested_splits_in.size();
    out_splits->assign(num_splits, {0});


    const auto& indices = indices_in.flat<INDEX_TYPE>();
    std::vector<ConstFlatType> params_nested_splits;
    params_nested_splits.reserve(params_nested_splits_in.size());
    for (const auto& splits_in : params_nested_splits_in) {
      params_nested_splits.push_back(splits_in.flat<SPLITS_TYPE>());
    }

    TF_RETURN_IF_ERROR(
        ValidateSplits(params_nested_splits, num_params_dense_values));


    int nrows = 1;
    for (int dim = 0; dim < indices_in.dims() - 1; ++dim) {
      nrows *= indices_in.dim_size(dim);
      int row_length = indices_in.dim_size(dim + 1);
      for (int i = 1; i < nrows + 1; ++i) {
        out_splits->at(dim).push_back(i * row_length);
      }
    }


    for (int i = 0; i < indices.size(); ++i) {
      int start = indices(i);
      int limit = indices(i) + 1;


      for (int dim = 0; dim < params_nested_splits.size(); ++dim) {
        const auto& splits = params_nested_splits[dim];
        int out_dim = dim + indices_in.dims() - 1;
        if (out_dim >= 0) {
          SPLITS_TYPE delta = out_splits->at(out_dim).back() - splits(start);
          for (int j = start; j < limit; ++j) {
            out_splits->at(out_dim).push_back(splits(j + 1) + delta);
          }
        }
        start = splits(start);
        limit = splits(limit);
      }
      if (limit != start) {
        value_slices->emplace_back(start, limit);
        *num_values += limit - start;
      }
    }
    return ::tensorflow::Status::OK();
  }
