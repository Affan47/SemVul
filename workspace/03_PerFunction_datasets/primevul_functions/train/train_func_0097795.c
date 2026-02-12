TEST(ArrayOpsTest, Reshape_ShapeFn) {
  ShapeInferenceTestOp op("Reshape");
  op.input_tensors.resize(2);


  INFER_OK(op, "?;?", "?");
  INFER_OK(op, "[?];?", "?");
  INFER_OK(op, "?;[?]", "?");
  INFER_OK(op, "[?];[?]", "?");
  INFER_OK(op, "[4];[?]", "?");


  Tensor new_shape = test::AsTensor<int32>({1, 2, 3});
  op.input_tensors[1] = &new_shape;
  INFER_OK(op, "?;[3]", "[1,2,3]");
  INFER_OK(op, "[?];[3]", "[1,2,3]");
  INFER_OK(op, "[6];[3]", "[1,2,3]");

  INFER_ERROR(
      "Cannot reshape a tensor with 12 elements to shape [1,2,3] (6 elements)",
      op, "[3,4];[3]");


  new_shape = test::AsTensor<int32>({-1});
  INFER_OK(op, "?;[1]", "[?]");
  INFER_OK(op, "[?];[1]", "[d0_0]");
  INFER_OK(op, "[2,2];[1]", "[4]");

  new_shape = test::AsTensor<int32>({2, -1});
  INFER_OK(op, "[3,4];[2]", "[2,6]");


  INFER_ERROR("Dimension size must be evenly divisible by 2 but is 7", op,
              "[7];[2]");

  new_shape = test::AsTensor<int32>({-1, -1, 2});
  INFER_OK(op, "[8];[3]", "[?,?,2]");
  INFER_OK(op, "?;[3]", "[?,?,2]");


  new_shape = test::AsTensor<int32>({-1, 2, 3});
  INFER_OK(op, "[?,2,3];[3]", "[d0_0,2,3]");


  new_shape = test::AsTensor<int32>({});
  INFER_OK(op, "[1];[0]", "[]");
  INFER_ERROR(
      "Cannot reshape a tensor with 2 elements to shape [] (1 elements)", op,
      "[1,2];[0]");


  new_shape = test::AsTensor<int32>({-1});
  INFER_OK(op, "[0];[1]", "[0]");
  new_shape = test::AsTensor<int32>({-1, 6});
  INFER_OK(op, "[0,2];[1]", "[0,6]");
  new_shape = test::AsTensor<int32>({0, -1});
  INFER_OK(op, "[0,2];[1]", "[0,?]");
}
