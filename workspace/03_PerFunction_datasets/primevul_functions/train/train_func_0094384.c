TEST(QuantizedUInt8PoolingOpTest, MaxPoolActivationRelu6) {


  QuantizedPoolingOpModel m(
      BuiltinOperator_MAX_POOL_2D,
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
      0, 4.5, 12, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({4.5, 6.0})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({164, 176}));
}
