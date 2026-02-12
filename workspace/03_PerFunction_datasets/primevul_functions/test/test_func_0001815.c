bool isKnownBroadcastable(ShapeComponentAnalysis& analysis,
                          ValueRange bcasted_shapes, Value output_shape) {
  auto output_shape_dims = analysis.GetValueInfo(output_shape);
  if (!output_shape_dims) return false;
  for (Value shape : bcasted_shapes) {
    auto shape_dims = analysis.GetValueInfo(shape);
    if (!shape_dims) return false;

    for (auto zip : llvm::zip(llvm::reverse(*output_shape_dims),
                              llvm::reverse(*shape_dims))) {
      const auto& first = std::get<0>(zip);
      const auto& second = std::get<1>(zip);


      if (first.isConstant(0) || second.isConstant(0)) return false;


      if (first.isConstant(1) || second.isConstant(1)) continue;

      if (first != second) return false;
    }
  }
  return true;
}
