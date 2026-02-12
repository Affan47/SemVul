TEST(ArrayOpsTest, Squeeze_ShapeFn) {
  ShapeInferenceTestOp op("Squeeze");

  auto rebuild_node_def = [&op](const std::vector<int32>& squeeze_dims) {
    TF_ASSERT_OK(NodeDefBuilder("test", "Squeeze")
                     .Input("input", 0, DT_FLOAT)
                     .Attr("squeeze_dims", squeeze_dims)
                     .Finalize(&op.node_def));
  };


  rebuild_node_def({});


  INFER_OK(op, "?", "?");

  INFER_OK(op, "[1,4,1,5,1]", "[d0_1,d0_3]");


  INFER_OK(op, "[1,?,1,?,1]", "?");


  rebuild_node_def({1});
  INFER_OK(op, "[4,1,5]", "[d0_0,d0_2]");

  INFER_OK(op, "[4,?,5]", "[d0_0,d0_2]");


  INFER_ERROR("Can not squeeze dim[1]", op, "[4,6,5]");


  rebuild_node_def({1, 2});
  INFER_OK(op, "[4,1,1,5]", "[d0_0,d0_3]");
  rebuild_node_def({1, -2});
  INFER_OK(op, "[4,1,1,5]", "[d0_0,d0_3]");


  rebuild_node_def({-2});
  INFER_OK(op, "[4,1,5]", "[d0_0,d0_2]");


  rebuild_node_def({-4});
  INFER_ERROR("not in [-3,3)", op, "[1,2,3]");
  rebuild_node_def({3});
  INFER_ERROR("not in [-3,3)", op, "[1,2,3]");
}
