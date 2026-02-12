TEST(ArrayOpsTest, Bitcast_ShapeFn) {
  ShapeInferenceTestOp op("Bitcast");
  auto rebuild_node_def = [&op](DataType input_type, DataType output_type) {
    TF_ASSERT_OK(NodeDefBuilder("test", "Bitcast")
                     .Input("input", 0, input_type)
                     .Attr("type", output_type)
                     .Finalize(&op.node_def));
  };

  rebuild_node_def(DT_FLOAT, DT_INT32);

  INFER_OK(op, "?", "?");


  INFER_OK(op, "[1,2]", "in0");


  rebuild_node_def(DT_INT32, DT_INT64);
  INFER_OK(op, "[1,2]", "[d0_0]");

  INFER_OK(op, "[1,?]", "[d0_0]");


  INFER_ERROR("does not match", op, "[1,4]");
  INFER_ERROR("does not match", op, "[1,3]");


  rebuild_node_def(DT_INT64, DT_INT32);
  INFER_OK(op, "[4,5]", "[d0_0,d0_1,2]");
  rebuild_node_def(DT_COMPLEX128, DT_INT32);
  INFER_OK(op, "[4,5]", "[d0_0,d0_1,4]");
  rebuild_node_def(DT_COMPLEX128, DT_HALF);
  INFER_OK(op, "[4,5]", "[d0_0,d0_1,8]");
  rebuild_node_def(DT_COMPLEX128, DT_INT8);
  INFER_OK(op, "[4,5]", "[d0_0,d0_1,16]");


  rebuild_node_def(DT_STRING, DT_INT32);
  INFER_ERROR("one of the type sizes is zero", op, "[1,2,3]");
  rebuild_node_def(DT_INT32, DT_STRING);
  INFER_ERROR("one of the type sizes is zero", op, "[1,2,3]");
}
