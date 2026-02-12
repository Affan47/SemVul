TEST(FloatPoolingOpTest, AveragePoolActivationRelu1) {
  FloatPoolingOpModel m(BuiltinOperator_AVERAGE_POOL_2D,
                        {TensorType_FLOAT32, {1, 2, 4, 1}},
                        2, 2,
                        {TensorType_FLOAT32, {}}, Padding_VALID, 2,
                        2, ActivationFunctionType_RELU_N1_TO_1);
  m.SetInput({
      0, -6, 2, 4,
      -3, -2, -10, 7,
  });
  m.Invoke();
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({-1.0, 0.75}));

  m.SetInput({
      0, -6, -2, -4,
      -3, -2, 10, -7,
  });
  m.Invoke();
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({-1.0, -0.75}));
}
