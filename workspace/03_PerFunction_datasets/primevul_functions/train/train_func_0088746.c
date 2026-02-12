LogicalResult matchAndRewrite(TFL::FullyConnectedOp fc_op,
                                PatternRewriter &rewriter) const override {

    if (fc_op.weights_format() != "DEFAULT") return failure();


    auto add_op = dyn_cast_or_null<TFL::AddOp>(fc_op.input().getDefiningOp());
    if (!add_op) return failure();
    if (add_op.fused_activation_function() != "NONE") return failure();


    {
      auto addend_shape = add_op.rhs().getType().cast<ShapedType>();
      if (!addend_shape.hasStaticShape()) return failure();
      if (addend_shape.getShape().size() != 1) return failure();
    }


    auto old_bias = fc_op.bias();
    if (!old_bias || old_bias.getType().isa<NoneType>()) {

      return failure();
    }


    {
      if (!IsF32Value(add_op.rhs()) || !IsF32Value(fc_op.filter()) ||
          !IsF32Value(old_bias))
        return failure();
    }

    auto new_bias = rewriter.create<TFL::FullyConnectedOp>(
        fc_op.getLoc(), old_bias.getType(),
        add_op.rhs(),
        fc_op.filter(),
        old_bias,
        rewriter.getStringAttr("NONE"),
        rewriter.getStringAttr("DEFAULT"),
        rewriter.getBoolAttr(true));


    auto new_fc = rewriter.create<TFL::FullyConnectedOp>(
        FusedLoc::get(add_op.getContext(), {add_op.getLoc(), fc_op.getLoc()}),
        fc_op.output().getTypes(),
        add_op.lhs(),
        fc_op.filter(),
        *new_bias.output().begin(),

        rewriter.getStringAttr(fc_op.fused_activation_function()),
        rewriter.getStringAttr("DEFAULT"),
        rewriter.getBoolAttr(fc_op.keep_num_dims()));
    rewriter.replaceOp(fc_op.getOperation(), new_fc.output());

    return success();
  }
