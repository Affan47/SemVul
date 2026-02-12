TEST(QuantizedUInt8PoolingOpTest, MaxPoolActivationRelu1) {


  QuantizedPoolingOpModel m(
      BuiltinOperator_MAX_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, 1}, -15.9375, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, -15.9375, 15.9375}, Padding_VALID, 2, 2,
      ActivationFunctionType_RELU_N1_TO_1);
  m.SetInput({
      -1.7, -6, 2, 4,
      -3, -2, -10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({-1.0, 1.0})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({120, 136}));

  m.SetInput({
      0, -6, -0.2, -0.4,
      -3, -2, 0.75, -0.99,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({0.0, 0.75})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({128, 134}));
}
