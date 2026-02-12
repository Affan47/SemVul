TEST(QuantizedPoolingOpTest, AveragePool) {


  QuantizedPoolingOpModel m(
      BuiltinOperator_AVERAGE_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, 1}, 0, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, 0, 15.9375});
  m.SetInput({
      0, 6, 2, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({2.75, 5.75})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({44, 92}));
}
