TEST(QuantizedPoolingOpTest, SymmetricAveragePoolPaddingValidStride1) {


  SymmetricQuantizedPoolingOpModel m(
      BuiltinOperator_AVERAGE_POOL_2D,
      {TensorType_INT8, {1, 2, 4, 1}, 0, 15.9375},
      2, 2,
      {TensorType_INT8, {}, 0, 15.9375}, Padding_VALID, 1, 1);
  m.SetInput({
      0, 6, 2, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({2.75, 5.0, 5.75})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({44 - 128, 80 - 128, 92 - 128}));
}
