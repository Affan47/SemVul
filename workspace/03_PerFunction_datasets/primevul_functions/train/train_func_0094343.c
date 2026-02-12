TEST(QuantizedPoolingOpTest, AveragePoolPaddingSameStride1) {


  QuantizedPoolingOpModel m(
      BuiltinOperator_AVERAGE_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, 1}, 0, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, 0, 15.9375}, Padding_SAME, 1, 1);
  m.SetInput({
      0, 6, 2, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(
                  ArrayFloatNear({2.75, 5.0, 5.75, 5.5, 2.5, 6.0, 8.5, 7.0})));
  EXPECT_THAT(m.GetOutput(),
              ElementsAreArray({44, 80, 92, 88, 40, 96, 136, 112}));
}
