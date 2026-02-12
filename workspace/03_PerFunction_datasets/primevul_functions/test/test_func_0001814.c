void runOnFunction() override {
    FuncOp func = getFunction();

    MLIRContext* ctx = &getContext();
    mlir::RewritePatternSet patterns(ctx);


    patterns.insert<CstrBroadcastableOpLowering>(ctx);

    patterns.insert<BroadcastOpLowering>(ctx);


    if (!optimize_only_constraints)
      patterns.insert<DynamicBroadcastInDimOpLowering>(ctx);


    for (auto op : ctx->getRegisteredOperations()) {
      if (llvm::isa<shape::ShapeDialect>(op.getDialect()))
        op.getCanonicalizationPatterns(patterns, ctx);
    }

    (void)mlir::applyPatternsAndFoldGreedily(func, std::move(patterns));
  }
