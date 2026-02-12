LogicalResult DynamicBroadcastInDimOpLowering::matchAndRewrite(
    mhlo::DynamicBroadcastInDimOp op, mlir::PatternRewriter& rewriter) const {
  MLIRContext* ctx = getContext();

  auto in_type = op.operand().getType().dyn_cast<RankedTensorType>();
  auto out_type = op.getResult().getType().dyn_cast<RankedTensorType>();
  if (!in_type || !out_type) return failure();


  auto bcast_dims = op.broadcast_dimensions().getValues<int64_t>();
  auto expected_bcast_dims = llvm::seq<int64_t>(
      out_type.getRank() - in_type.getRank(), out_type.getRank());
  if (!llvm::equal(bcast_dims, expected_bcast_dims)) return failure();

  ShapeComponentAnalysis shape_component_analysis;
  auto input_map = isNonExpandingBroadcast(
      shape_component_analysis, op.operand(), op.output_dimensions());
  if (!input_map) return failure();


  SmallVector<Value> output_dyn_dimensions;
  Location loc = op.getLoc();
  int64_t rank = out_type.getRank();
  for (size_t d = 0; d < rank; ++d) {
    int64_t output_dim = out_type.getShape()[d];


    if (output_dim >= 0) continue;


    Value output_dyn_dim = rewriter.create<tensor::ExtractOp>(
        loc, op.output_dimensions(),
        ValueRange{rewriter.create<ConstantIndexOp>(loc, d)});


    if (!output_dyn_dim.getType().isIndex())
      output_dyn_dim = rewriter.create<IndexCastOp>(loc, output_dyn_dim,
                                                    rewriter.getIndexType());

    output_dyn_dimensions.push_back(output_dyn_dim);
  }


  Value init = rewriter.create<linalg::InitTensorOp>(loc, output_dyn_dimensions,
                                                     out_type.getShape(),
                                                     out_type.getElementType());


  AffineMap output_map = AffineMap::getMultiDimIdentityMap(rank, ctx);


  SmallVector<llvm::StringRef> iterator_types(rank, "parallel");

  rewriter.replaceOpWithNewOp<linalg::GenericOp>(
      op, TypeRange{init.getType()},
      ValueRange{op.operand()},
      ValueRange{init},
      llvm::makeArrayRef({*input_map, output_map}),
      iterator_types,
      [&](OpBuilder& nested_builder, Location nested_loc, ValueRange args) {
        nested_builder.create<linalg::YieldOp>(nested_loc, args[0]);
      });

  return success();
}
