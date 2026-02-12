TEST(ArrayOpsTest, ExtractImagePatchesShapeTest) {
  ShapeInferenceTestOp op("ExtractImagePatches");
  auto set_op = [&op](const std::vector<int32>& ksizes,
                      const std::vector<int32>& strides,
                      const std::vector<int32>& rates, const string& padding) {
    TF_ASSERT_OK(NodeDefBuilder("test", "ExtractImagePatches")
                     .Input("input", 0, DT_FLOAT)
                     .Attr("ksizes", ksizes)
                     .Attr("strides", strides)
                     .Attr("rates", rates)
                     .Attr("padding", padding)
                     .Finalize(&op.node_def));
  };


  set_op({1, 2, 2, 1}, {1, 1, 1, 1}, {1, 2, 2, 1}, "VALID");
  INFER_OK(op, "[1,7,7,2]", "[d0_0,5,5,8]");


  set_op({1, 1, 1, 1}, {1, 1, 1, 1}, {1, 2, 2, 1}, "VALID");
  INFER_OK(op, "[1,7,7,2]", "[d0_0,7,7,d0_3]");


  set_op({1, 2, 2, 1, 1}, {1, 1, 1, 1}, {1, 2, 2, 1}, "VALID");
  INFER_ERROR(
      "ExtractImagePatches requires the ksizes attribute to contain 4 values, "
      "but got: 5",
      op, "[1,7,7,2]");
}
