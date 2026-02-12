TEST(ArrayOpsTest, QuantizedReshape_ShapeFn) {
  ShapeInferenceTestOp op("QuantizedReshape");
  op.input_tensors.resize(2);


  INFER_OK(op, "?;?;?;?", "?;[];[]");
  INFER_OK(op, "[?];?;?;?", "?;[];[]");
  INFER_OK(op, "[?];[?];?;?", "?;[];[]");
  INFER_OK(op, "[4];[?];?;?", "?;[];[]");
  Tensor new_shape = test::AsTensor<int32>({1, 2, 3});
  op.input_tensors[1] = &new_shape;
  INFER_OK(op, "[?];[3];?;?", "[1,2,3];[];[]");
  INFER_OK(op, "[6];[3];?;?", "[1,2,3];[];[]");
  INFER_ERROR(
      "Cannot reshape a tensor with 12 elements to shape [1,2,3] (6 elements)",
      op, "[3,4];[3];?;?");


  INFER_ERROR("must be rank 0", op, "?;?;[1];?");
  INFER_ERROR("must be rank 0", op, "?;?;?;[1]");
}
