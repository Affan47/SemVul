TEST(QuantizedInt8PoolingOpTest, MaxPoolActivationRelu1) {


  SymmetricQuantizedPoolingOpModel m(
      BuiltinOperator_MAX_POOL_2D,
      {TensorType_INT8, {1, 2, 4, 1}, -15.9375, 15.8130},
      2, 2,
      {TensorType_INT8, {}, -15.9375, 15.8130}, Padding_VALID, 2, 2,
      ActivationFunctionType_RELU_N1_TO_1);
  m.SetInput({
      -1.7, -6, 2, 4,
      -3, -2, -10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({-1.0, 1.0}, 0.004)));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({120 - 128, 136 - 128}));

  m.SetInput({
      0, -6, -0.2, -0.4,
      -3, -2, 0.75, -0.99,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({0.0, 0.75}, 0.004)));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({128 - 128, 134 - 128}));
}
