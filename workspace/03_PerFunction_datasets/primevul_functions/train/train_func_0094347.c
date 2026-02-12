TEST(QuantizedPoolingOpTest, SymmetricAveragePoolActivationRelu6) {


  SymmetricQuantizedPoolingOpModel m(
      BuiltinOperator_AVERAGE_POOL_2D,
      {TensorType_INT8, {1, 2, 4, 1}, -15.9375, 15.8130},
      2, 2,
      {TensorType_INT8, {}, -15.9375, 15.8130}, Padding_VALID, 2, 2,
      ActivationFunctionType_RELU6);
  m.SetInput({
      0, -6, 12, 4,
      -3, -2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({0.0, 6.0}, 0.025)));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({128 - 128, 176 - 128}));

  m.SetInput({
      0, 6, 12, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({2.75, 6.0}, 0.025)));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({150 - 128, 176 - 128}));
}
