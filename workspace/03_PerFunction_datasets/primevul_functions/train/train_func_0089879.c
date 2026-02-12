void Compute(OpKernelContext* context) override {

    Tensor encoded_variant = context->input(0);
    Tensor row_splits = context->input(1);
    auto flat_row_splits = row_splits.flat<SPLIT_TYPE>();
    TensorShape dense_values_shape;
    OP_REQUIRES_OK(context,
                   TensorShapeUtils::MakeShape(context->input(2).vec<int32>(),
                                               &dense_values_shape));

    const auto& flat_variants = encoded_variant.flat<Variant>();


    std::vector<Tensor> values;
    for (int i = 0; i < flat_variants.size(); ++i) {
      if (const auto* encoded = flat_variants(i).get<RaggedTensorVariant>()) {
        values.push_back(encoded->values());
      } else {


        const auto value_dtype = DataTypeToEnum<VALUE_TYPE>::v();
        int piece_size = flat_row_splits(i + 1) - flat_row_splits(i);
        TensorShape zeros_shape = dense_values_shape;
        zeros_shape.set_dim(0, piece_size);
        Tensor zero(value_dtype, zeros_shape);
        zero.flat<VALUE_TYPE>() =
            zero.flat<VALUE_TYPE>().constant(VALUE_TYPE());
        values.push_back(zero);
      }
    }

    if (values.size() == 1) {

      context->set_output(0, values[0]);
    } else {

      using Piece = typename TTypes<VALUE_TYPE, 2>::Matrix;
      using ConstPiece = typename TTypes<VALUE_TYPE, 2>::ConstMatrix;
      std::vector<std::unique_ptr<ConstPiece>> pieces;
      pieces.reserve(values.size());
      for (const Tensor& t : values) {
        pieces.emplace_back(
            new ConstPiece(t.shaped<VALUE_TYPE, 2>({1, t.NumElements()})));
      }
      Tensor* out = nullptr;
      OP_REQUIRES_OK(context,
                     context->allocate_output(0, dense_values_shape, &out));
      Piece out_flat =
          out->shaped<VALUE_TYPE, 2>({1, dense_values_shape.num_elements()});
      ConcatCPU<VALUE_TYPE>(context->device(), pieces, &out_flat);
    }
  }
