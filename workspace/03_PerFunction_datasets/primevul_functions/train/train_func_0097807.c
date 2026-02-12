TEST(ArrayOpsTest, MirrorPadGrad_ShapeFn) {
  ShapeInferenceTestOp op("MirrorPadGrad");
  op.input_tensors.resize(2);


  INFER_OK(op, "?;?", "?");


  INFER_OK(op, "?;[?,4]", "?");


  INFER_ERROR("must be rank 3 but is rank 2", op, "[?,?];[3,2]");


  INFER_ERROR("Dimension 1 in both shapes must be equal, but are 3 and 2", op,
              "[?,?,?];[3,3]");


  INFER_OK(op, "[?,?,?];[3,2]", "[?,?,?]");


  Tensor paddings_t(DT_INT64, TensorShape{3, 2});
  test::FillValues<int64_t>(&paddings_t, {1, 10, 2, 20, 3, 30});
  op.input_tensors[1] = &paddings_t;

  INFER_OK(op, "[111,222,333];[3,2]", "[100,200,300]");
  INFER_OK(op, "[111,?,333];[3,2]", "[100,?,300]");
}
