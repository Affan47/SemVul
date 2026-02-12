TEST(ArrayOpsTest, Tile_ShapeFn) {
  ShapeInferenceTestOp op("Tile");
  op.input_tensors.resize(2);


  TF_ASSERT_OK(NodeDefBuilder("test", "Tile")
                   .Input("input", 0, DT_FLOAT)
                   .Input("multiples", 1, DT_INT32)
                   .Finalize(&op.node_def));


  INFER_OK(op, "?;?", "?");


  INFER_OK(op, "[2,3,1,4];?", "[?,?,?,?]");


  INFER_ERROR("Shape must be rank 1 but is rank 2", op, "[2,3,1,4];[4,1]");


  INFER_OK(op, "?;[4]", "[?,?,?,?]");


  Tensor multiples = test::AsTensor<int32>({2, 3, 4, 5});
  op.input_tensors[1] = &multiples;
  INFER_OK(op, "[2,3,1,4];[4]", "[4,9,4,20]");

  multiples = test::AsTensor<int64_t>({2, 3, 4, 5});
  INFER_OK(op, "[2,3,1,4];[4]", "[4,9,4,20]");
}
