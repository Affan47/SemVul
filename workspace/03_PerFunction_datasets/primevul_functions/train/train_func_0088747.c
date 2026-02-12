LogicalResult matchAndRewrite(TFL::AddOp add_op,
                                PatternRewriter &rewriter) const override {

    DenseElementsAttr added_value;
    Value constant_val = add_op.rhs();
    if (!matchPattern(constant_val, m_Constant(&added_value))) return failure();


    auto fc_op =
        dyn_cast_or_null<TFL::FullyConnectedOp>(add_op.lhs().getDefiningOp());
    if (!fc_op) return failure();


    auto constant_val_type = constant_val.getType().cast<TensorType>();


    bool is_scalar_rhs = false;
    if (constant_val_type.getRank() == 0) {
      is_scalar_rhs = true;
    } else if (constant_val_type.getRank() != 1) {
      return failure();
    }

    Value filter = fc_op.filter();
    Value bias = fc_op.bias();
    ElementsAttr bias_value;
    const bool is_none_bias = bias.getType().isa<NoneType>();
    if (fc_op.fused_activation_function() != "NONE") return failure();

    if (!is_none_bias && !matchPattern(bias, m_Constant(&bias_value)))
      return failure();


    if (is_none_bias) {
      if (is_scalar_rhs) {


        auto filter_type = filter.getType().dyn_cast<RankedTensorType>();


        if (filter_type == nullptr || filter_type.getRank() != 2) {
          return failure();
        }
        int num_channels = filter_type.getShape()[0];


        RankedTensorType type = RankedTensorType::get(
            {num_channels}, constant_val_type.getElementType());
        auto attr = rewriter.getZeroAttr(type);
        bias = rewriter.create<ConstantOp>(add_op.getLoc(), type, attr);
        auto none_af = rewriter.getStringAttr("NONE");
        bias =
            rewriter.create<AddOp>(add_op.getLoc(), bias, constant_val, none_af)
                .output();
      } else {


        bias = constant_val;
      }
    } else {
      auto none_af = rewriter.getStringAttr("NONE");
      bias =
          rewriter.create<AddOp>(add_op.getLoc(), bias, constant_val, none_af)
              .output();
    }

    auto fc = rewriter.create<TFL::FullyConnectedOp>(
        FusedLoc::get(fc_op.getContext(), {fc_op.getLoc(), add_op.getLoc()}),
        add_op.getType(),
        fc_op.input(),
        filter,
        bias,

        rewriter.getStringAttr(add_op.fused_activation_function()),
        rewriter.getStringAttr(fc_op.weights_format()),
        rewriter.getBoolAttr(fc_op.keep_num_dims()));
    rewriter.replaceOp(add_op, fc.output());

    return success();
  }
