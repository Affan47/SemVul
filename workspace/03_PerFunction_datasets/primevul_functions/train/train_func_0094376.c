TEST(QuantizedPoolingOpTest, AveragePoolActivationRelu1) {


  QuantizedPoolingOpModel m(
      BuiltinOperator_AVERAGE_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, 1}, -15.9375, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, -15.9375, 15.9375}, Padding_VALID, 2, 2,
      ActivationFunctionType_RELU_N1_TO_1);
  m.SetInput({
      0, -6, 2, 4,
      -3, -2, -10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({-1.0, 0.75})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({120, 134}));

  m.SetInput({
      0, -6, -2, -4,
      -3, -2, 10, -7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({-1.0, -0.75})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({120, 122}));
}
