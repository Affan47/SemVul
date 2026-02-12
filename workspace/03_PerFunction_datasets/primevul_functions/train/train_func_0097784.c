TEST(ArrayOpsTest, Placeholder_ShapeFn) {
  {

    ShapeInferenceTestOp op("Placeholder");
    TensorShape shape({1, 2});
    TF_ASSERT_OK(NodeDefBuilder("test", "Placeholder")
                     .Attr("shape", shape)
                     .Attr("dtype", DT_FLOAT)
                     .Finalize(&op.node_def));
    INFER_OK(op, "", "[1,2]");
  }

  {

    ShapeInferenceTestOp op("Placeholder");
    TensorShape shape({});
    TF_ASSERT_OK(NodeDefBuilder("test", "Placeholder")
                     .Attr("shape", shape)
                     .Attr("dtype", DT_FLOAT)
                     .Finalize(&op.node_def));
    INFER_OK(op, "", "[]");
  }

  {

    ShapeInferenceTestOp op("Placeholder");
    const int64_t dims[2] = {1, -1};
    PartialTensorShape shape;
    TF_ASSERT_OK(PartialTensorShape::MakePartialShape(dims, 2, &shape));
    TF_ASSERT_OK(NodeDefBuilder("test", "Placeholder")
                     .Attr("shape", shape)
                     .Attr("dtype", DT_FLOAT)
                     .Finalize(&op.node_def));
    INFER_OK(op, "", "[1,?]");
  }

  {

    ShapeInferenceTestOp op("Placeholder");
    PartialTensorShape shape;
    TF_ASSERT_OK(NodeDefBuilder("test", "Placeholder")
                     .Attr("shape", shape)
                     .Attr("dtype", DT_FLOAT)
                     .Finalize(&op.node_def));
    INFER_OK(op, "", "?");
  }
}
