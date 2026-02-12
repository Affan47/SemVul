void OptimizePass::runOnFunction() {
  OwningRewritePatternList patterns(&getContext());
  auto *ctx = &getContext();
  auto func = getFunction();


  OwningRewritePatternList phase_0_patterns(&getContext());
  phase_0_patterns.insert<RemoveReshapeAfterFullyConnected,
                          RemoveReshapeBeforeFullyConnected>(ctx);
  (void)applyPatternsAndFoldGreedily(func, std::move(phase_0_patterns));


  TFL::populateWithGenerated(patterns);
  patterns.insert<FuseFullyConnectedAndAdd, FuseAddAndFullyConnected,
                  FuseFullyConnectedAndMul, FuseMulAndFullyConnected,
                  FuseFullyConnectedAndReluX<TFL::ReluOp, kRelu>,
                  FuseFullyConnectedAndReluX<TFL::Relu6Op, kRelu6>,
                  FuseFullyConnectedAndReluX<TFL::Relu1Op, kRelu1>>(ctx);
  if (enable_canonicalization_) AddCanonicalizationPatterns(ctx, &patterns);
  (void)applyPatternsAndFoldGreedily(func, std::move(patterns));


  OwningRewritePatternList phase_2_patterns(&getContext());
  TFL::populateWithGenerated(phase_2_patterns);
  phase_2_patterns.insert<
      ScalarizeSplatConstantForAdd, ScalarizeSplatConstantForSub,
      ScalarizeSplatConstantForMul, ScalarizeSplatConstantForDiv,
      FuseFullyConnectedAndAdd, FuseAddAndFullyConnected,
      FuseFullyConnectedAndMul, FuseMulAndFullyConnected,
      FuseFullyConnectedAndReluX<TFL::ReluOp, kRelu>,
      FuseFullyConnectedAndReluX<TFL::Relu6Op, kRelu6>,
      FuseFullyConnectedAndReluX<TFL::Relu1Op, kRelu1>,
      FuseBinaryOpToFollowingConv2D, FuseBinaryOpToFollowingDepthwiseConv2D,
      FuseBinaryOpToFollowingFullyConnected, FuseConv2DAndMulWithQDQs,
      FuseDepthwiseConv2DAndMulWithQDQs, ConvertTrivialTransposeOpToReshapeOp,
      RemoveReshapeAfterFullyConnected, RemoveReshapeBeforeFullyConnected,
      FuseUnpackAndConcatToReshape>(ctx);
  if (enable_canonicalization_)
    AddCanonicalizationPatterns(ctx, &phase_2_patterns);
  (void)applyPatternsAndFoldGreedily(func, std::move(phase_2_patterns));
}
