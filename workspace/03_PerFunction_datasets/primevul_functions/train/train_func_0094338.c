TEST(FloatPoolingOpTest, MaxPoolActivationRelu) {
  FloatPoolingOpModel m(BuiltinOperator_MAX_POOL_2D,
                        {TensorType_FLOAT32, {1, 2, 4, 1}},
                        2, 2,
                        {TensorType_FLOAT32, {}}, Padding_VALID, 2,
                        2, ActivationFunctionType_RELU);
  m.SetInput({
      -1, -6, 2, 4,
      -3, -2, 10.5, 7,
  });
  m.Invoke();
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({0.0, 10.5}));
}
