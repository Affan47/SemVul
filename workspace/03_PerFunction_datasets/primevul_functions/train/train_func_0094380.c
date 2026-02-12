TEST(QuantizedUInt8PoolingOpTest, MaxPoolPaddingSameStride1) {


  QuantizedPoolingOpModel m(
      BuiltinOperator_MAX_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, 1}, 0, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, 0, 15.9375}, Padding_SAME, 1, 1);
  m.SetInput({
      0, 6, 2, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({6, 10, 10, 7, 3, 10, 10, 7})));
  EXPECT_THAT(m.GetOutput(),
              ElementsAreArray({96, 160, 160, 112, 48, 160, 160, 112}));
}
