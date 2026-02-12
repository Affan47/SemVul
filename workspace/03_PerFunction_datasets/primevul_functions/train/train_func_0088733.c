LogicalResult matchAndRewrite(TFL::MulOp mul_op,
                                PatternRewriter &rewriter) const override {


    if (mul_op.lhs().getType() != mul_op.getType()) return failure();


    DenseElementsAttr cst;
    Value constant_val = mul_op.rhs();
    if (!matchPattern(constant_val, m_Constant(&cst))) return failure();


    auto fc_op =
        dyn_cast_or_null<TFL::FullyConnectedOp>(mul_op.lhs().getDefiningOp());
    if (!fc_op) return failure();
    Value filter = fc_op.filter();
    Value bias = fc_op.bias();
    ElementsAttr cst_tmp;
    if (!matchPattern(filter, m_Constant(&cst_tmp))) return failure();
    if (!bias.getType().isa<NoneType>() &&
        !matchPattern(bias, m_Constant(&cst_tmp)))
      return failure();
    if (fc_op.fused_activation_function() != "NONE") return failure();


    auto shape = cst.getType().getShape();
    if (!IsDimensionsDegenerateExceptLastOne(shape)) return failure();

    int64_t element_size = shape.empty() ? 1 : shape[shape.size() - 1];


    int64_t normalized_shape[2] = {element_size, 1};
    auto new_cst = cst.reshape(RankedTensorType::get(
        normalized_shape, cst.getType().getElementType()));
    Type new_type = new_cst.getType();
    if (!IsBroadcastableElementsAttrAndType(new_type, filter.getType())) {
      return failure();
    }

    auto new_op =
        rewriter.create<ConstantOp>(mul_op.getLoc(), new_type, new_cst);
    Value new_const_val = new_op.getResult();


    auto new_filter =
        rewriter.create<TF::MulOp>(mul_op.getLoc(), filter, new_const_val).z();

    if (!bias.getType().isa<NoneType>()) {
      bias =
          rewriter.create<TF::MulOp>(mul_op.getLoc(), bias, constant_val).z();
    }

    auto fc = rewriter.create<TFL::FullyConnectedOp>(
        FusedLoc::get(fc_op.getContext(), {fc_op.getLoc(), mul_op.getLoc()}),
        mul_op.getType(),
        fc_op.input(),
        new_filter,
        bias,

        rewriter.getStringAttr(mul_op.fused_activation_function()),
        rewriter.getStringAttr(fc_op.weights_format()),
        rewriter.getBoolAttr(fc_op.keep_num_dims()));
    rewriter.replaceOp(mul_op, fc.output());

    return success();
  }
