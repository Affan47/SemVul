TEST(ArrayOpsTest, BatchToSpaceND_ShapeFn) {
  ShapeInferenceTestOp op("BatchToSpaceND");
  op.input_tensors.resize(3);
  TF_ASSERT_OK(NodeDefBuilder("test", "BatchToSpaceND")
                   .Input("input", 0, DT_FLOAT)
                   .Input("block_shape", 1, DT_INT32)
                   .Input("crops", 2, DT_INT32)
                   .Finalize(&op.node_def));


  INFER_OK(op, "?;[2];?", "?");


  INFER_OK(op, "[?,?,?,?];[2];?", "[?,?,?,d0_3]");

  {

    Tensor block_shape = test::AsTensor<int32>({2, 3});
    op.input_tensors[1] = &block_shape;
    INFER_OK(op, "[?,?,?,2];[2];?", "[?,?,?,d0_3]");

    INFER_OK(op, "[18,?,?,2];[2];?", "[3,?,?,d0_3]");


    {
      Tensor crops = test::AsTensor<int32>({1, 1, 0, 1}, {{2, 2}});
      op.input_tensors[2] = &crops;
      INFER_OK(op, "[18,?,2,2];[2];[2,2]", "[3,?,5,d0_3]");
      op.input_tensors[2] = nullptr;
    }


    {
      Tensor crops = test::AsTensor<int32>({1, 1, 0, 0}, {{2, 2}});
      op.input_tensors[2] = &crops;
      INFER_OK(op, "[18,2,1,2];[2];[2,2]", "[3,2,3,d0_3]");
      op.input_tensors[2] = nullptr;
    }

    op.input_tensors[1] = nullptr;
  }

  INFER_ERROR("block_shape must have rank 1", op, "?;[1,1];?");
  INFER_ERROR("block_shape must have known size", op, "?;[?];?");
  INFER_ERROR("rank", op, "[2,2];[2];[2,2]");
  INFER_ERROR("rank", op, "[2,2,3];[3];[3,2]");

  {
    Tensor block_shape = test::AsTensor<int32>({0, 2});
    op.input_tensors[1] = &block_shape;
    INFER_ERROR("block_shape must be positive", op, "[1,2,2];[2];[2,2]");
    op.input_tensors[1] = nullptr;
  }

  {
    Tensor block_shape = test::AsTensor<int32>({1, 1});
    op.input_tensors[1] = &block_shape;
    Tensor paddings = test::AsTensor<int32>({0, -1, 0, 0}, {{2, 2}});
    op.input_tensors[2] = &paddings;
    INFER_ERROR("crops cannot be negative", op, "[1,2,2];[2];[2,2]");
    op.input_tensors[1] = nullptr;
    op.input_tensors[2] = nullptr;
  }


  {
    Tensor block_shape = test::AsTensor<int32>({2, 2});
    op.input_tensors[1] = &block_shape;
    Tensor crops = test::AsTensor<int32>({3, 2, 0, 0}, {{2, 2}});
    op.input_tensors[2] = &crops;
    INFER_ERROR("Negative", op, "[4,2,3,1];[2];[2,2]");
    op.input_tensors[1] = nullptr;
    op.input_tensors[2] = nullptr;
  }


  {
    Tensor block_shape = test::AsTensor<int32>({2, 3});
    op.input_tensors[1] = &block_shape;
    INFER_ERROR("divisible", op, "[3,1,1,1];[2];[2,2]");
    op.input_tensors[1] = nullptr;
  }
}
