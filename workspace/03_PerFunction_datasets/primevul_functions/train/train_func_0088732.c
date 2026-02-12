LogicalResult matchAndRewrite(TFL::FullyConnectedOp fc_op,
                                PatternRewriter &rewriter) const override {

    if (fc_op.weights_format() != "DEFAULT") return failure();


    auto mul_op = dyn_cast_or_null<TFL::MulOp>(fc_op.input().getDefiningOp());
    if (!mul_op) return failure();
    if (mul_op.fused_activation_function() != "NONE") return failure();


    {
      auto multiplier_shape = mul_op.rhs().getType().cast<ShapedType>();
      if (!multiplier_shape.hasStaticShape()) return failure();
      if (multiplier_shape.getShape().size() != 1) return failure();
    }


    if (!IsF32Value(mul_op.rhs()) || !IsF32Value(fc_op.filter())) {
      return failure();
    }

    auto location =
        FusedLoc::get(mul_op.getContext(), {mul_op.getLoc(), fc_op.getLoc()});

    auto new_filter = rewriter.create<TFL::MulOp>(
        location,
        fc_op.filter(),
        mul_op.rhs(),
        rewriter.getStringAttr("NONE"));

    auto new_fc = rewriter.create<TFL::FullyConnectedOp>(
        location, fc_op.output().getTypes(),
        mul_op.lhs(),
        new_filter,
        fc_op.bias(),

        rewriter.getStringAttr(fc_op.fused_activation_function()),
        rewriter.getStringAttr("DEFAULT"),
        rewriter.getBoolAttr(fc_op.keep_num_dims()));
    rewriter.replaceOp(fc_op.getOperation(), new_fc.output());

    return success();
  }
