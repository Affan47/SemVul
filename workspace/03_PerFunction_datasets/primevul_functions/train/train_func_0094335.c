TEST(FloatPoolingOpTest, MaxPoolWithZeroStride) {
  EXPECT_DEATH(
      FloatPoolingOpModel m(BuiltinOperator_MAX_POOL_2D,
                            {TensorType_FLOAT32, {1, 2, 4, 1}},
                            2, 2,
                            {TensorType_FLOAT32, {}},
                            Padding_VALID,
                            0, 0),
      "Cannot allocate tensors");
}
