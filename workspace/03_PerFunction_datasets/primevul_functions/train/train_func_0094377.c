TEST(QuantizedPoolingOpTest, AveragePoolActivationRelu6) {


  QuantizedPoolingOpModel m(
      BuiltinOperator_AVERAGE_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, 1}, -15.9375, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, -15.9375, 15.9375}, Padding_VALID, 2, 2,
      ActivationFunctionType_RELU6);
  m.SetInput({
      0, -6, 12, 4,
      -3, -2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({0.0, 6.0})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({128, 176}));

  m.SetInput({
      0, 6, 12, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({2.75, 6.0})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({150, 176}));
}
